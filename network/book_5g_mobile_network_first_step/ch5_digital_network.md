## 디지털 통신이란 무엇인가
### 디지털 신호란?
- 아날로그: 어떠한 양을 표시할 때 틈이 없이 연속적인 값으로 나타내는 것
- 디지털: 어떤 양을 표시할 때 비연속적인 값으로 나타내는 것
- 아날로그 신호를 디지털 신호로 변환하는 것일 디지털 화라고 부른다.
- 디지털 통신 방식은 보내는 정보량 대비 비용이 아날로그에 비해 급격히 낮아짐

### 디지털 신호의 장점
1. 외부 방해 신호에 대한 저항력이 크다.
  - 디지털 신호는 0과 1만 존재, 간섭을 받아서 0.8 또는 1.2가 도이ㅓ도 1로 복구 가능
2. 디지털 통신은 신호를 통신 체널 조건에 맞추는 지능적인 성격을 갖는다.
  - 전파를 통해 신호 전달, 크기, 주파수, 파장이 변화
  - 디지털 통신은 체널의 특징 분석, 왜곡을 일으키는 양을 미리 제거하여 체널을 안정화
3. 소프트웨어에 의해 제어가 가능
  - 아날로그의 경우 새로운 서비스 변경을 하려면 하드웨어 변경이 필수적이었음
4. 어떤 형태의 신호도 전송이 가능
  - 음성, 데이터, 영상 등 모든 신호 전송이 가능
5. 효율성이 뛰어남
  - 아날로그 이동통신보다 10배 이상의 체널을 사용, 10배의 주파수 자원 효율성을 지님
6. 보안
  - 임의의 데이터를 추가 또는 변경하였다가 수신 시에 이를 복원함으로써 복구가 쉬움

### 디지털 통신의 데이터 전송 용량
- 셰넌의 체널 용량 공식
![shannon](../../images/shannon.png)
- C: 체널의 전송 용량
- B: 주파수 대역폭
- S: 신호 전력
- N: 잡음 전력
- 즉, 대역폭이 넓고 전력이 세며 잡음이 낮을 수록 전송 용량이 커진다.

### 디지털 통신 기술
- 아날로그 신호를 디지털 신호로 변환하는 기술
- 높은 주파수로 디지털 신호를 변조하는 기술
- 변조된 신호를 멀리 보낼 수 있도록 증폭하는 기술
- 디지털 신호를 원래의 아날로그 신호로 변환하는 기술 등

### A-D 변환(Analog to Digital)
- 표본화, 양자화, 부호화 3단계로 이루어짐
- 표본화
  - 모든 시간에 정보 대신 일부 시간의 표본값만 추출
  - 목소리의 경우 1초당 8천개의 샘플을 추출
- 양자화
  - 아날로그 신호의 세기를 디지털 신호의 세기로 만듬
  - 목소리의 경우 256 레벨 중 1개로 선택
- 부호화
  - 디지털 신호의 세기를 디지털 부호로 만드는 과정
  - 목소리의 경우 세기 레벨(0~256)을 8비트로 표현이 가능
  - 각 레벨을 2진수로 표현하고 이를 이어붙여 비트 스트림 생성이 가능
  - 목소리의 경우 8000 x 8이므로 64kbps가 된다.

### 원천 부호화 (Source Coding)
- 아날로그가 디지털화 신호 또느 디지털 신호를 압축하여 주파수 이용 효율을 높일 ㅅ ㅜ있다.
- Coding, Decoding으로 구성되며 이 둘을 합쳐서 CODEC이라 부른다.

### 체널 부호화
- 정보 데이터에 추가적으로 에러 체크를 위한 비트(패리티 비트)를 삽입하여 에러를 찾고 정정하는 것
- 원천 부호하 방식에 의해 줄어든 데이터에 추가 데이터를 넣어주게 된다.

### 인터리빙
- 페이딩이 발생하면 연속된 여러개의 데이터를 동시에 잃게 되는 집중 에러(Burst Error)가 발생
- 이 경우 에러 복구가 어려워진다.
- 산발적으로 에러가 발생하는 임의 에러 형태로 에러 발생을 분산시켜 복구 능력을 유지시켜 주는 기술이 인터리빙이다.

### 변조와 복조
- 모뎀: 변조(Modulation)과 (Demodulation)의 줄임말
- 목소리를 전송하기 위해서는 저주파수 대인 목소리의 주파수를 높여 안테나로 전송하고(modulation) 이를 다시 저수파수 대역으로 낮춰 듣게된다.(demodulation)

### 다중 접속 및 다중화(Multiplexing)
- 단말기들이 상호 간섭없이 경쟁적으로 기지국에 접속하기 위한 기술들
- FDMA, TDMA, CDMA, OFDMA 등 여러 방식이 있다.
- FDMA
  - 시간을 고정, 단말기 별로 주파수를 분할, 아날로그에서 많이 사용
- TDMA
  - 주파수를 고정, 시간을 slot 단위로 분할, 주파수 재사용 계수를 3~4까지 줄여 가입자 수용 용량을 2~3배 증가시킴
- CDMA
  - 셀룰러 주파수의 전 체널에 걸쳐 다수의 통화가 가능하도록 설계 (아직 잘 이해를 못함)
- OFDMA
  - 여러 개의 반송파를 한 사람에게 할당, 고속 데이터 전송이 가능하도록 설계, LTE 등에서 사용(아직 잘 이해 못함)

### 대역확산
- 신호를 간섭으로부터 보호하기 위해 우너래의 신호를 여러 주파수 대역을 나누어 전송하는 것
- 각 주파수 전력을 줄일 수 있음
- 여러 주파수 가운데 하나를 수신하지 못하더라도 원래의 신호를 복원 가능

### 듀플렉스
- 순방향 / 역방향 링크 구분을 위한 기술
- FDD: 역방향을 낮은 주파수에 할당
- TDD: 순방향, 역방향 시간 길이를 조정하여 서비스를 제공
