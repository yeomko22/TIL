### Pod Status
- Pending: 어느 노드에 배치할지 결정하는 단계
- ContainerCreating: 컨테이너를 만드는 단계
- Running: 컨테이너가 동작하는 단계

### Pod Condition
- 파드의 상태를 나타내주는 true/false 지표들
- PodScheduled
- Initialized
- ContainerReady
- Ready

### Pod Ready Condition
- 하나의 파드는 여러개의 컨테이너를 포함하고, 컨테이너 안에는 여러개의 프로세스가 돌고 있다.
- 그러나 프로세스가 시작해서 준비되기까지 시간이 걸리는 애플리케이션들이 있다. 그런데 파드가 Ready 상태가 되면 쿠버네티스는 해당 파드가 트래픽을 받을 준비가 되어 있다고 간주하고 트래픽을 보내게 되고, 그 결과로 사용자는 원하는 서비스를 제공받지 못하게 된다.
- 따라서 이 중간의 간격을 메꿔주는 장치가 필요하며, Readiness Probes가 하나의 해결책이다.
- 웹 서버의 경우 준비 여부를 확인하는 api를 하나 만들어서 설정해준다.
- 혹은 TCP test나 준비 상태를 확인할 수 있는 스크립트 파일도 좋다.
```
spec:
  containers:
    readinessProbe:
      httpGet:
        path: /api/ready
        port: 8080
      initialDelaySeconds: 10
      periodsSeconds: 5
      failureThreshold: 8
```
```
spec:
  containers:
    readinessProbe:
      tcpSocket:
        port: 3306
```
```
spec:
  containers:
    readinessProbe:
      exec:
        command:
          - cat
          - /app/is_ready
```

### Multi Pod Readiness Probes
- 파드 여러개가 트래픽을 수신하고 있을 때, 새로운 파드가 추가되어 Ready 상태가 되면 서비스는 자동으로 새로운 파드에 트래픽을 나누어 준다.
- 그러나 해당 파드 내의 애플리케이션이 준비가 되지 않았다면 에러가 발생한다. 따라서 이러한 상황을 방지하기 위해서 readiness probe가 중요하다.

### Liveness Probes
- 파드 안의 컨테이너 안의 애플리케이션이 실제로 동작 중인지 여부를 확인하기 위한 장치
- 만일 정상적으로 작동하지 않는다면 해당 컨테이너를 파괴하고 다시 만든다.
- 웹 애플리케이션 서버라면 healty 여부를 체크하는 api를 추가한다.
- tcp socket 테스트나 스크립트 파일 실행 등으로 liveness 테스트를 수행 가능하다.
- 문법은 readinessProbe와 동일하다.

### Monitoring Kubernetes
- 노드 레벨 메트릭, 파드 레벨 메트릭, 컨테이너 레벨 메트릭이 있다.
- 쿠버네티스는 자체적으로 이러한 메트릭들을 모두 수집해서 모니터링을 제공해주는 툴을 내장하고 있지 않다.
- 대신 오픈 소스 툴들이 있으며, metric server, prometheus, elastic stack, datadog, dynatrace 등의 도구들이 있다.

### Heapster vs Metric server
- 이전까지는 Heapster가 표준, 지금은 Metric Server를 쓴다.
- 쿠버네티스의 각 노드들은 kubelet을 띄우며, kubelet 안에는 cAdvisor가 내장되어 있다.
- 이 kubelet 안의 cAdvisor가 파드들로부터 메트릭을 수집해서 metric server에 전송해주는 역할을 한다.
- 깃헙에서 소스코드를 받아서 yaml 파일을 이용해 오브젝트를 만들어줌으로써 사용이 가능하다.
- 그 결과로 kubectl top node 명령어로 모니터링이 가능하다.
```
$ kubectl top node
$ kubectl top pod
```
