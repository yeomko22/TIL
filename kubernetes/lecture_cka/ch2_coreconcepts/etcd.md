### ETCD란?
- key value database

### ETCD 설치 및 실행
- 2379 포트를 기본으로 사용
- set key value로 값 저장 가능
- get key로 값 꺼내오기 가능

### ETCD in Kubernetes
- cluster에 관련한 데이터를 저장한다.
  - Nodes
  - Pods
  - Configs
  - Secrets
  - Accounts
  - Roles
  - Bindings
  - Others

### Setup - Manual
- 직접 파이너리 압축 파일을 다운받아서 설치 가능
- 클러스터를 구축해서 고가용성 확보가 가능하다.

### Setup - kubeadm
- kubeadm이 파드로 관리

### kubernetes registry
- registry
  - minions
  - pods
  - replicasets
  - deployments
  - roles
  - secrets

### ETCT 고가용성
- 여러 etcd 인스턴스가 필요

### 기타 ETCD commands
```
etcdctl snapshot save 
etcdctl endpoint health
etcdctl get
etcdctl put
```
