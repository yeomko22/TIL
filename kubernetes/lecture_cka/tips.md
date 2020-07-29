### kubectl run 명령어로 간단한 파드 생성하기
```
// nginx 파드 생성하기
$ kubectl run --generator=run-pod/v1 nginx --image=nginx

// 파드 yaml 파일 생성하기
$ kubectl run --generator=run-pod/v1 nginx --image=nginx --dry-run -o yaml

// deployment 생성하기
$ kubectl create deployment --image=nginx nginx

// deployment yaml 파일 생성하기
$ kubectl create deployment --image=nginx nginx --dry-run -o yaml
$ kubectl create deployment --image=nginx nginx --dry-run -o yaml > nginx-deployment.yaml
```

### Imperative Command 사용
- 대부분의 쿠버네티스 작업은 declarative하게 이루어지지만, Imperative 커맨드를 사용해서 더 쉽고 빠르게 작업을 수행할 수도 있다.
```
$ kubectl run nginx --image=nginx
$ kubectl create deployment --image=nginx nginx
$ kubectl create deployment --image=nginx nginx --dry-run=true -o yaml
```
--dry-run=true로 지정하면 리소스를 실제로 생성하지 않고, 해당 명령문이 유효한지, 리소스를 생성할 수 있는지를 검사만 한다.

```
$kubectl create deployment --image=nginx nginx --dry-run=client -o yaml > nginx-deployment.yaml
```
- Deployment 생성용 yaml 저장

```
$ kubectl expose pod redis --port=6379 --name redis-service --dry-run=client -o yaml
$ kubectl create service clusterip redis --tcp=6379:6379 --dry-run=client -o yaml

$ kubectl expose pod nginx --port=80 --name nginx-service --type=NodePort --dry-run=client -o yaml

$ kubectl create service nodeport nginx --tcp=80:80 --node-port=30080 --dry-run=client -o yaml
```
```
$ kubectl run httpd --image=httpd:alpine --port=80 --expose
```
- 파드, 클러스터ip 생성하고 포트 노출

- 배포된 파드의 구성을 yaml 파일로 출력하기
```
$ kubectl get pods <파드 이름> -o yaml >> result.yaml
```

- 모든 네임스페이스에 대해서 오브젝트를 조회하려면 --all-namespaces 옵션을 추가한다.
```
$ kubectl get daemonsets --all-namespaces
```
- kubernetes 마스터 노드에서 워커 노드 ssh 접속하기
```
$ ssh <워커 노드 내부 ip>
```
- 각 워커 노드의 kubelet 설정 파일 위치
```
// 아래 파일에서 staticPodPath 옵션을 확인할 것
/var/lib/kubelet/config.yaml
```

```
$ cd /etc/systemd/system/kubelet.service.d
$ cat 10-kubeadm.conf
// KUBELET_CONFIG_ARGS=--config=/var/lib/kubelet/config.yaml
$ grep -i static /var/lib/kubelet/config.yaml
// staticPodPath를 알아낼 수 있음

```

### kube-apiserver configureation
```
$ cat /etc/kubernetes/manifests/kube-apiserver.yaml
```
