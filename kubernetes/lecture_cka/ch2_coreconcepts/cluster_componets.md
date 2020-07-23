### 쿠버네티스 구성
- worker node: 실제 컨테이너를 운영
- master node: 워커노드들을 관리, 계획, 스케줄링, 모니터링
- etcd: 키벨류 데이터 베이스
- kube-scheduler: 컨테이너를 올려놓을 적절한 노드를 찾는 역할
- controller-manager
- kube-apiserver: 클러스터 내부의 모든 동작들을 관리
- 모든 것들이 container 형태로 동작이 가능함, docker를 주로 사용
- kubelet: 노드의 컨테이너를 관리하는 캡틴의 역할
- kube-proxy: 컨테이너 간에 통신을 담당, 서로 다른 노드에 배포된 컨테이너들이 통신할 수 있도록 도움

정리하자면
- master
  - ETCD Cluster
  - kube-apiserver
  - kube-scheduler
  - kube-controller-manager
- worker
  - kube-proxy
  - kubelet
  - container runtime engine

### ETCD란?
- key value database

### ETCD 설치 및 실행
- 2379 포트를 기본으로 사용
- set key value로 값 저장 가능
- get key로 값 꺼내오기 가능

### ETCD in Kubernetes
- cluster에 관련한 데이터를 저장한다.
  - Nodes
  - Pods
  - Configs
  - Secrets
  - Accounts
  - Roles
  - Bindings
  - Others

### Setup - Manual
- 직접 파이너리 압축 파일을 다운받아서 설치 가능
- 클러스터를 구축해서 고가용성 확보가 가능하다.

### Setup - kubeadm
- kubeadm이 파드로 관리

### kubernetes registry
- registry
  - minions
  - pods
  - replicasets
  - deployments
  - roles
  - secrets

### ETCT 고가용성
- 여러 etcd 인스턴스가 필요

### 기타 ETCD commands
```
etcdctl snapshot save 
etcdctl endpoint health
etcdctl get
etcdctl put
```

### Kube-API Server
- 주된 관리 컴포넌트
- kubectl 명령어를 내리면 kube-apiserver가 이를 수신하고 etcd에서 데이터를 가져와서 사용자에게 보여주게 됨.
- kubectl을 거치지 않고 곧바로 kube-apiserver로 요청을 날릴 수도 있으며, 이 경우 인증 과정이 필요
```
curl -X POST /api/v1/namespaces/default/pods ...[other]
```
- kube-apiserver의 역할
  - Authenticate user
  - Validate Request
  - Retrieve data
  - Update ETCD (kube-apiserver랑만 유일하게 통신함)
  - scheduler
  - kubelet
- 직접 kube-apiserver를 셋팅하려면 많은 인증서들이 필요하다.

### Kube Controller manager
- 상태를 감시하고, 복구하는 역할을 수행한다.
- node-controller
  - kube-apiserver를 통해서 node들의 상태를 모니터링
  - 5초마다 노드의 상태를 확인
  - 40초 동안 응답이 없으면 unreachable로 표기
  - 5분동안 응답이 없으면 해당 노드에 배포된 파드들을 다른 건강한 노드에 배포
- replication-controller
  - replicaset을 모니터링
  - 만약 특정 파드가 죽었다면 이를 복구하는 역할을 수행한다.
- 그 외에도 많은 종류의 컨트롤러가 있다.
  - Deployment-Controller
  - CronJob
  - Service-Account-Controller
  - Node Controller
  - PV-Binder-Controller
  - PV-Protection Controller
  - Replication Controller
  - Endpoint-Controller
- 이러한 컨트롤러들을 하나의 프로세스로 묶어서 관리하며 이를 Kube-Controller-Manager라 부른다.
- 이 kube-controller-manager 셋팅 시에 옵션으로 node-monitor-period나 node-monitor-grace-period 등과 같은 옵션 값들을 설정해준다.

### Kube scheduler
- 어떤 파드가 어느 노드에 가야할 지를 결정하는 역할을 한다. 
- 파드를 띄우는 역할은 kubelet이 한다.
- 크기가 다른 노드들이 클러스터에 있을 수 있다. 때문에 어느 노드에 어떤 파드가 가야할 지를 선택할 필요가 생겼다.
- 어떻게 선정하는가?
  - 파드의 CPU, 메모리 요구량에 맞지 않은 노드는 제외한다.
  - 랭크를 매긴다. 여유 리소스가 많은 순으로 랭크를 매기게 된다.
  - taint, selector, affinity 등 고려해야할 요소들이 많다.

### Kubelet
- 각각의 노드에서 캡틴의 역할
- 컨테이너를 띄우고 내리며 kube-apiserver와 통신한다.
- kubelet의 역할
  - 클러스터에 노드를 등록
  - 파드를 생성
  - 노드와 파드의 상태를 모니터링

### kube-proxy
- pod-network: 서로 다른 노드 간에 배포된 파드간에 통신이 필요
- 이 때 각 파드는 노드를 옮겨다닐 수 있으므로 ip가 달라질 수 있음
- 서비스를 사용해서 ip를 가져오고, 이를 통해서 파드 간에 통신을 진행
- 그러나 서비스는 실제 파드가 아니다. 이를 버츄얼 컴포넌트라고 한다.
- 실제 통신을 담당하는 것은 kube-proxy이다.
- 각각의 노드는 kube-proxy를 갖고 있다.
- kube-proxy는 새로운 서비스가 생겨나는 것을 모니터링한다.
- 새로운 서비스가 등장하면 kube-proxy는 해당 서비스에 트래픽을 포워딩 시켜주는 iptables rules를 생성한다.
- kube-proxy는 Deamonset의 형태로 배포된다.
