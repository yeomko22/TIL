### monitoring
- low level metric을 수집한다. CPU, memory, disk, network와 관련된 지표들
- 이런 메트릭을 수집해서 모니터링 솔루션에 전달한다.
- metric server, prometheus, elastic stack 등등이 있다.

### Heaster vs Metrics server
- Heapster는 이제 deprecated된다.
- metrics server가 이를 대체한다. metric을 in-memory에 저장, 영구 저장이 아니다.
- 쿠버네티스 노드에는 kubelet이 떠있으며 그 안에는 cAdvisor가 있다. 이는 각각의 파드들에서 메트릭들을 수집하는 역할을 한다.
- 간단한 명령어로 메트릭 확인 가능하다.
```
$ kubectl top node
$ kubectl top pod
```

### logs
```
// 도커 컨테이너 로그 확인
$ docker logs -f ecf 

// 쿠버네티스 파드 로그 확인
$ kubectl logs -f <파드 이름>

// 파드 안에 컨테이너가 여러개인 경우
$ kubectl logs -f <파드 이름> <컨테이너 이름>
```
- 자격증 시험에서는 이 정도만 알아도 된다.
