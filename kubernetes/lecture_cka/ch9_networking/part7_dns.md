### DNS
- kubernetes는 built in DNS를 제공한다.
- 서비스가 생길 때마다 kubernetes DNS는 서비스 이름과 IP를 테이블에 기록한다.
- 그래서 클러스터 내의 모든 파드는 서비스 이름으로 서비스와 통신할 수 있다.
- 네임 스페이스 내부에서는 이름만으로 서로 식별이 가능하다. 그러나 서로 다른 네임 스페이스라면 풀 네임을 붙여줘야 식별 가능하다.
- 만일 apps 네임 스페이스 아래에 web-serice가 위치한다면 web-service.apps.svc.cluster.local로 접속이 가능하다.
- 즉, cluster.local 아래에 svc 아래에 apps 아래에 web-service 도메인이 위치하는 것이며, 이를 실제 도메인 이름처럼 거꾸로 올라가면서 풀 도메인을 생성하게 된다.

### How Kubernetes Implement DNS
- 두 개의 파드가 있다고 가정
- 가장 단순한 방법은 /etc/hosts에 파드 이름과 IP를 각각 기재해주는 것이다.
- 이를 이제 중앙 DNS 서버에 모아주고 /etc/resolv.conf에 DNS 서버 주소를 적어주는 것이다.
- 이 역할을 해주는 것이 kube-dns이며 1.13 버전부터는 CoreDNS가 이 역할을 대체한다.

### CoreDNS
- replicaset 안에 두 개의 파드로 배포됨
- 파드 안에서는 ./Coredns 실행 파일을 돌린다.
- coredns는 config파일을 요구하며 이를 corefile이라 부른다.
- /etc/coredns/Corefile에서 내용을 확인 가능
- 여기서 kubernetes 필드 값에서 도메인의 기본 주소인 clsuter.local 등을 설정한다.
- 이 corefile은 configmap 오브젝트로 생성하여 관리한다.
- 그리고 이 coredns 파드가 새로운 서비스가 생성될 떄를 감지하여 레코드를 추가하는 것이다.
- coredns deployment 자체도 서비스를 만들고, 나머지 파드들은 /etc/resolv.conf에서 이 서비스의 ip를 바라보도록 설정된다.
