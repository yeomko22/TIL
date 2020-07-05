### kubectl 주요 커맨드
```
$ kubectl delete -f <config file>
```
- config file을 이용해서 생성한 팟을 삭제
```
$ kubectl describe <object type> <object name>
```
- 현재 동작 중인 pod의 세부 내용을 확인
```
$ kubectl set images <object_type>/<object_name> <container_name>
```
```
$ eval $(minikube docker-env)
```
- 내 로컬 docker-cli를 minikube vm 내부의 docker-server로 연결해준다!
```
$ kubectl get pv
# kubectl get pvc
```
- persistent volume과 persistent volume claim 목록을 보여주는 명령어

### kubectl 부가 기능
- docker logs, docker exec 등과 같은 기능들을 kubectl 명령어를 통해서 수행할 수 있다.

### service fullname 알아내기
```

```