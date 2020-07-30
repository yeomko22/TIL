### Docker Container Netwokring type
- host: 호스트 네트워크에 직접 달라붙는 유형
```bash
$ docker run --network host nginx 
```
- 컨테이너를 생성할 때마다 컨테이너의 네임스페이스가 생성된다.
- bridge: 컨테이너들이 브릿지에 달라붙는 유형으로 기본 네트워크 옵션. docker0라는 이름이 붙는다.
- 컨테이너와 브릿지는 veth를 통해서 연결된다.
- 포트 포워딩은 iptable을 통해서 수행한다.

### CNI(Container Networking Interface)
- 지금까지 살펴본 네트워킹 과정
  - 네트워크 네임 스페이스 만들기
  - 브릿지 만들기
  - VETH로 네임 스페이스와 브릿지 연결하기
  - IP 할당하기
  - interface UP 하기
  - NAT 활성화 시키기

- 이를 도커에 적용해보면 아래와 같다.
  - 네임 스페이스(컨테이너) 만들기
  - 브릿지 만들기
  - VETH로 네임스페이스와 브릿지 연결하기
  - IP 할당하기
  - interface UP하기
  - NAT 활성화 시키기
- 사실 쿠버네티스도 비슷한 과정으로 네트워크를 구성한다. 그러니 걱정하지 말라.
- 이러한 과정을 추상화시켜주고, 도커, 메소스, 로켓 등 여러 컨테이너 솔루션들에 대해서도 손쉽게 네트워킹 작업을 수행할 수 있도록 정해진 표준을 CNI라고 부른다.

### CNI
- CNI는 컨테이너 런타임들이 어떠한 요구 조건들을 만족시켜야하는지를 규정한다.
- CNI는 플러그인들이 어떠한 기능들을 제공해야하는 지를 규정한다. 
- CNI를 만족시키는 플러그인들로 CNI 측이 자체 개발한 BRIDGE, VLAN, IPVLAN, MACVLAN, WINDOWS, DHCP, host-local 등이 있다.
- 써드 파티 플러그인들로는 weaveworks, flannel, cilium, nsx 등이 있다.
- docker는 CNI를 구현하지 않았다. 

### Cluster Networking
- 쿠버네티스 클러스터는 여러대의 노드로 구성되어 있다.
- 각 노드는 적어도 하나의 인터페이스를 가지고 네트워크에 연결된다.
- 각 노드(호스트)들은 고유한 ip 주소와 맥주소를 가진다.
- 마스터 노드의 kube-apiserver는 6443 포트로 요청들을 수신한다.
- 마스터 노드와 워커 노드들의 kubelet은 10250 포트를 사용한다.
- kube-scheduler는 10251 포트를 사용한다.
- kube-controller-manager는 10252 포트를 사용한다.
- etcd는 2379 포트를 사용한다.
