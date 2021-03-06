### ipv6
- IPv4의 32비트 주소 공간이 부족하여 이를 대체하기 위한 차세대 프로토콜
- 128비트 주소 공간 사용
- 헤더 구조 단순화
- Flow Label이라는 필드를 도입하여 흐름 제어 기능을 지원
- 16진수 8개를 :로 붙여서 사용

### DS/ECN 필드
- DS: DS가 동일한 트래픽은 동일한 서비스 등급으로 처리된다.
- ECN: 혼잡이 예상될 경우 송신 호스트에게 전송하여 송신 속도를 조절한다.

### Flow Label 필드
- 음성이나 영상 데이터 처럼 실시간 서비스가 필요할 때 사용
- 해당 패킷만 중간 호스트들이 특별한 기준으로 처리할 수 있도록 지원

### 터널링
- 이동 호스트가 자신의 고유 주소를 유지하면서 인터넷 서비스를 받기위한 라우팅 처리
- 기존에 할당 받은 IP와 이동한 새 위치에서의 IP 두 가지 주소를 관리
- 먼저 호스트가 이동하게 되면 Foreign Agent로 부터 COA를 발급 받음
- Foreign Agent는 Home Agent와 COA를 이용하여 터널을 형성한다.
- 송신 호스트 -> Foreign Agent로 패킷 전송, 이 때 자신의 홈 주소 사용
- Foreign Agent는 Home Agent에 터널을 이용하여 데이터 전송
- Home Agent가 수신 호스트에 데이터 전달
- 즉, 이동 호스트는 자신의 Home Address와 이동시 발급받은 COA를 이용하여 데이터 송수신을 하는 것

### 기타 프로토콜
- ARP: IP -> MAC
- RARP: MAC -> IP
- ICMP: IP 레이어에서 발생하는 오류 처리
- IGMP
  - 특정 그룹에 속하는 모든 호스트들에게 메세지를 전송하는 방식을 멀티캐스팅
  - 멀티 캐스트 그룹에 가입하거나 탈퇴할 때 사용하는 프로토콜
