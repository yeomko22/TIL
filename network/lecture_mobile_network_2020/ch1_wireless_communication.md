### 무선 통신 발전의 역사
- 1860 맥스웰 방정식, 전자기파의 발견
- 1880 헤르츠, 무선전송 실험 성공
- 1895 마르코니, 30Km 떨어진 곳에 디지털 신호 전송 성공
- 1938 Federal Communication Commision, rules for radio telephony 제정
- 1946 뉴욕에 기지국을 설치하고 무선 통신 제공, 543명 수용 가능
- 1979 1G 시스템 등장 (일본)

### 1G 특징
- 대표 표준: AMPS
- 동시 접속 기술: FDMA
- 특징
  - 아날로그를 사용, 통화 품질이 좋지 못하고 수용 가능 인원이 적다.
  - 오로지 전화를 위해서 탄생

### 2G의 등장
- 대표 표준: IS-95, GSM(현재도 유럽에서 사용)
- 동시 접속 기술: TDMA, CDMA
- 특징
  - 디지털을 사용, 수용 가능 인원이 확늘어남. 통화 서비스의 대중화
  - 문자, 이메일 등의 서비스가 가능하였으나 여전히 통화 위주의 서비스
  - 일반인들이 핸드폰을 사기 시작

### 3G의 등장
- 대표 표준: CDMA2000(IS-95의 진화), WCDAM(GSM의 진화)
- 동시 접속 기술: CDMA
- 특징
  - 사실상 WCDMA가 글로벌 표준으로 자리잡음
  - 데이터 서비스가 일반화 되었으나 킬러 컨텐츠나 단말기가 뒷받침되지 못하였다.
  - 사용자 수가 많지 않아서 이동통신사 측에서도 기지국을 천천히 깜
  
### 4G의 등장
- 대표 표준: LTE(3.9G), LTE-A
- 동시 접속 기술: OFDM(Orthogoal Frequency Division Multiplexing)
- 특징
  - 2GHz 근방의 대역을 사용
  - 20MHz 정도의 대역폭을 사용
  - IMT-Advanced는 피크 전송률을 1Gbps를 요구했는데 LTE가 이를 못맞춰서 3.9G라 부름
  - 당시 킬러 컨텐츠와 단말기가 갖춰진 상태에서 표준이 도입된 거라 폭발적인 인기를 누림
  - 이후 LTE-A가 등장하며 진정한 의미의 4G 표준안으로 자리잡음
- LTE 핵심 기술
  - Carrier Aggregation(CA)
  - MIMO: 다수의 안테나로 단말기와 기지국이 통신하는 것
  - OFDM

### 5G의 등장
- 대표 표준: 아직 없음
- 특징
  - eMBB(enhanced mobile broadband): 초고속
  - uRLLC(ultra reliable low latency communication): 초저지연, 초신뢰
  - mMTC(massive machine type communication): 초연결
- 적용 분야
  - eMBB: VR
  - uRLLC: Self Driving
  - mMTC: Smart City
- 한계점
  - 킬러 컨텐츠가 없다. 그래서 소비자들의 관심을 이끌어내고 있지 못하다.
- 5G의 8가지 KPI
  - peek data rate: 20Gbps
  - user experienced data rate: 100Mbps
  - spectral efficiency: 30Mbps
  - mobility: 500km/h
  - latency: 1ms
  - devices/km: 1000000
  - energy efficiency
  - area traffic capacity

### 5G의 핵심 기술
- massive MIMO: 기지국에 100개 이상의 안테나를 설치
- mmWave: 28GHz 주파수를 사용, 이 때의 파장이 약 10mm, 그래서 이 주파수 대역을 mmWave라 부른다.
- mmWave 대역을 사용하면 안테나의 길이가 줄어들고, 이를 통해 massive MIMO 구현이 가능하다.
- massive MIMO로 대용량 컨텐츠의 초고속 전송이 가능해진다.
- 높은 주파수일 수록 직진성이 강해지고 감쇄 현상이 일어난다. 그래서 기지국을 촘촘하게 깔아야 한다.
- 5G에서는 셀 하나에 3.5GHz 대역의 기지국을 설치하고, 그 안에 28GHz 대역의 기지국을 설치하는 Heterogeneous Network를 구성한다.

### Wifi
- L1, L2(physical, data link) 레이어에 해당하는 표준안
- IEEE 802.3(이더넷) 유선 네트워크를 무선망으로 만들어보자는 시도에서 탄생
- IEEE 802.11(wifi) 등장
- 점차 진화하여 2012 802.11ax(wifi6) 등장
- 2.4GHz와 5GHz를 제공

### bluetooth
- wifi에 자극을 받아서 등장
- 초기에는 마우스, 키보드 등을 무선화, 이 당시에는 1Mbps 속도로 음악 재생이 불가능
- 이후 음악 전송까지 가능한 bluetooth EDR(enhanced data rate)
