### 프로세스 개념
- 프로그램: 저장장치에 저장되어 있는 정적인 상태
- 프로세스: 메모리에 올라와서 실행되는 동적인 상태

### 프로그램에서 프로세스로의 전환
- 프로세스는 컴퓨터 시스템의 작업 단위로 테스크라고도 부름
- 프로그램을 메모리에 올리고, 프로세스 제어 블록 (PCB)를 만든다.
- PCB는 운영체제 레벨에서 프로스세를 제어하기 위해서 사용된다.

### PCB
- 프로그램이 프로세스가 되려면 메모리에 올라가는 동시에 PCB가 생성되어야 한다.
- 운영체제가 해당 프로세스를 위해 관리하는 데이터 구조이므로 운영체제 영역에서 만들어진다.
- 즉, 프로세스 = 프로그램 + 프로세스 제어 블록
- PID: 개별 프로세스를 구분하기 위한 ID
- 메모리 관련 정보: CPU는 실행하고자 하는 프로세스가 메모리 어디에 저장되어 있는지를 알아야함. 이를 위해서 PCB 내부에 프로세스 메모리 위치 정보를 저장.
- 각종 중간값: PC, 작업 중간값 저장 레지스터 등

### 프로세스의 다섯가지 상태
- creat: 프로그램이 메모리에 올라오고 운영체제로부터 PCB를 할당받은 상태
- ready: ready queue안에서 자기 순서를 기다리는 상태. CPU 스케쥴러에 의해 관리
- running: CPU의 할당을 받아 실행되는 상태, 자신에게 주어진 time slice 동안 작업
- blocking: 작업 실행 도중 IO를 요청하면 실행을 멈추고 io 작업을 대기. 이 때 입출력장치별로 마련된 큐에서 대기. 들어가게 되며 io 작업이 완료되면 다시 ready queue로 이동
- terminate: 프로세스가 종료된 상태

### 특별한 프로세스의 상태
- pause: 프로세스가 작업을 일시적으로 쉬고 있는 상태
- suspend: 프로세스가 메모리에서 잠시 쫓겨난 상태

### 컨텍스트 스위치
- CPU가 특정 프로세스의 작업을 처리하다가 멈추고 다른 프로세스의 작업을 처리하는 과정
- PCB 교체 작업이 발생
  - 1. CPU가 먼저 P1을 실행하고 있다가 타임아웃이 발생
  - 2. P1의 상태를 PCB 1에 저장, PCB 2에서 P2의 상태를 가져옴
  - 3. P2를 실행하다가 역시 타임아웃 발생
  - 4. P2의 상태를 PCB 2에 저장, PCB 1에서 P1의 상태를 가져옴
- 인터럽트 발생 시에도 컨텍스트 스위치는 발생 가능하다.

### 프로세스의 구조
- 코드, 데이터, 스택 영역으로 구성
- 데이터 영역은 일반 데이터 영역과 힙 영역으로 구성
- ex) 워드 프로세스 프로그램을 실행한다면 프로그램 자체는 코드 영역에, 편집 중인 문서는 데이터 영역에, 운영체제가 워드프로세서를 작동하기 위해 사용하는 각종 부가 데이터는 스택 영역에서 관리
- 코드 영역: 프로그램 본문 저장
- 데이터 영역: 변수, 파일 등 각종 데이터 모든 곳
- 스택 영역: 함수 호출 시 리턴 주소 저장, 운영체제가 프로세스를 작동하기 위해 유지하는 영역으로 사용자에게 보이지 않음.

### 프로세스 생성과 복사
- fork() 시스템 콜을 사용하여 새로운 프로세스를 복사함
- fork 수행 시 부모 프로세스의 경우엔 리턴 값이 자식 프로세스의 PID, 자식 프로세스의 경우엔 -1
- fork 수행하여 프로세스를 복사한 다음, exec 시스템 콜을 호출하여 프로세스의 내용을 교체

### 유닉스 프로세스 계층 구조
- 부팅 시에 커널 관련 프로세스를 여러개 만들고 여기서 init 프로세스가 전체 프로세스의 출발점이 된다.
- 다른 모든 프로세스들은 init 프로세스의 자식으로 만든다.

### 쓰레드
- 프로세스의 코드에 정의된 절차에 따라 CPU에 작업을 요청하는 실행 단위
- 한 프로세스 내부의 쓰레드들은 프로세스의 코드, 데이터, 힙 영역을 공유
- 쓰레드 컨텍스트 스위치 시에는 PCB를 교체할 필요가 없으며 이 경우 캐시 메모리를 활용할 수 있어서 프로세스 스위치보다 오버헤드가 적다.
- 멀티 쓰레드의 단점으로는 동일한 자원에 여러 쓰레드가 동시에 접근하는 레이스 컨디션을 신경써주어야 하며, 동기화 처리를 해주어야 한다.
- 또한 하나의 쓰레드가 예외를 일으켜 프로세스가 종료될 경우 전체 쓰레드가 동작을 멈춘다는 점이 있다.

### 멀티 프로세스 vs 멀티 쓰레드
- 익스플로어러는 멀티 쓰레드 방식, 크롬은 멀티 프로세스 방식
- 익스플로어러에서는 여러 화면들 중에 하나가 문제가 생기면 전체가 종료 됨
- 따라서 어느 기법이 항상 우세하다기 보다는 상황에 적합한 방식을 선택하면 됨

### 멀티 쓰레드 모델
- 커널 쓰레드: 커널이 직접 생성하고 관리하는 스레드
- 유저 쓰레드: 라이브러리에 의해 구현된 일반적인 스레드

### 유저 레벨 스레드
- 운영체제가 멀티 스레드를 지원하지 않을때 사용하는 방법
- 실제 커널 레벨에서는 단일 쓰레드로 동작 (1 to N)

### 커널 레벨 쓰레드
- 커널이 멀티 쓰레드를 지원 (1 to 1)
- 멀티코어 활용이 가능

### 프로세스의 동적 할당 영역 (heap)
- 정적 할당 영역에는 코드, 데이터가 속함
- 동적 할당 영역에는 힙과 스택이 속함. 프로세스 런타임에 만들어지는 영역
- 스택
  - 함수 호출시 완료되면 되돌아올 주소 값을 저장
  - 함수 호출 시에만 할당되고 사용되는 지역 변수를 스택에 저장
  - 프로세스를 작동하기 위해 커널이 유지하는 자료 구조
  - 쓰레드 별로 스택이 할당됨
- 힙
  - malloc에 의해서 프로그램 런타임에 크기가 결정되어 메모리에 할당되는 변수들을 저장하는 영역
  - 처음부터 크기를 결정하여 정의한 변수는 데이터 영역에 저장되며 프로세스 종료 시까지 메모리를 차지
  - malloc으로 할당한 변수는 필요 없어지면 free 함수로 메모리 영역을 반환 가능
  - 예를들어 워드 프로세스의 경우 문서를 편집하는 공간을 배열로 만든다면 사용자가 얼마나 큰 문서를 만들지 알 수 없기 때문에 사전에 배열의 크기를 알 수 없음. 


