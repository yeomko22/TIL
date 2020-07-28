### Backup
- Resource Configuration
- ETCD Cluster
- Persistent Volumes

### Declarative
- resource configuration 파일을 github과 같은 소스코드 버전 관리 시스템에 저장한다.

### Kube-apiserver 이용한 백업
```bash
$ kubectl get all --all-namespaces -o yaml > all-deploy-services.yaml
```
- VELERO 등 외부 솔루션이 있다.

### Backup - ETCD
- ETCD Cluster는 마스터 노드에 호스팅된다.
- etcd 컨피그에 데이터 저장 폴더가 기록되어 있다.
- 스냅샷을 명령어로 생성이 가능하다.
```bash
$ ETCDTL_API=3 etcdctl snapshot save snapshot.db
$ service kube-apiserver stop
$ ETDCCTL_API=3 etcdctl snapshot restore snapshot.db --data-dir /var/lib/etcd-from-backup --initial-cluster master-1
```

- etcd-master pod의 description에서 --listen-client-urls 옵션을 보면 이 etcd가 어느 포트를 수신하고 있는지 알 수 있음.
```
// etcd 백업 파일 생성
ETCDCTL_API=3 etcdctl 
  --endpoints=https://[127.0.0.1]:2379
  --cacert=/etc/kubernetes/pki/etcd/ca.crt 
  --cert=/etc/kubernetes/pki/etcd/server.crt 
  --key=/etc/kubernetes/pki/etcd/server.key 
  snapshot save /tmp/snapshot-pre-boot.db
```
- 스냅샷 생성 시에 cacert, cert, server key 값을 옵션으로 넣어줘야한다.

```
// etcd 백업 파일을 이용한 복구
ETCDCTL_API=3 etcdctl --endpoints=https://[127.0.0.1]:2379 --cacert=/etc/kubernetes/pki/etcd/ca.crt \
     --name=master \
     --cert=/etc/kubernetes/pki/etcd/server.crt --key=/etc/kubernetes/pki/etcd/server.key \
     --data-dir /var/lib/etcd-from-backup \
     --initial-cluster=master=https://127.0.0.1:2380 \
     --initial-cluster-token=etcd-cluster-1 \
     --initial-advertise-peer-urls=https://127.0.0.1:2380 \
     snapshot restore /tmp/snapshot-pre-boot.db
```
- 참고자료: https://github.com/mmumshad/kubernetes-the-hard-way/blob/master/practice-questions-answers/cluster-maintenance/backup-etcd/etcd-backup-and-restore.md
