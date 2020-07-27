### Multi Container
- micro service architectur: 큰 서비스를 쪼갠다.
- 그런데 때때로 두 서비스가 같이 동작해야 할 때가 있는데 Web Server와 Log Agent가 그러하다.
- 스케일 아웃을 하더라도 함께 배포되길 바라며, 네티워크와 스토리지를 공유하길 바랄 수 있다.
- 이럴 때 파드 하나에 여러 컨테이너를 묶어서 배포한다.

### MultiContainer 디자인 패턴
- sidecar: 기본 컨테이너의 기능을 확장하거나 강화하는 용도의 컨테이너를 추가하는 패턴, 로그 수집 컨테이너가 대표적
- adapter: 파드 외부로 노출되는 정보를 표준화 하는 역할, 주로 모니터링 지표를 어댑터 컨테이너를 통해 표준화 된 형식으로 노출시키고 외부 모니터링 시스템에서 그 데이터를 주기적으로 가져가서 모니터링에 이용
- ambassador: 파드 내 프록시 역할을 하는 컨테이너를 추가하는 패턴, 파트 외부에서 접근 시 프록시를 통함. 파드의 트래픽을 더 세밀하게 조정이 가능. 서비스 매시용 오픈소스 이스티오가 이러한 패턴으로 구성 됨

### init Container
- 외부 저장소에서 소스코드를 받아오고 종료되는 프로세스를 파드 시작 시점에서 실행시키고 싶을 수 있다.
- 일반적인 컨테이너라면 파드의 생명주기 동안에 동작함을 보장해야 한다.
- 따라서 이러한 경우 initContainers를 사용한다.
```
apiVersion: v1
kind: Pod
metadata:
  name: myapp-pod
  labels:
    app: myapp
spec:
  containers:
  - name: myapp-container
    image: busybox:1.28
    command: ['sh', '-c', 'echo The app is running! && sleep 3600']
  initContainers:
  - name: init-myservice
    image: busybox
    command: ['sh', '-c', 'git clone <some-repository-that-will-be-used-by-application> ; done;']
```
- initContainers라는 필드 아래에 일반 컨테이너 설정해주듯이 똑같이 해주면 된다.
- 파드 생성 시점에서 initContainer가 실행되고, 일반 컨테이너가 실행되기 전에 종료된다.
- 여러개의 initContainer를 설정 시에 순차적으로 한번만 실행된다.
