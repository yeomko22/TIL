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
