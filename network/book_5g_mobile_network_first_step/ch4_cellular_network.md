## 셀룰러 이동통신이란 무엇인가?
### 셀룰러 이동통신 시스템
- 서비스 지역을 적절한 안테나 높이를 갖는 저전력 송신기에 의해 각각 서비스 되어지는 많은 작은 구역들로 나누는 것
- 셀룰러 이동통신 시스템에서는 단말기가 기지국에서 다른 기지국으로 이동해도 통화가 가능
- 이동성 부여를 위해서 HLR이 반드시 필요

### 셀의 정의
- 1 기지국 = 1 셀
- 셀마다 하나의 기지국을 두고 기지국의 송신 출력이 해당 셀만 커버하도록 한다.

### 주파수 재사용
- 전파의 세기는 거리가 멀어질 수록 약해짐
- 일정 거리 이상 떨어진 두 셀에서는 서로 간섭이 적어 동일한 주파수 체널 사용이 가능
- 이를 주파수 재사용이라 하며 재사용 비율을 주파수 재사용율이라 부른다.
- 주파수 재사용율이 높을수록 주파수 재사용할 수 있는 거리가 멀어지고 가입자 수용 용량이 작아짐
- 즉, 주파수 재사용율은 낮을 수록 좋다.

### 셀 분할
- 가입자 수가 증가하여 한 셀에서 수용 가능한 최대 가입자 수를 초과할 경우 작은 크기의 셀들로 분할
- 작은 셀들로 쪼개어 수용 가능 용량을 늘리는 방법
- 이 때 동일 체널 간섭을 최소화 하기 위해서 기지국 송신 출력을 감소시켜야한다.
- 서비스 면적 계산시에는 육각형이 가장 바람직

### 체널 구조
- 기지국과 단말기가 서로의 신호를 전달하는 길
- 기지국 -> 단말기 (forward, down), 단말기 -> 기지국 (backward, up)
- 전송 방향 구분으로는 FDD(Frequency Division Duplex) 방식과 TDD(Time Division Duplex) 방식이 있다.
- RF(Radio Frequency, 무선 주파수): 전파를 이용하여 신호를 송수신하기 위해 할당된 주파수 영역
- Channel: 이동 단말기와 기지국간에 통화가 되는 특정 주파수(주파수 나누어 할당)
  - 제어 체널: 통화하기 전 신호를 주고 받는 체널
  - 통화 체널: 음성 및 데이터 신호가 전달되는 체널

### 셀룰러 엔지니어링
- 전파 예측 모델링: 기지국에서 보낸 전파 신호를 단말기에서 어느 정도 세기로 받을 수 있을지 예측
- 전파 모델링 파라미터: 전파 감쇠에 다양한 요인들이 있음. 이를 파라미터로 설계해서 예측 모델에 반영할 수 있어야 한다.

### 위치 등록
- 단말기가 이동해도 네트워크가 단말기의 위치를 파악 가능하도록 HLR에 저장
- 단말기의 가입자, 번호, 위치 등을 저장하는 데이터 베이스

### 로밍
- 단말기각 다른 이동통신 교환기 서비스 영역 또는 다른 사업자 영역으로 이동하여도 통화가 가능하도록 하는 기술
- 동일 사업자 내 로밍, 사업자 간 로밍, 국제 로밍으로 분류

### 호출
- 단말기는 항상 이동 중, 그러므로 교환기가 단말기를 호출할 때에는 등록되어 있는 기지국을 포함한 인근 기지국을 한꺼번에 호출하며 이를 페이징(Paging)이라 부른다.

### 핸드 오프
- 단말기가 현재 셀에서 이웃한 셀로 이동하는 상황에서도 통화를 유지하는 기술
- 교환기 간, 기지국 간에 이동하는 단말기에 대한 정보를 넘겨주기 때문

### 전력 제어
- 전파는 거리에 따라 감쇄
- 기지국 가까이에 있는 단말기의 전파 수신 신호 크기는 멀리있는 단말기 보다 큼
- 따라서 단말기에서 기지국으로 신호를 보낼 때에는 거리에 따라 출력을 조절해야함
- 이 전력 제어를 잘 수행하지 않으면 순방향 링크, 역방향 링크의 셀 영역이 일치하지 않아서 서비스 품질 저하의 원인이 된다.

### 다이버시티
- 두 개 이상의 독립된 전파 경로를 통해 전송된 여러 개읜 수신신호 가운데 가장 양호한 특성을 가진 신호를 이용하는 방법
- 브랜치 구성법과 합성법이 함께 수행된다.

### 간섭
- 주파수 재사용에 따라서 일정 거리를 두고 동일한 주파수를 사용하는 기지국끼리는 서로 동일체널간섭 현상이 일어난다.
- 특정 주파수 수신시에 인접 주파수 신호가 넘어와서 간섭하는 것을 인접체널간섭이라 한다.

### 통화 품질 측정 방법
- 주관적인 방법
  - MOS(Mean Opinion Score): 고객들에게 5단계 평가 받음
  - DRT(Diagnostic Rhyme Test): 자음이 다른 단어들 구분하는 테스트
- 객관적 방법
  - BER(Bit Error Rate)
  - FER(Frame Error Rate)
  - PER(Packet Error Rate)
  - 이동 통신에서는 버스트 에러가 많이 발생하므로 FER, PER이 특히 중요

### 기지국 엔지니어링
- 기지국 형태 선정: 1셀에 몇개의 기지국을 둘지를 결정, 6섹터(60도씩 담당)의 경우 도심지에 적함
- 기지국 위치 선정: 셀 경계지역에서 수신 신호 레벨을 먼저 선정, 셀 간 중복 지역이 비슷하도록 조정

### 셀룰러 시스템의 구성
- 단말기(MS, 이동국이라고도 부름), 기지국(BTS), 기지국 제어기(BSC), 교환기(MSC), HRL, 관문 교환기 (GMSC), 타 망으로 구성

### 단말기의 구성
- 이동 전화 단말기는 크게 무선 대역 처리부(Radio Frequency)와 기저대역(baseband) 처리부로 구분
- 단말기의 세부 H/W, S/W구조는 스킵

### 기지국의 구성
- 안테나, 무선 처리부(RF), 디지털 처리부(baseband)로 구성
- 철탑을 세우고 철탑 위에 안테나를 설치, 실내에 있는 기지국 장비에 연결함
- 옥외형 기지국과 옥내형 기지국이 있으며 기지국 장비를 실내에 둘지 실외에 둘지 차이
- 환경에 따라 다양한 형태의 기지국이 있다.

### 중계기
- 기지국 만으로 전파가 도달하지 않는 불량 지역을 개선하기 위하여 중간에 신호를 증폭해주는 장치

### 기지국 제어기
- 여러 BTS(기지국)을 제어, 헨드오프 처리부

### 교환기
- MSC(Mobile Switching Center)는 망의 중심부, 이동가입자 상호간 또는 이동통신가입자와 고정 통신망 또는 다른 이동통신 사업자의 가입자와 호를 교환하는 기능을 제공
- HRL 및 VLR과의 정보 교환 기능을 제공
- VLR은 MSC에 내장되어 있음.

### 라우터
- 여러 다른 종류의 망과 다말간에 데이터를 주고 받는 데이터 교환 장비
- 인터넷 망에서 패킷 데이터를 교환하는데 주로 이용됨
- 이동통신망의 핵심 장비가 되어가고 있음

### 라우터의 세가지 주요 기능
- 패킷 전달
- 패킷 데이터 서비스 품질 관리: 지연 시간최소화 되도록 전달하는 등의 서비스 품질 관리
- 혼잡 제어기

### 라우터의 종류
- Access Router
- Distribution Router
- Security Router
- Core Router
- Edge Router
- Border Router
- Subscriber Edge Router / Customer Edge Router
- 음성/데이터/팩스/영상 처리 라우터

### VLR
- 교환기 영역에서 임시적으로 단말기를 관리하기 위해 임시 번호를 부여하여 가입자를 관리하는 데이터 베이스
- MSC 영역의 가입자 정보를 일시적으로 관리
- HLR의 부담을 줄여주는 역할을 수행

 ### HRL
 - 가입자의 위치 정보 등을 보관하는 데이터 베이스

### 인증장치/단말장치 등록기
- 인증키와 인증 알고리즘을 저장하고 인증 절차를 수행하는 장비

### 망관리 / 고객관리 / 과금 시스템
- 장애 관리 및 운용 관리를 위한 장비

### 셀룰러 시스템의 동작
- 이동전화 - 이동전화
1. 단말기가 기지국에 신호를 보냄
2. 기지국은 교환국으로 전달
3. 교환국에서 위치 등록
4. 발신자가 통화 요청
5. 발신자 근처 기지국이 이를 수신, 교환국에 전달
6. 교환국에서는 미리 등록되어 있던 수신자 위치로 일제 호출(Paging)
7. 수신자 근처 기지국이 이를 수신
8. 수신자 단말기에 전화가 가게됨
9. 발신자와 수신자는 각자 체널을 열어놓고 대기하다가 교환국과 기지국이 위치를 찾으면 두 체널이 연결되어 통화가 이루어지게 된다.

### 핸드오프 절차
1. 통화중에 신호가 약해지면 기지국에 체널 전환 요청
2. 기지국은 이를 교환국에 전달
3. 교환국은 신호 세기가 강한 기지국에 전환을 지시
4. 또한 교환국은 기존 기지국을 통해서 단말기에 새로운 기지국 체널 정보를 알려줌
5. 기존 기지국은 단말기와 연결을 끊고 교환국에 알려줌
6. 단말기는 새로운 기지국과 통신하고 이를 교환국에 알려줌

### 통화 품질 장애의 원인
1. 통화가 안이루어 질 때
  - 전파 환경상의 문제, 서비스 되지 않는 지역에 있는 경우
  - 네트워크의 문제, 교환국 및 기지국의 용량이 부족하거나 고장인 경우
  - 단말기의 문제, 소프트웨어 및 하드웨어의 문제
2. 통화 중 끊어지는 경우
  - 서비스가 안되는 전파가 없는 지역으로 들어가는 경우
  - 핸드오프를 했는데 새로운 기지국에 체널이 없는 경우
3. 통화 중 잡음이 생기는 경우
  - 전파의 세기가 약한 곳에서 통화할 때
  - 교환 시슽메에서 다른 사용자의 신호를 중꼐하여 수신하였을 때
