### Demonset이란?
- 모든 노드에 하나의 파드를 자동으로 띄워준다.
- 모니터링, 로그 뷰어 등의 기능을 수행할 수 있다.
- deamonset의 대표적 사례가 kube-proxy이다.
- networking도 좋은 사례 중 하나이다.
```
apiVersion: apps/v1
kind: DeamonSet
metadata:
  name: <DEAMONSET-NAME>
spec:
  selector:
    matchLabels:
      app: monitoring-agent
  template:
    metadata:
      labels:
        <KEY:VALUE>
    spec:
      containers:
      - name: <CONTAINER-NAME>
        image: <IMAGE-NAME>
```

### DaemonSet 작동 원리
- 1.12 버전 이전까지는 DeamonSet의 각 파드들은 nodeSelector를 통해서 특정 노드를 지정해서 파드를 배포하는 방식으로 작동했다.
- 1.12 버전 부터는 nodeAffinity와 default scheduler를 사용해서 배포한다.
