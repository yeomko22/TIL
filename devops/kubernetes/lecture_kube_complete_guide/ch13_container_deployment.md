### Updating existing object
- Declartive 방식으로 오브젝트를 업데이트 하려면 컨피그 파일을 수정하고 이를 apply 하면된다.

### config file
- 모든 config 파일은 name과 kind를 포함한다.
- 수정된 config file을 적용하면 kubectl은 name과 kind를 이용해서 노드들에서 현재 동작 중인 오브젝트를 찾아낸다. 그리고 변화를 반영한다. 

### 실행 중인 object의 세부 내용 검사하기
```
$ kubectl describe <object type> <object name>
ex)
$ kubectl describe pod client-pod
```

### Limitation of config file
- config file로는 업데이트 할 수 있는 필드 값이 제한되어 있다.
- Pod은 그 값이 극히 제한되어 있다.

### Object Types
- Pods: 서로 상관관계가 높은 컨테이너들을 묶어서 실행하는 오브젝트
- Services: Kubernetes Cluster에 네트워킹을 설정해주는 오브젝트
- Deployment: 동일한 pods들을 관리해주는 오브젝트로 현재 실행 중인 숫자나 설정 값들이 제대로 박혀있는 지를 관리한다.

### Pods와 Deployment 차이점
- Pods는 개발 환경에서 사용되며 설정 값 변경 등에 제약이 있다.
- Deployment는 하나 이상의 동일한 pods를 실행한다.
- 각각의 팟들을 모니터링 하고 설정 값 변경도 좋다.
- 개발로도 배포로도 훌륭하다.

### Deployment
- pod-template를 포함하며, 이는 다양한 설정값들을 포함할 수 있다. 이는 config file을 통해서 컨테이너의 설정 값을 변경할 수 있다.
```
apiVersion: apps/v1
kind: Deployment
metadata:
  name: client-deployment
spec:
  replicas: 1
  selector:
    metchLabels:
      component: web
  template:
    metadata:
      labels:
        component: web
    spec:
      containers:
        - name: client
          image: stephengrider/multi-client
          ports:
            - containerPort: 3000
```
- replicas: pods의 복사본을 몇개나 만들 것인가
- selector: Service에서의 selector와 유사한 역할을 한다. Deployment가 작동하는 방식은 먼저 Selector에 명시된 pod을 마스터가 생성하고, 이를 selector로 찾아내서 복사본도 만들고 관리도 하는 것. 반복처럼 보이지만 실은 역할이 다르다.

### why use service?
- 각각의 팟은 고유한 내부 IP를 부여받는다.
- 팟이 추가, 삭제, 업데이트 될 경우 IP가 변경될 수 있다.
- 따라서 팟의 IP로 직접 접속하게 되면 자주 변경되는 IP로 인한 장애를 겪을 수 있다.
- service는 selector에 부합하는 모든 pod들을 지켜보다가 IP 변화를 감지하고 이를 관리한다. 이러한 복잡성을 추상화해주는 역할을 수행한다.

### scaling and change configuration
- 설정 값을 변경해서 적용하면 기존의 pod을 제거하고 새로 만든다.

### triggering deployment update
- 쿠버네티스로 이를 구현하는게 어렵다!
- 업데이트를 하려면 config file에 변화를 주고, kubectl apply를 내려야 한다.
- 그런데 이미지의 버전이 업데이트 되어도 config file은 변화하지 않는다.
- 그러므로 kubenetes가 변화를 감지하지 못한다.
- 수동으로 업데이트하거나, 일일이 최신 이미지의 태그를 config file에 명시하는 것은 비효율적인 방법이다.
- 그나마 나은 방식은 kubectl 명령어를 통해서 imperative하게 컨테이너 버전 업데이트 명령어를 내려주는 것이다.

### container update
- 도커 이미지 빌드 시에 태그를 달아준다.
- kubectl 명령어를 이용해서 새 버전의 이미지를 배포한다.
- 나중에 클라우드 솔루션 이용하게 되면 이를 스크립트로 작성해서 자동화하므로 걱정하지 말 것!
