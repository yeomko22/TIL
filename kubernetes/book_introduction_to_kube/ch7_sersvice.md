### Service란?
- 쿠버네티스에서 파드는 노드를 옮겨다니면서 실행이 가능
- 그러므로 파드의 IP는 계속해서 변하므로 이를 고정적으로 접근하기 위해서 Service 사용
- 서비스는 주로 L4 영역에서 통신, 인그레스는 L7 영역에서 통신할때 사용

### Service Type
- ClusterIP: 기본 서비스 타입, 클러스터 내부에서만 사용 가능, 외부에서 접속 불가
- NodePort: 클러스터 외부에서 접속할 수 있는 가장 간단한 방법
- LoadBalancer: 클라우드 서비스에서 제공하는 로드밸런서 장비에서 사용
- ExternalName: 서비스를 spec.externalName 필드에 설정한 값과 연결, 클러스터 내부에서 외부 접근 시에 사용

### ClusterIP
- selector로 지정된 파드들의 IP를 꾸준히 지켜봄
- 해당 서비스로 들어오는 요청을 파드들에게 연결시켜 줌
- cluster 내부에서만 접속이 가능하므로 테스트용 파드를 하나 만든 후 해당 파드 내로 들어가서 요청을 날려보면서 테스트가 가능

### 헤드리스 서비스
- .spec.clusterIP 필드 값을 None으로 설정하면 clusterIP가 없는 서비스를 만들 수 있음
- 로드 밸런싱이 필요 없거나, 단일 서비스 IP가 필요 없을 때 사용
- 헤드리스 서비스에 셀렉터를 설정하면 쿠버네티스 API로 확인할 수 있는 엔드포인트가 만들어짐

### kube-proxy
- 쿠버네티스에서 서비스를 만들었을 때 클러스터 IP나 노드포트로 접근할 수 있게 만들어 실제 조작을 하는 컴포넌트
- 네트워크 관리 방법으로 userspace, iptables, IPVS 등이 있다.
- 현재는 iptables를 기본으로 사용하지만 IPVS로 바뀔 것으로 예상됨

### 로드 밸런싱 알고리즘
- round robin: 프로세스 사이 우선순위 두지 않고 순서와 시간 단위로 CPU 할당
- least connection: 접속 개수가 가장 적은 서버 선택
- destination hashing: 목적지 IP 주소로 해시값을 계산해 분산할 실제 서버를 선택
- source hashing: 출발지 IP 주소로 해시값을 계산해 분산할 실제 서버를 선택
- shortest expected delay: 응답 속도가 가장 빠른 서버 선택
- never queue: 활성 접속 개수가 0인 서버를 가장 먼저 선택
