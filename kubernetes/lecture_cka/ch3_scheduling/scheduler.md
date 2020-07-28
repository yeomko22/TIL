### scheduler가 여러개라면?
- default scheduler와 함께 own kube-scheduler를 만들어서 동시에 운영할 수 있다.
- scheduler 배포시에는 옵션 값에 주의해서 배포할 것
```
--scheduler-name=my-custom-scheduler
```
- kubeadm에서 파드의 형태로 kube-scheduler를 배포한다.
- /etc/kubernetes/manifest 폴더에 기본 scheduler 설정 yaml 파일이 있고, 이걸 고대로 복 뜬 다음 옵션 값들을 바꿔서 배포하면 된다.
```
- command
  - --scheduler-name=my-custom-scheduler
  - --lock-object-name=my-custom-scheduler
```
- 배포한 스케쥴러는 kubectl get pods -n kube-system에서 확인
- 파드 배포시에 스케쥴러를 지정할 수 있음.
```
spec:
  schedulerName: my-custom-scheduler
```
- kubectl get events로 custom scheduler가 제대로 동작하는 지 확인 가능하다.

- 예제에서 까다로웠던 부분
  - 커스텀 스케쥴러 설정 yaml 파일에서 commands 아래에서 leader-elect를 false로 설정해주어야 했고, --port 옵션에 새로 지정한 포트를 넣어줘야 했으며, 이때 현재 비어있는 포트를 먼저 확인하고 설정해야 했다.
