### Deployment
- 새로운 버젼의 이미지를 배포하고 싶다. 단, 순차적으로 인스턴스를 업데이트 하고 싶다.(RollingUpdate)
- RollBack도 수행하고 싶을 수 있다.
- blue/green 배포도 수행하고 싶을 수 있다.
- 이 모든 것을 가능케 해주는 것이 Deployment이다.

### Deployment Definition
```
apiVersion: apps/v1
kind: Deployment
metadata:
  name: myapp-Deployment
  labels:
    app: myapp
    type: front-end
spec:
  template:
    metadata:
      name: myapp-pod
      labels:
        app: myapp
        type: front-end
  replicas: 3
  selector:
    matchLabels:
      type: front-end
```
- replicaset이랑 kind 부분만 다르다.
