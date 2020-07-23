## 3장 전파란 무엇인가
### 전파, 주파수, 신호
- 전파: 인공적 매개물이 없이 공간에 전파하는 3000GHz 보다 낮은 주파수의 전자파
- 무선 통신에 사용하는 낮은 주파수 대를 포함하여 적외선, 가시광선, 자외선, X선, 우주선을 총칭

### 전파 용어
- 파동: 전파가 진행하는 움직임
- 파장: 하루에서 마루까지 거리
- 마루: 파동이 진행하면서 그 위치가 가장 높은 곳
- 골: 가장 낮은곳
- 진폭: 마루나 골의 깊이
- 주기: 한번 진동에 소요되는 시간, 마루에서 마루까지, 골에서 골까지 소요되는 시간
- 파동은 위아래로 전달되는 횡파와 좌우로 전달되는 종파가 있다.

### 주파수
- 헤르츠를 사용, 1초에 1번 진동하면 1Hz
- c(전파 속도) = f(주파수) x λ(파장)
- 이때 전파의 속도는 빛의 속도로 고정
- 그러므로 주파수가 높아질 수록 파장이 짧아진다.
- 파장이 짧아질 수록 안테나 길이가 짧아진다.
- 주파수가 높을 수록 대량의 데이터 전송이 가능해진다.

### 왜 주파수가 높을 수록 대량의 데이터 전송이 가능한 걸까?
- 대량의 데이터 전송 시에는 넓은 대역폭이 필요
- Mhz 주파수 대역에서 10Mhz 확보하는 것과 Ghz 대역에서 10Mhz 대역을 확보하는 것 중에 후자가 쉽다.
- 대용량 데이터를 보내기 위해서 고주파 대역으로 옮겨가고 있다.
- 1Hz가 2비트를 보낼 수 있다. 1.25Mhaz 대역폭을 사용할 경우 최대 3Mbps를 전송
- 20 MHz 대역폭을 이용하는 LTE의경우 100Mbps 이상의 데이터 전송이 가능
- 즉, 고주파일 수록 더 많은 비트 전송이 가능하며 대역폭을 확보하기에도 쉽다.

### 무선통신에 사용하는 전파
- 3kHz부터 3000GHz 사이의 주파수 대역의 전파를 무선 통신에 사용
- 파장 범위는 0.1mm에서 10km, 전기 진동(전류 변화)로 인해서 발생
- 전기는 자계를 만들고, 자계는 전기를 만든다.

### 전파의 확산
- 도선에 전류가 흐르면 자계가 발생
- 자계에 의해 전계가 발생
- 이 둘은 상호 수지그올 발생하게 됨
- 폐곡선을 그리면서 자유 공간으로 전파하게 된다.
- 전파는 직진하거나 반사하거나 굴절한다.
- 주파수가 높은 전파일 수록 직진성이 강하며, 감쇠 현상이 쉽게 일어난다.

### 그 외 전파의 특성
- 전파의 회절: 장애물이 있으면 돌아간다.
- 전파의 간섭: 서로 다른 두 전파가 서로 상쇄되거나 합쳐진다.
- 전파의 편파: 상하로만, 좌우로만 진동하는 전파를 걸러낼 수 있는 특성
- 전파의 감쇠: 일정한 거리를 진행할 수록 저파의 세기가 줄어든다. 전파의 세기는 데시벨(dB) 단위로 측정한다.
- 페이딩: 외부 물체가 지나갈 때 전파가 커지거나 작아지는 현상, 순간적으로 통화가 끊어지는 경험.
- 도플러 효과: 송신점의 주파수와 수신점의 주파수가 정지 상태에서 동일하다가 이동할 경우 주파수가 달라지는 현상, 멀어지는 물체일 수록 주파수가 늘어진다.

### 전파의 전달 형태
- 지상파: 직접파, 대지반사파, 지표파, 회절파 등 지표면과 가까운 거리에서 전파를 전달, 지상파 tv의 어원
- 공간파: 성층권, 중간권, 열권 등 대기권 위를 통해서 전파를 전달하는 방법