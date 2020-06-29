### kubectl 기본 사용법
```
// 파드 생성
$ kubectl run {파드 이름} --image="도커 이미지 경로" --port="사용할 포트"

// 파드들에 접근할 때 필요한 서비스를 생성
// 아직 서비스에 대한 개념이 부족
$ kubectl expose pod {파드 이름} --type=NodePort
```

```
$ kubectl get pods
>>
NAME                                          READY   STATUS    RESTARTS   AGE
calico-kube-controllers-8bb9d4787-85stz       1/1     Running   1          2d16h
calico-node-jckc9                             1/1     Running   2          2d16h
calico-node-qcsmc                             1/1     Running   2          2d16h
```
- Name: pod 이름
- Ready: 숫자 형태로 파드 준비 상태 표시
- Status: Running, Terminating, ContainerCreating 등으로 표시

```
$ kubectl get services
NAME                        TYPE        CLUSTER-IP      EXTERNAL-IP   PORT(S)                  AGE
coredns                     ClusterIP   10.233.0.3      <none>        53/UDP,53/TCP,9153/TCP   2d16h
dashboard-metrics-scraper   ClusterIP   10.233.50.79    <none>        8000/TCP                 2d16h
echoserver                  NodePort    10.233.42.144   <none>        8080:32369/TCP           3m4s
kubernetes-dashboard        ClusterIP   10.233.31.158   <none>        443/TCP                  2d16h
```
```
$ kubectl port-forward svc/echoserver 8080:8080
```

```
// 실행중인 파드의 로그 수집 시 사용
$ kubectl logs -f {파드 이름}
```
