### 전송 계층의 기능
- 데이터 링크 계층이 물리적인 데이터 전송을 담당한다면 전송 계층은 논리적인 선로를 통해 데이터를 주고 받음
- 흐름 제어: 수신 호스트의 슬라이딩 윈도우 크기를 조절하여 송신 호스트의 패킷 전송 속도를 제어
- 오류 제어: 패킷 변형이나 분실등의 오류 발생 시 재전송을 요청
- 분할과 병합: 상위 계층에서 전송을 요구한 데이터의 크기가 전송 계층에서 처리할 수 있는 크기보다 클 경우 이를 쪼개어 전송
- 서비스 프리미티브: 전송 계층을 사용하기 위한 인터페이스

### TCP 주요 기능
- 연결형 서비스를 제공
- 전이중 (Full Duplex) 방식의 양방향 가상 회선을 제공
- 신뢰성 있는 데이터 전송을 보장

### TCP 특징
- IP 프로토콜 위에서 동작하는 전송 계층의 프로토콜은 TCP와 UDP가 있으며, 이들은 운영체제 내부 기능으로 구현됨.
- 상위 계층에서 시스템 콜을 통해서 사용이 가능
- 데이터를 세그먼트라는 블록 단위로 분할하여 전송 

### TCP 헤더 필드
- Source Port/Destination Port: 호스트 내부에서 다른 프로세스와 구분할 수 있도록 프로세스의 고유 주소가 필요.
  포트는 프로세스에 할당되는 네트워크 자원
- Sequence Number: 송신 프로세스가 지정하는 순서 번호. 세그먼트 전송 과정에서 전송되는 바이트 수를 기준으로 증가
  TCP에서는 전송 데이터의 각 바이트마다 순서 번호가 존재
- Acknowledgement Number: 수신 프로세스가 제대로 수신한 바이트의 수를 응답하기 위해서 사용
- Data Offset: 데이터의 시작 위치를 나타냄
- Window:  수신 윈도우의 버퍼 크기 지정을 위해서 사용. 수신 프로세스가  수신할 수 있는 바이트 수를 표시
- Checksum: 변형 오류를 검출하기 위해서 사용.
- Urgent Pointer: 긴급 데이터를 처리하기 위한 것

### TCP 헤더의 플래그 비트
- TCP 헤더에는 플래그 비트가 8개 정의되어 있음
- 처음 2개는 혼잡 제어 용도로 사용
- 나머지 6개는 1이면 다음 의미를 지님
  - URG: Urgent Pointer 필드가 유효한지 나타냄
  - ACK: Acknowledgement Number 필드가 유효한지 나타냄
  - PSH: 현재 세그멘트에 포함된 데이터를 상위 계층에 즉시 전달하도록 지시할 때 사용
  - RST: 연결의 리셋이나 유효하지 않은 세그먼트에 대한 응답용으로 사용
  - SYN: 연결 설정 요구를 의미
  - FIN: 연결을 종료하고 싶다는 의사를 상대방에게 알리기위해 사용

### 혼잡 제어
- ECN은 라우터가 송신 프로세스에 명시적으로 혼잡 발생을 알려주어 송신 프로세스가 트래픽을 완화하는 기술
- TCP는 ECN 기능을 지원하기 위해서 CWR 필드와 ECE 필드를 정의

### 포트 번호
- TCP와 UDP가 상위 계층에 제공하는 주소 표현 방식
- TCP 연결 설정되면 양 단의 프로세스가 사용하는 고유 주소는 IP 주소와 포트 번호가 조합된 형태

### TCP 연결 설정
- three way handshake를 통해서 연결을 설정
- SYN 패킷으로 연결 설정을 요청
- SYN, ACK로 연결 요청에 응답, 이 때 ACK는 처음 SYN에서 전달된 Seq보다 1 증가해서 보냄
- 연결이 되었다는 의미로 ACK 전송. 이 때 전송하고자 하는 데이터가 있다면 실어서 보낸다.

### TCP 데이터 전송
- 흐름 제어로는 헤더의 윈도우 필드를 사용
- 분실 오류 발생 시 timeout을 발생시켜 재전송이 이루어짐
- 변형 오류 발생 시 NAK 전송하지 않고 마찬가지로 timeout 발생시켜 재전송 요청

### 연결 해제
- FIN 패킷 전송해서 연결 해제 요청
- FIN, ACK를 전송해서 해제 요청에 응답, 그리고 남은 데이터 마저 전송
- 전송한 데이터에 대한 ACK 전송
- 그 다음 FIN 패킷을 보내어 연결 해제 승인
- ACK 보내주어 연결해제 완료
