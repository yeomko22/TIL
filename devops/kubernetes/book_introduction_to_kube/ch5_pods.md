### 파드란?
- 서로 관련성이 높은 컨테이너들을 묶어서 관리하는 단위
- 컨테이너들이 같은 목적으로 자원을 공유
- 웹 서버, 로그 수집기, 볼륨 컨테이너 이렇게 묶어서 구성
- 파드 안의 컨테이너들은 IP를 공유하며, 파드 안에서 각 컨테이너들은 포트로 구분된다.

### pod lifecycle
- pending: 쿠버네티스 시스템에 파드를 생성 중
- running: 파드 안 모든 컨테이너가 실행 중인 상태
- succeeded: 파드 안 모든 컨테이너가 정상 실행 종료된 상태, 재시작 안함
- failed: 파드 안 모든 컨테이너 중 정상적으로 실행 종료 되지 않은 컨테이너가 있는 상태
- unknown: 파드의 상태를 확인할 수 없는 상태. 파드가 있는 노드와 통신할 수 없을 때

### kubelet의 컨테이너 진단
- livenessProbe: 컨테이너가 실행 됐는지 확인, 실패시 컨테이너를 재시작
- readinessProbe: 컨테이너가 실행된 후 실제로 서비스 요청에 응답할 수 있는지를 진단. 실패시 엔드포인트 컨트롤러는 해당 파드에 연결된 모든 서비스들을 대상으로 엔드포인트 정보 제거
- 이 두 가지 프로브를 제공하는 것이 쿠버네티스의 장점
- 즉, 켜졌다고 바로 트래픽을 받는 것이 아니라, 트래픽을 받을 준비가 돼었는지 확인 후 트래픽 전달

### 초기화 컨테이너
- 앱 컨테이너가 실행되기 전에 파드를 초기화
- 보안상 이유료 앱 컨테이너 이미지와 같이 두면 안되는 소스코드 별도로 관리시에 유용
- 파드 초기화 시에 Imperative하게 특정 명령어들을 수행하는데 유용
- config 파일의 spec 아래에 initContainers로 생성이 가능
- pod 생성 전에 해당 컨테이너들을 실행하는 것

### 인프라 컨테이너
- 모든 파드에서 항상 실행되는 pause라는 컨테이너가 있으며, 이를 infra container라 부른다.
- pause는 파드 안 기본 네트워크로 실행, PID 1로 설정, 다른 컨테이너의 부모 컨테이너 역할을 수행

### 스태틱 파드
- kube-spiserver를 통하지 않고 kubelet이 직접 실행하는 파드들이 있다.
- kubelet 설정에서 --pod-manifest-path 옵션에 디렉터리를 지정하고, 파드를 넣어두면 kubelet이 이를 감지해서 파드로 실행
- kube-apiserver, etcd 같은 시스템 파드를 실행하는 용도로 많이 사용함

### 파드에 CPU와 메모리 자원 할당
- 특정 노드의 리소스는 남고, 특정 노드의 리소스는 부족한 상황이 발생 가능
- 파드 설정 시에 파드 안의 각 컨테이너가 CPU와 메모리를 얼마나 사용할 수 있을지 지정 가능
- yaml 파일에서 limits와 requests 옵션을 지정해서 설정이 가능함
- spec.containers[].resources.limits.cpu: 최대 사용 가능량
- spec.containers[].resources.limits.memory: 최대 사용 가능량
- spec.containers[].resources.requests.cpu: 최소 자원 요구량
- spec.containers[].resources.requests.memory: 최소 자원 요구량

- requests에 적혀있는 요구량을 만족하는 노드에 파드를 스케쥴링 함
- 만일 requests를 만족하는 노드가 없다면 파드는 pending 상태로 넘어가지 못함
- limits는 특정 컨테이너의 리소스 사용량을 제한하는 필드로 노드 안의 리소스를 특정 컨테이너가 모두 가져가는 것을 예방

### 파드 구성 패턴
- 사이트카 패턴
  - 원래 사용하려던 기본 컨테이너의 기능을 확장하는 용도로 컨테이너를 추가
  - 웹 서버 컨테이너가 들은 파드에 로그 수집 컨테이너를 추가하고, 파일 시스템을 통해서 데이터 전달
- 앰버서더 패턴
  - 파드 안에 프록시 역할을 하는 컨테이너를 추가
  - 외부 세계와의 연결은 프록시가 처리, 원래의 웹 서버는 프록시하고만 통신
  - 이는 서비스 메쉬용 오픈 소스인 Istio에서 사용
- 어댑터 패턴
  - 파드 외부로 노출되는 정보를 표준화하는 어댑터 컨테이너를 사용
  - 어댑터 컨테이너로 파드의 모니터링 지표를 표준화한 형식으로 노출
  - 외부의 모니터링 시스템에서 해당 데이터를 주기적으로 가져가서 모니터링하는데 이용
  - 이는 모니터링 오픈 소스인 프로메테우스에서 사용

