### Service란?
- 다른 애플리케이션 혹은 유저와 통신하는 것을 도와준다.
- 외부 유저와 프런트엔드 앱을 연결해준다.
- 프런트엔드 앱과 다른 애플리케이션을 연결해준다.
- 외부 데이터 소스와도 연결해준다.

### Service 구성
- 노드에 ip가 부여되고, 그 안에 파드가 떠있다.
- 외부 유저가 어떻게 노드 안의 파드에 통신을 하는가?
- 노드 안의 파드는 내부 IP가 부여된다.
- 노드 안의 파드에 접속하는 방법
  - 노드에 SSH 접속한 뒤, 파드의 IP에 접속한다.
  - 노드 IP에 접속한 뒤, 서비스를 통해서 파드에 접속한다. -> 쿠버네티스 서비스의 역할!
  - 포트를 개방해서 트래픽을 수신하고, 파드에 전달하는 서비스가 있다.(NodePort)

### Service Types
- NodePort: 외부에 포트 개방
- ClusterIP: 클러스터 내부용 가상 IP 부여되고
- LoadBalancer: 로드 밸런싱 수행

### NodePort
- 외부에 파드의 특정 포트를 개방하는 서비스
- 실제로는 3개의 포트를 사용한다.
  - targetPort: 파드가 사용하는 포트
  - Port: 서비스에서 파드로 연결되는 포트 
  - NodePort: 외부에 개방되는 포트

### NodePort 생성
```
apiVersion: v1
kind: Service
metadata:
  name: svc
spec:
  type: NodePort
  ports:
  - targetPort: 80
    port: 80
    nodePort: 30008
  selector:
    app: myapp
    type: front-end
```
- 라벨만 맞춰주면 하나의 서비스가 셀렉터 라벨에 맞는 여러 파드에 연결된다.
- 파드가 여러 노드에 나뉘어져 있다면? 아무 노드에 접속하더라도 동일한 서비스에 연결되고, 이를 통해서 파드들에 트래픽이 분산되게 된다.

### ClusterIP
- 서비스를 돌리기 위해서 다양한 종류의 파드들이 필요하며, 파드들 간에 통신이 필요하다. 이 때 파드들 간의 통신에 사용되는 것이 서비스가 ClusterIP이다.
- 이를 통해서 MSA 서비스 구현이 쉬워진다.

```
apiVersion: v1
kind: Service
metadata:
  name: back-end
spec:
  type: ClusterIP
  ports:
  - targetPort: 80
    port: 80
  selector:
    app: myapp
```
