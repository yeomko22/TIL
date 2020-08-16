### proxy
![proxy](../../images/proxy.png)
- 클라이언트와 서버 사이에서 클라이언트 인증을 할 필요가 있다. 이를 Customer Management 단에서 해주기 보다는 클라와 서버 중간에서 인증만 담당하는 별도의 모듈을 활용하여 처리하는 것이 바람직하다. 이처럼 클라이언트가 직접적으로 서버에 요청을 보내지 않고 중간에 다른 모듈을 통해서 요청을 보내도록 하는 것을 프록시라고 부른다.
- client 입장에서는 서버에 곧바로 요청을 하나, 프록시를 통해 요청하나 똑같은 동작을 수행하게 된다. 그러나 프록시는 그 중간에서 서버에 작업을 요청하기 전, 혹은 후에 특정한 로직을 수행하게 된다.
- 스프링은 모든 종류의 통신에 이러한 프록시를 적용한다.

### Envoy
- istio의 proxy는 envoy라는 오픈소스 프록시 프로젝트에 기반한다. envoy는 istio의 주요 컴포넌트 중 하나이다.
- istio에서 주로 사용하는 envoy의 특징은 circuit breaking, tracing이다.
- envoy 대신 istio를 써야만 하는 이유가 있는가? envoy만 써도 서비스 매쉬 구현이 가능하다. 그러나 쿠버네티스에 맞게끔 사용하려면 너무 어렵다. 
- istio를 사용하면 kubernetes yaml 파일을 통해서 envoy 설정을 할 수 있다. 즉, kubernetes yaml을 작성하면 이를 envoy configuration file로 자동 변환 해준다.
- 정리하자면 envoy는 다양한 형태의 클러스터에 배포될 수 있다. 하지만 kubernetes에 맞게끔 적용하기 위해서는 해야할 일들이 많다. istio는 중간에서 이 작업을 대신해준다.
- istio에서 각 파드들에 배포되어 있는 프록시 컨테이너를 data plane이라 부른다.

### Istio Control plane
![istio_architecture](../../images/istio_architecture.png)
- 각 파드에 proxy가 배포되어 있으며, 이를 통해서 파드 안의 컨테이너에 트래픽이 전달된다. 프록시 간에는서로 통신이 가능하며 이를 mesh traffic이라 부른다.
- control plane에는 istiod라는 파드 안에 pilot, citadel, galley라는 컴포넌트가 들어있다.

### Control Plane - Galley
- kubernetes yaml 파일을 읽어와서 이를 istio가 이해할 수 있는 형태로 변환해준다. 이는 즉, istio가 kubernetes가 아닌 환경에서도 동작할 수 있다는 의미이다. 그러나 istio를 사용할 때 galley를 직접 만지게 될 일은 없다.

### Control Plane - Pilot
- pilot은 envoy가 이해할 수 있는 포맷으로 설정을 변경해주는 역할을 수행한다. 그리고 프록시들에게 이러한 설정을 주입해준다.

### Control Plane - Citadel
- 프록시들의 TLS certificate를 관리해주는 역할을 수행한다. galley나 pilot과는 통신하지 않는다. 즉, 클러스터 내부에서 TLS/SSL 통신을 할 수 있다. 

### Istiod
- 현재는 galley, pilot, citadel이 istiod 안에 묶여있으며 istiod는 하나의 파드로 쿠버네티스 클러스터에 뜨게 된다.
