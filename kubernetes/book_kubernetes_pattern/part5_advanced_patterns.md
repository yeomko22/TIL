## 5부 고급 패턴
### 22장 컨트롤러
- 컨트롤러 패턴은 쿠버네티스 세트를 능동적으로 모니터링하고 요청한 상태로 유지 관리한다.
- 현재 애플리케이션 상태를 정기적으로 watch하고 reconcile하는 컨트롤러 컬렉션으로 구성된다.
- 선언적 API는 쿠버네티스에게 어떻게 작동해야하는지를 알려주기보다 상태가 어떻게 보여야 하는 지를 알려준다. 그리고 watch, event, reconcile 과정은 컨트롤러에 의해서 내부저긍로 수행된다.

### 컨트롤러
- 예를 들어 레플리케 세트 컨트롤러는 주기적으로 파드의 개수 변화를 주시하고, 이를 분석한다.
- 만일 요청된 상태와 현재 상태가 맞지 않는다면 API 서버에 요청을 보낸다.
- API 서버는 kubelet에게 명령을 내려 새로운 파드를 생성함으로써 상태를 복원한다.

### 오퍼레이터
- 더 정교한 차세대 컨트롤러
- CRD와 연동하는 정교한 reconcilation 프로세스
- 복잡한 애플리케이션 도메인 로직을 캡슐화하고 전체 애플리케이션의 수명 주기를 관리한다.

### 컨테이너 리눅스 업데이트 오퍼레이터
- 쉘 스크립트로 컨트롤러를 구성할 수 있다.
```
namespace=${WATCH_NAMESPACE:-default} // watch할 namespace 설정

base=http://localhost:8001 // 동일한 파드에서 실행되는 앰버서더 프록시를 통해 쿠버네티스 API에 접근
ns=namespaces/$namespace
curl -N -s $base/api/v1/${ns}/configmaps?watch=true
while read -r event // 컨피그맵 이벤트를 주시하기 위한 루프
do
  # ...
done
```

### 정리
- 컨트롤러는 관심 객체의 요청한 상태와 실제 상태를 알기 위하 관심 객체를 모니터링하는 능동적인 리컨실리에이션 프로세스다.
- 내부 컨트롤러와 마찬가지로 사용자 정의 컨트롤러를 개발하여 사용할 수 있다.

### 23장 오퍼레이터
- 오퍼레이터는 CRD를 사용해 애플리케이션에 대한 운영 지식을 알고리즘 및 자동화 된 형식으로 캡슐화하는 컨트롤러이다.
- 컨트롤러 패턴을 확장해 유연성과 표현력을 높일 수 있다.
- 사용자 정의 컨트롤러는 쿠버네티스 고유 자원만 보고 관리하므로 사용에 제한이 있다.
- 쿠버네티스 플랫폼에 추가 도메인 객체가 필요한 새로운 개념을 추가하고 싶을 수 있다.
- 만일 프로메테우스를 모니터링으로 채택한다면 여기에 필요한 설정 값들을 모두 모아서 쿠버네티스 자원으로 정의하고 싶을 수 있다. 이 때, 오퍼레이터를 사용해 쿠버네티스 API를 확장할 수 있다.
- 즉, 오퍼레이터란 쿠버네티스와 쿠버네티스 이외의 것들을 둘 다 이해하는 쿠버네티스 컨트롤러다.

### CRD
- CRD를 사용하면 특정 도메인 컨셉트를 관리하기 위한 목적으로 쿠버네티스를 확장할 수 있다.
```
apiVersion:apiextensions.k8s.io/v1beta1
kind: CustomResourceDefinition
metadata:
  name: prometheuses.monitoring.coreos.com
spec:
  group: monitoring.coreos.com
  names:
    kind: prometheus
    plural: prometheuses
  scope: Namespaced
  version: v1
  validation:
    openAPIV3Schema
  subresources:
    status: {}
    scale:
      specReplicasPath: .spec.replicas
      statusReplicasPath: .status.replicas
      labelSelectorPath: .status.labelSelector
```
- CustomResourceDefinition을 사용해서 정의
- 속하는 API group과 이름 등을 설정한다.
- subResource 아래에 status와 scale을 정의하여 사용이 가능하다. scale을 지정하면 CRD가 replica를 요청할 수 있다.
- CRD를 정의하면 아래처럼 자원을 생성할 수 있다.
```
apiVersion: monitoring.coreos.com/v1
kind: Prometheus
metadata:
  name: prometheus
spec:
  serviceMonitoringSelector:
    matchlabels:
      team: frontend
  resources:
    requests:
      memory: 400Mi
```
- 하지만 CRD만으로는 의미가 없으며 컨트롤러가 필요하다.

### 오퍼레이터란?
- operator는 쿠버네티스 애플리케이션을 packing, deploying, managing할 수 있는 방법
- CRD를 operator로 관리할 수 있다.
- stateful service를 배포하기에도 좋다.
- 예를 들어 operator를 이용해서 postgresql을 배포할 경우, create replica, initiate failover, create backups, scale 등의 작업을 수행한다.
- operator는 관리 측면에서 유용한 기능을 제공한다.
- coreos에서 제공하는 operator-sdk를 이용해서 golang 기반으로 operator를 개발할 수 있다.


