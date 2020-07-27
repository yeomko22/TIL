### Rollout and Versioning
- 새로운 버젼의 애플리케이션이 배포되려면 기존의 버전을 업데이트 해야한다.
```
$ kubectl rollout status deployment/myapp-deployment
```
- 지금까지 deployment가 겪어온 히스토리를 쭉 보여준다.

### 배포 전략
- recraete: 기존의 인스턴스를 다 파괴하고 새로 띄움 -> 서비스 중단 발생
- rolling update: 순차적으로 인스턴스를 내리고 새 인스턴스를 띄움 -> 서비스 중단 발생하지 않음
- rolling update가 default 옵션

### kubectl apply
- yaml 파일에서 이미지의 버젼을 바꿔준 뒤 apply 해준다.
- kubectl set image deployment/myapp-deployment:nginx=nginx:1.9.1
- imperative하게 변경해줄 경우 yaml 파일과 실제 배포된 이미지의 버젼이 맞지 않을 수 있으므로 주의해야한다.

### Upgrades
- Deployment 안에는 Replicaset이 떠있고, 그 안에 replica들이 뜨게 된다.
- Deployment는 새로운 replicaset을 만들고, 기존 파드를 내림과 동시에 새로운 replicaset에 새로운 파드를 띄워준다.
- 롤백은 아래 명령어로 쉽게 수행할 수 있다.
```
$ kubectl rollout undo deployment/myapp-deployment
```
### kubectl run
```
// deployment를 생성함
$ kubectl run nginx --image=nginx
```

### 배포 관련 커맨드 정리
```
$ kubectl apply -f <yaml 파일 이름>
$ kubectl set image deployment/myapp-deployment nginx=nginx:1.9.1
$ kubectl rollout status deployment/myapp-deployment
$ kubectl rollout hist
$ kubectl rollout undo deployment/myapp-deployment
```
