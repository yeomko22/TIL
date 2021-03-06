### Label
- key-value 쌍으로 구성
- metadata 태그 아래에 정의해서 사용 가능함
- label은 컨트롤러가 자신이 관리해야할 파드를 구분하는 역할로 사용
- 컨트롤러와 파드는 레이블을 통해서 느슨하게 연결됨 -> 유연한 구조
- label을 여러개 달 수도 있다.
```
labels:
  app: nginx
  environment: develop
  release: beta
```
```bash
$ kubectl get pods -l environment=develop
```
- 특정 라벨을 가진 파드들만 모아보는 명령어
- 라벨을 통해 일종의 조건문을 구현 가능

### Annotation
- key-value 쌍으로 구성
- 쿠버네티스 클라이언트나 라이브러리가 자원을 관리하는데 활용
- ingress-nginx에서는 에너테이션으로 nginx 설정 값들을 입력 가능
- annotation도 여러개 달 수 있으며 일종의 주석처럼 활용 가능

### 배포 방법
- 롤링 업데이트: 전체 파드를 한번에 교체하는 것이 아니라 일정 개수씩 교체하면서 배포, 디플로이먼트의 기본 배포 방식
- 블루/그린: 기존에 실행된 파드 개수와 같은 개수의 신규 파드를 모두 실행한 후 신규 파드가 정삭적으로 실행되면 트래픽을 한꺼번에 옮김 
- 카나리 배포: 소수의 파드만 새로운 버전으로 배포하고 실제 동작을 지켜본 다음 나머지 파드들도 업데이트 하는 배포 방식

### label을 이용한 카나리 배포
- 디플로이먼트에 라벨을 기본 라벨과 카나리 라벨 두 종류로 매겨준다.
- 서비스에서는 기본 라벨만 selector로 지정해주면 트래픽이 카나리 파드와 일반 파드에 골고루 나뉘어 들어간다.
- 카나리 파드에 새로운 버전이 컨테이너를 배포하고 지켜보다가 전체 파드를 업데이트 해주는 방식으로 카나리 배포를 구현할 수 있다.
