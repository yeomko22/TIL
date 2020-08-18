### telemetry requirement
- 각 파드마다 envoy sidecar proxy가 동작하고 있어야한다.
- control plane이 동작중이어야 한다.(Telemetry)
- telemetry를 동작시키기 위해선 istio yaml 설정이 필요하지 않다.
- Virtual Service나 Gateway같은 오브젝트는 트레픽 제어에 사용된다.

### virtual service란?
- custom routing rules를 서비스 매쉬 내에서 정의할 수 있도록 해주는 것
- 하나의 서비스에 여러 파드를 연결하면 쿠버네티스 서비스는 자동으로 로드 밸런싱을 적용한다.
- virtual service는 프록시들을 설정한다. virtual service를 설정하면 pilot은 모든 프록시들에 virtual service를 전달한다.
- virtual service는 service를 대체하는 것이 아니다. 여전히 함께 사용해야한다. service discovery에 사용된다.
- istio에서는 프록시들끼리 통신을 한다. 따라서 다른 형태의 service가 필요한 것이며, 이를 virtual service라는 형태로 구현한 것이다.
- 외부에서 클러스터 내부로 트래픽이 들어오는 것을 허용하는 gateway와 virtual service의 yaml은 아래와 같은 형태를 갖는다.
```
apiVersion: networking.istio.io/v1alpha3
kind: Gateway
metadata:
  name: bookinfo-gateway
spec:
  selector:
    istio: ingressgateway # use istio default controller
  servers:
  - port:
      number: 80
      name: http
      protocol: HTTP
    hosts:
    - "*"
---
apiVersion: networking.istio.io/v1alpha3
kind: VirtualService
metadata:
  name: bookinfo
spec:
  hosts:
  - "*"
  gateways:
  - bookinfo-gateway
  http:
  - match:
    - uri:
        exact: /productpage
    - uri:
        prefix: /static
    - uri:
        exact: /login
    - uri:
        exact: /logout
    - uri:
        prefix: /api/v1/products
    route:
    - destination:
        host: productpage
        port:
          number: 9080
```
