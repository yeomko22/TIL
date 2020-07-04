### 파드 스케줄링이란?
- 파드를 어느 노드에서 실행하면 좋을지 결정하는 것
- 어느 노드에서 설정할지 지정 가능 (노드 셀렉터)
- 노드 스펙 최소 요구 조건과 선호 조건 명시 가능 (resource request / limit)
- 파드 간의 관계를 설정 가능 (파드 어피니티)
- 더 이상 스케쥴링을 하지 않도록 노드 설정 가능 (타인트, 커든)

### nodeSelctor
- .spec 필드에 nodeSelector를 통해서 노드의 라벨을 직접 지정 가능
```bash
# 노드에 라벨을 매겨줌
$ kubectl label nodes minikube disktype=ssd
```
```
# yaml 단에서 nodeSelector에 노드의 라벨 지정
spec:
  nodeSelector:
    disktype: ssd
```

### 노드 어피니티 / 안티 어피니티
- 노드 어피니티: 파드들을 묶어서 같은 노드에 실행토록 한다.
- 노드 안티 어피니티: 파드들을 다른 노드에 나누어서 실행토록 한다.

### 노드 어피니티
- requiredDuringSchedulingIgnoredDuringExecution: 스케줄링 시에 꼭 필요한 조건
- preferredDuringSchedulingIgnoredDuringExecution: 스케줄링 시에 만족하면 좋은 조건
```
spec:
  affinity:
    nodeAffinity:
      requiredDuringSchedulingIgnoredDuringExecution:
        nodeSelectorTerms:
          - matchExpressions:
            - key: beta.kubernetes.io/os 
              operator: In
              values:
                - linux
                - window
            - key: disktype
              operator: Exists
      preferredDuringSchedulingIgnoredDuringExecution:
        - weight: 10
          preference:
            matchExpressions:
              - key: kubernetes.io/hostname
                operator: In
                values:
                  - worker-node01
```
- required 조건 충족 못할 시 pending 상태로 대기함
### 파드 어피니티 / 안티 어피니티
- 개별 파드 사이의 관계를 정의
- 같은 노드에 배포되어야 하면 어피니티, 다른 노드에 배포되어야 하면 안티 어피니티를 사용
```
spec:
  affinity:
    podAntiAffinity:
      requiredDuringSchedulingIgnoredDuringExecution:
        - labelSelector:
            matchExpressions:
              - key: app
                operator: In
                values:
                  - store
          topologyKey: "kubernetes.io/hostname"
    podAffinity:
      requiredDuringSchedulingIgnoredDuringExecution:
        - labelSelector:
            matchExpressions:
              - key: app
                operator: In
                values:
                  - store
          topologyKey: "kubernetes.io/hostname"      
```

### 테인트와 톨러레이션
- taint 설정 노드에는 파드를 스케줄링 하지 않는다.
- taint 설정한 노드에 파드 스케줄을 하기 위해서는 toleration을 설정해야한다.
- 노드를 특정 역할만 하도록 만들때 주로 사용한다.
- taint는 key=value:effect로 묶어서 설정이 가능하다.
```bash
# taint 설정
$ kubectl taint nodes minikube key01=value01:NoSchedule
# taint 삭제
$ kubectl taint nodes minikube key01-
```
- effect로는 세 가지 설정이 가능하다.
  - NoSchedule: 톨러레이션 설정이 없으면 파드 스케줄링 안함
  - PreferNoSchedule: 톨러레이션 없으면 파드 스케줄링 안하지만, 클러스터 내에 리소스가 부족해지면 스케줄링 가능
  - NoExecute: 톨러레이션 없으면 스케줄링 하지 않으며, 기존 파드들도 톨러레이션 없으면 종료시킴
```
spec:
  tolerations:
    - key: "key01"
      operator: "Equal"
      value: "value01"
      effect: "NoSchedule"
```

### 커든과 드레인
- cordon은 지정된 노드에 추가로 파드를 스케줄링하지 않도록 함.
- 해당 노드에 NoSchedule 이펙트가 담긴 taint를 추가하고 Unschedulable 속성을 true 값으로 변경한다.
- kubectl cordon, uncordon 명령어로 설정과 해제가 가능하다.
- drain은 지정된 노드에 있는 파드들을 다른 노드로 이동시키는 명령이다.
