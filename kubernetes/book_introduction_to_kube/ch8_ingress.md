### Ingress
- 클러스터 외부에서 안으로 접근하는 요청들을 어떻게 처리할지 정의해둔 규칙들의 모음
- 클러스터 외부에서 접근할 수 있는 URL 제공
- 트래픽 로드 밸런싱
- SSL 인증 처리
- 도메인 기반 가상 호스팅 제공
- Ingress 자체는 이런 규칙들을 정의해둔 자원이고 실제 동작하는 것은 Ingress Controller이다.

### Ingress 주의점
- 예제 코드와 실제 동작하는 코드가 약간 다르다.
- 특히 annotations의 rewrite-target은 직접 최신 예제 코드를 보고 적용해야한다.
- ingress controller 설치는 로컬 환경에 설치하는 것과 클라우드 환경에 설치하는 것이 다르므로 주의할 것
- SSL 적용은 추후에 개인 프로젝트 마무리 단계에서 적용해보는 것으로 한다.

### 무중단 배포시에 주의점
- 새로운 파드가 뜨면 이를 감지해서 트래픽의 방향을 바꿔주는 역할을 Ingress가 수행한다.
- 이 때 무중단 배포를 구현하기 위해서 설정해주어야 할 값들이 있다.
- maxSurge, maxUnavailable
  - maxSurge: 디플로이먼트에 기본 설정된 파드 개수에 여분의 파드를 몇개 더 만들 수 있는지 설정
  - maxUnavailable: 디플로이먼트를 업데이트 하는 동안에 몇 개의 파드를 이용할 수 없어도 되는지
  - 이 둘을 적절히 조절하여 항상 일정 개수 이상의 파드를 이용할 수 있어야 함
- readinessProbe 지원 여부 확인
  - 쿠버네티스는 livenessProbe, readinessProbe 두 가지 방식으로 파드 진단
  - 무중단 배포 시에는 readinessProbe를 신경써야함
  - 컨테이너가 서비스 요청을 처리할 준비가 되었는지 진단
  - 자바 프로세스의 경우에는 실행하고 나서 초기화 과정이 길기 때문에 readinessProbe 과정이 중요
- 컨테이너 안에 그레이스풀 종료 설정
  - kubectl이 새 파드를 띄우고 이전 파드 종료시에는 SIGTERM 신호를 보낸다.
  - 만일 그대로 컨테이너가 종료된다면 기존에 수신한 요청을 완료하지 못하는 상황이 발생한다.
  - kubelet은 SIGTERM 신호를 보낸 뒤 일정 시간 동안 그레이스풀 종료가 되지 않으면 강제로 SIGKILL을 보내어 종료함
  - 그러므로 컨테이너 내부에서 SIGTERM을 무시하도록 설정해주어야 함

  ### 무중단 배포 구현
  - deployment 설정 파일 작성 시에 배포 전략 설정
  ```
  spec:
    strategy:
      rollingUpdate:
        maxSurge: 25%
        maxUnavailable: 25%
      type: RollingUpdate
  ...
  template:
    spec:
      containers:
        - image: ~
          livenessProbe:
            httpGet:
              path: /liveness
              port: 5000
          readinessProbe:
            httpGet:
              path: /readiness
              port: 5000
  ```
