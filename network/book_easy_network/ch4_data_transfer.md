### 네트워크를 통해 호스트를 연결했을 때의 장점
- 자원 공유
- 병렬 처리로 인한 성능 향상
- 중복 저장으로 인한 신뢰성 향상

### 데이터 전송 방식의 종류
- 점대점 (1:1)
    - 스타형, 링형, 완전형, 불규칙형
- 브로드캐스팅: 연결된 모든 호스트에 데이터 전달
    - 버스형(이더넷), 링형

### 오류 제어
- 수신 호스트의 응답 프레임
    - 데이터 프레임의 일부가 깨지는 오류를 확인, 재수신을 요청
    - 변형 오류에 대한 대응
- 수신 호스트의 타이머 기능
    - 분실 오류 시, 수신 호스트는 이를 알 수 없음.
    - 타임아웃을 걸어서 수신 오류에 대응
-순서 번호 기능
    - 수신 호스트의 긍정 응답 프레임이 분실되면 제대로 도착 했음에도 송신 호스트가 인지 불가
    - 프레임에 번호를 매겨서 이를 대응
    - 중복 프레임을 수신하는 오류를 차단

### 흐름 제어
- 송신 호스트와 수신 호스트 사이의 전송 속도를 제어하여 분실 오류를 방지
- 수신 호스트의 버퍼가 가득차서 프레임을 수신하지 못하는 상화을 방지
- 슬라이딩 윈도우 프로토콜을 사용

### 프레임
- 전송 데이터의 오류를 확인하기 위해 체크섬, 송수신 호스트의 주소, 프로토콜의 제어 코드 등의 정보가 포함됨
- 프레임은 문자열로 구성할 수도 있고, 비트 스트림으로 구성할 수도 있다.
- 프레임의 시작과 끝을 알리기 위해서 플래그를 추가하고, 비트 스터핑이라는 방식을 적용해 프레임을 구성한다.

### 다항 코드
- 변형 오류에 대응하는 두 가지 방식
    - 오류 검출 코드 방식: 패리티 비트 추가, 변형 탐지시 재전송 요청, 일반적으로 사용
    - 오류 복구 방식: 수신 호스트가 직접 오류를 복구

### 패리티 비트
- 1 바이트의 데이터에서 나머지 7개의 비트는 정보를 나타내고 1 비트를 패리티 비트로 설정
- 패리티 비트는 바이트 내에서 1의 개수가 짝수 혹은 홀수가 되도록 맞춰주는 역할
- 만일 전송 과정에서 변형이 일어나면 짝수/홀수가 안맞게 되어 검출 가능
- 그러나 비트 두 개가 동시에 바뀔 시에 탐지 불가능

### 블록 검사
- 여러개의 바이트를 하나의 블록으로 구성, 숲형 수직 방향에 모두 패리티 비트 적용

### 다항 코드
- CRC(cyclic redundancy code): 현재 통신 프로토콜에서 가장 많이 사용하는 오류 검출 기법
- 바이트를 다항식으로 표현, ex) 1010 = x^3 + x
- 전송 데이터를 생성 다항식으로 나누어 체크섬 정보를 얻음
- 체크섬을 수신 호스트에 전달, 이를 이용해 데이터가 변형되었는지 체크