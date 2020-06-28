### Load Balancer
- Service의 subtype
- 일종의 Legacy로 외부 트래픽을 클러스터에 전달해주는 역할을 한다.
- 특정 pod에 외부 트래픽을 전달해주는 역할을 하는 서비스
- 따라서 여러개의 팟을 외부에 노출시키고 싶다고 한다면 적절하지 못하다.
- 클라우드 서비스를 이용할 때에는 별도의 Load Balancer 서비스가 있고 이를 클러스터 내부로 연결하기 위해서 만들어진 서비스이다.

### Ingress
- ingress-nginx라는 프로젝트가 있고, 커뮤니티 주도로 만든 프로젝트다.
- kubernetes-ingress라는 프로젝트가 있고, nginx 회사가 주도로 만든 프로젝트이다.
- 두 개의 프로젝트 모두 nginx를 기반으로 한다.
- 두 개의 프로젝트는 완전히 별개로 kubernetes/ingress-nginx 프로젝트를 사용한다는 점에 주의하라
- ingress의 셋업은 GCP, AWS, Azure를 쓰느냐에 따라서 살짝씩 달라진다.

### Ingress Controller
- 우리가 원하는 상태로 오브젝트들을 맞춰주는 것을 쿠버네티스에서는 Controller라고 한다.
- 외부에서 들어으는 트래픽을 수신하여 라우팅해주도록 Ingress 오브젝트의 상태를 맞춰주는 config file을 작성한다.
![ingress_kubernetes](../../../images/ingress_kubernetes.png)
- kubernetes-ingress는 config file을 통해서 Ingress Controller를 만들고, 이 컨트롤러가 트래픽을 제어하는 팟을 만든다.
![ingress_nginx](../../../images/ingress_nginx.png)
- Ingress NginX는 config file을 통해서 바로 트레픽을 제어하는 팟을 만드는 차이가 있다.
- 해당 토이 프로젝트에서는 Ingress-nginx 프로젝트를 사용한다.

### Ingress Config
- yaml 파일에 모든 routing rule을 담는다.
- config file로 kubectl은 nginx pod을 생성한다.
- 이 pod에다가 Load Balancer Service를 붙여준다.
- 그리고 여기에 Google Cloud Load Balancer를 붙여서 외부 트래픽을 수신한다.
- 왜 Load Balancer Service에 자체 nginx로 만든 pod을 연결하지 않고 Ingress config파일을 통해서 만든 ingress-nginx를 연결하는 것인가? -> 그냥 nginx로 라우팅을 하면 ClusterIP Service를 지나쳐서 팟으로 바로 연결될 수 있다. 그러므로 Ingress를 사용하는 것이다.

### Ingress 설치
```
$ kubectl apply -f https://raw.githubusercontent.com/kubernetes/ingress-nginx/master/deploy/static/provider/cloud/deploy.yaml
```
- 먼저 ingress-nginx라는 Namespace를 만들어준다.
- 그 다음 default-http-backend라는 Deployment를 만들어주며, 이는 nginx pod이 제대로 작동하는지 healthcheck 등을 해주는 역할을 수행하며, 404 페이지 등을 서빙해주는 역할을 한다.
- 그 다음 default-http-backend의 서비스를 생성하고, 그 다음 ConfigMap 오브젝트를 생성한다. 이는 여러가지 설정 값들을 담고 있는 오브젝트이다.
- 그 다음 ServiceAccount 오브젝트를 생성하고 ClusterRole 오브젝트를 만들어서 전달한다. 그 이외에도 다양한 설정 값들을 제공하는 오브젝트를 생성한 뒤에 nginx-ingress-controller Deployment를 생성한다.

### Ingress Config File
- Ingress Service에서는 rules를 정하고 Service를 지정하면 된다.
- nginx conf를 작성하는 것과 유사하다.
