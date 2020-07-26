### Replication Controller
- 쿠버네티스의 초기 컨트롤러
- High Availability
  - 파드를 운영하다가 크래쉬가 났다.
  - 서비스 중단을 방지하기 위해서 여러 파드를 띄워놓으며 이를 고가용성을 확보했다고 한다.
  - Replication Controller는 클러스터에 일정 숫자만큼 파드가 운영되도록 관리하는 역할을 한다.
- Load Balancing & Scaling
  - 사용자가 늘어나면 더 많은 파드가 필요해지며, 더 많은 노드에 파드를 배포해야 할 수 있어야한다.
  - 이를 Replication Controller를 통해서 관리가 가능하다.

### Replication Controller yaml 예시
```
apiVersion: v1
kind: ReplicationController
metadata:
  name: myapp-rc
  labels:
    app: myapp
    type: front-end
spec:
  replicas: 3
  template:
    metadata:
      name: myapp-pod
      labels:
        app: myapp
        type: front-end
    spec:
      containers:
      - name: nginx-containers
        image: nginx
```
- spec 아래 template에 replication controller에서 운용할 파드의 명세를 넣어준다.

### Replication Set yaml 예시
```
apiVersion: apps/v1
kind: ReplicaSet
metadata:
  name: myapp-rc
  labels:
    app: myapp
    type: front-end
spec:
  selector:
    matchLabels:
      type: front-end
  replicas: 3
  template:
    metadata:
      name: myapp-pod
      labels:
        app: myapp
        type: front-end
    spec:
      containers:
      - name: nginx-containers
        image: nginx
```
- replicaset은 replication controller의 발전형
- selector의 사용이 가능함
- 왜 selector를 지정해주어야하는가? -> template에 지정되지 않은 파드에도 연결이 가능하기 때문이다.

### Labels and Selector
- 파드 세 개가 있고, 여기에 ReplicationSet이 모니터링 중이다.
- 클러스터에 수백개의 파드가 있다고 생각할 때, ReplicaSet 프로세스가 어느 파드를 모니터링할 지 결정하기가 어렵다.
- 이 떄 레이블이 사용된다.
- 만일 레플리카 셋을 생성했을 때 matchLabels에 해당하는 파드들이 이미 생성되어 있다면 추가적으로 파드를 생성하지 않고 파드들에 레플리카 셋이 연결된다.
- 만일 모니터링 해야할 파드가 없다면 템플릿에 기재되어 있는 파드를 생성하게 된다.
- 추후에 특정 파드가 죽게 될 경우 새로 생성해줘야 하므로 template는 반드시 기재를 해주어야한다.

### Scale
- yaml에서 replicas의 숫자를 늘려주면 됨
- kubectl scale --replicas=6 -f replicaset-definition.yaml
- kubectl scale --replicas=6 replicaset myqpp-replicaset

### commands
```
$ kubectl create -f replicaset-definition.yaml
$ kubectl get replicaset
$ kubectl delete replicaset myapp-replicaset
$ kubectl replace -f replicaset-definition.yaml
$ kubectl scale --replicas=6 -f replicaset-definition.yaml
```
