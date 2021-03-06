### 프로토콜 설계 시에 고려 사항
- 주소 표현: 상대방을 구분할 수 있도록 표현.
    - 브로드캐스팅 방식: 모든 호스트에 데이터를 전송하도록 표기
    - 멀티캐스팅 방식: 그룹으로 묶어서 지칭하는 방식
- 오류 제어: 전송 실패시 재전송 
- 흐름 제어: 송신 호스트와 수신 호스트 사이 전송 속도 조절
- 데이터 전달 방식: 단방향, 전이중, 반이중

### 서비스 프리미티브
- 하위 계층이 상위 계층에 서비스를 제공하는 방식으로 프로토콜이 동작
- 연결형: CONNECT, DATA, DISCONNECT
- 비연결형: REQUEST, INDICATION, RESPONSE, CONFIRM

### TCP/IP
- 인터넷은 네트워크 계층으로 IP, 전송 계층으로 TCP/UDP 사용
- TCP/UDP는 커널의 기능. 유저는 소켓 시스템 콜을 호출하여 TCP와 UDP 기능을 사용 가능
- TCP/IP를 구현하기 위해서는 이를 보조하는 프로토콜들이 필요

### ARP/RARP
- 인터넷 통신을 하기 위해서는 자신의 IP, MAC, 상대방의 IP, MAC가 필요
- IP -> MAC으로 변환할 때 사용하는 프로토콜이 ARP
- MAC -> IP로 변환할 때 사용하는 프로토콜이 RARP

### ICMP
- IP 동작 과정에서 오류가 발생하면 오류 메세지가 생성. 이를 전송하는 기능을 담당하는 프로토콜
