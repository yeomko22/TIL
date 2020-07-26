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
