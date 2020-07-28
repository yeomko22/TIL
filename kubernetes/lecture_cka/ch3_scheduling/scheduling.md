### Manual Scheduling
- spec 아래에 nodeName을 지정해서 배포가 가능
- 스케쥴러가 있다면 스케쥴러가 노드를 지정해준다. 이를 수동으로 대체하는 것
```
spec:
  nodeName: node02
```
- 혹은 binding 오브젝트를 생성하는 방법이 있다.
```
apiVersion: v1
kind: Binding
metadata:
  name: nginx
target:
  apiversion: v1
  kind: Node
  name: node02
```

### Label & Selectors
- 오브젝트들을 그루핑하기 위해서 사용함
- 기준에 따라 필터링하기 위해서 사용하기도 함
- 컨트롤러의 셀렉터에 파드의 라벨을 넣어주어 둘을 연결해 줌
```
$ kubectl get pods --selector app=App1
// 라벨 여러개 지정할 때에는 , 뒤에 공백 없이 그냥 이어주면 됨
$ kubectl get pods --selector env=prod,bu=finance,tier=frontend
```

### Annotation
- 일종의 주석을 남기기 위한 역할을 한다.

### Taint, Tolerations
- 모기와 사람의 비유
- taint
  - 모기가 접근하지 못하도록 쫓아냄. 즉, 아무 파드나 노드에 배포되지 못하도록 막아준다.
  - 모기약에 면역이 있는 모기들만 접근이 가능, 이를 tolerate라 한다.
 - taint는 노드에 부여되고 tolerate는 파드에 부여된다.

 ### Taint, Tolearation command
 ```bash
 $ kubectl taint nodes node-name key=value:taint-effect
 ```
 - key=value 값은 toleartion사용을 위한 것
 - 세 가지 효과가 있다.
  - NoSchedule
  - PreferNoSchedule: 가급적 피할 것
  - NoExecute: 새로운 파드가 더 이상 스케쥴 되지 않으며, 기존 파드들도 다른 노드로 쫓아냄
```bash
spec:
  tolerations:
  - key: "app"
    operator: "Equal"
    value: "blue"
    effect: "NoSchedule"
```
- double quote에 주의할 것

### Taint NoExecute
- 해당 노드에 돌고 있던 파드는 다른 노드로 쫓아낸다.
- toleration이 있는 파드만 남겨놓는다.
- taint, toleration을 지정하더라도 특정 파드가 특정 노드로 갈 것이라는 보장을 할 수 없다.
- master node는 자동으로 NoSchedule로 taint가 되어서 여기에는 파드가 배포되지 않는 것
- taint 명령어에 노드명과 taint 명, 그리고 마지막에 -를 붙여주면 untaint를 수행한다.
```
$ kubectl taint nodes master node-role.kubernetes.io/master:NoSchedule-
```

### Node Selector
- 노드별로 갖고 있는 리소스 크기가 다르며, 파드마다 요구하는 리소스 크기가 다르다.
- nodeselector를 사용해서 파드가 배포되어야 하는 노드를 지정하는 방법이 있다.
```
spec:
  nodeSelector:
    size: Large
```
- size: Large라는 라벨을 노드에 붙여주고, 특정 노드에 해당 파드가 배포되도록 설정해주는 것이다.
```
$ kubectl label nodes <node-name> <label-key>=<label-value>
```
- 하지만 Large or Medium, not Small과 같은 규칙들을 적용할 수가 없다. 이를 보완해주는 것이 Affinity이다.

### Affinity
- 파드가 특정 노드에서 동작하도록 보장해주는 역할을 수행한다.
```
spec:
  affinity:
    nodeAffinity:
      requiredDuringSchedulingIgnoredDuringExecution:
      nodeSelectorTerms:
      - matchExpressions:
        - key: size
          operator: In
          values:
          - Large
          - Medium
```
- operator를 통해서 다양한 작업이 가능하다.
```
- matchExpressions:
  - key: size
    operator: NotIn
    values:
    - Small
```
```
- matchExpressions:
  - key: size
    operator: Exists
```

### Affinity Type
- requiredDuringSchedulingIgnoredDuringExecution
- preferredDuringSchedulingIgnoredDuringExecution
- 파드는 두 가지 상태가 있다.
  - DuringScheduling: 파드가 막 생성되어 배포할 노드를 선택해야하는 상황. requiredDuringScheduling은 이 시점에서 affinity rule을 반드시 고려해야 하는 조건이다. 만일 prefer로 설정되어 있고, affinity rule을 만족하는 노드가 없으면 그냥 배포해버린다. 
  - DuringExecution: 파드가 배포되어 동작중인 시점이다. 이미 노드에 파드가 배포되어 동작하는 상황에서 affinity rule이 추가된 상황이다. 현재 쿠버네티스는 IgnoredDuringExecution 밖에 지원하지 않지만, RequiredDuringExecution도 지원될 예정이다. 이 모드에서는 기존에 동작 중인 파드가 새로 추가된 affinity rule에 맞지 않으면 evict 해버린다.
- 예제 Deployment 파일
```
apiVersion: apps/v1
kind: Deployment
metadata:
  name: red
spec:
  replicas: 3
  selector:
    matchLabels:
      app: red
  template:
    metadata:
      name: red
      labels:
        app: red
    spec:
      containers:
      - name: red-container
        image: nginx
      affinity:
        nodeAffinity:
          requiredDuringSchedulingIgnoredDuringExecution:
            nodeSelectorTerms:
            - matchExpressions:
              - key: node-role.kubernetes.io/master
                operator: Exists
```

### Node Affinity vs Taint & Tolerations
- 각각의 장단점이 있으므로 섞어서 사용해야 한다.

### Requests / Limits
- 각 노드는 정해진 리소스가 있으며, 파드는 이 리소스를 소비하게 된다.
- 스케쥴러는 파드가 요구하는 리소스만큼 확보 가능한 노드를 선택해주는 역할을 한다.
- 리소스는 CPU, MEM, DISK로 구성된다.
- 각 파드는 0.5CPU, 256Mi를 기본으로 요구한다.
```
spec:
  resources:
    requests:
      memory: "1Gi"
      cpu: 1
    limits:
      memory: "2Gi"
      cpu: 2
```
- 0.1, 100m으로 표현할 수 있다. 1 CPU는 AWS에서는 1vCPU, GCP와 Azure에서는 1 core이며 1개의 Hypterthread를 의미한다.
- G, M, K로 표현 가능, 뒤에 i 붙여도 동일한 의미한다
- 도커 컨테이너는 기본적으로 소모하는 자원의 한계가 없다. 때문에 하나의 파드가 노드의 모든 자원을 소모할 수 있기 때문에 limit을 걸어주며, 1 cpu 512 Mi가 파드의 기본 limit 값이다.

- 만일 CPU 리미트를 넘어서려 하면 throttle을 발생시켜 리미트를 넘어가지 않도록 조절한다.
- 하지만 MEM 리미트를 넘어서면 파드를 terminate 시켜버린다.
