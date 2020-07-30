### Service Networking
- clusterIP: 클러스터 내부에서 파드에 고정적인 IP를 부여
- NodePort: 파드를 외부에 노출시킴
- 서비스는 어떻게 동작하는 것일까?
- 서비스는 cluster wide 컨셉이다. 실제 오브젝트로 존재하거나 별도의 서버로 존재하는 것이 아니다.

### kube-proxy
- 파드를 직접 생성하는 것은 kubelet의 역할이다. 여기에 IP를 부여하는 것은 kube-proxy가 수행한다. 그렇다면 kube-proxy는 대체 어떻게 이 작업을 수행하는 것인가
- userspace, iptables, ipvs 셋 중에 선택할 수 있으며 iptable이 기본 옵션이다.
- db라는 파드가 배포되었다고 치고 db-service도 만들었다고 하자.
- 파드와 서비스에 IP가 부여되는데, 이 범위는 kube-apiserver 실행시에 --service-cluster-ip-range ipNet 옵션 값으로 전달할 수 있으며, 10.0.0.0/24가 기본값이다.
- 파드와 서비스의 IP는 겹쳐서는 안된다.
- 서비스를 아래 명령어로 까볼 수 있다.
```
$ iptables -L -t net | grep db-Service
```
- 서비스가 해주는 역할은 사실은 서비스 IP로 들어오는 트래픽을 DNAT을 이용해 파드의 IP로 포워딩 해주는 것이다.
- NodePort도 마찬가지로 생성하면 kube-proxy가 iptable을 설정해주는 것이다.
- 결국 서비스의 정체는 iptable에 라우팅 룰을 추가해주는 것이다.
