출처: IBM Cloud, https://www.youtube.com/watch?v=1iyFq2VaL5Y&t=9s

### Service Mesh란?
- micro service 간의 network를 말한다.

### istio 주요 기능
- load balancing
- fine grained control
- access control visibility
- visibility

### istio control plane
- pilot: istio의 service mesh를 실질적으로 관리하는 컴포넌트
- Citadel: 서비스 메쉬 내에서 사용하는 인증서를 관리
- mixer: 데이터 플레인에서 들어오는 데이터들을 한 곳으로 모아주는 역할, telemetry
