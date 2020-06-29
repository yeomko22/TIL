### Replica Controller
- 가장 초창기 컨트롤러
- 현재는 replicaset을 많이 사용

### Replicaset
- replica controller의 발전 버전으로 집합 기반의 selector를 지원
- rolling-update 옵션이 필요할 때는 deployment를 사용해야함
- 컨트롤러는 selector를 이용해 관리하고자 하는 파드를 지정한다.
```
selector:
  matchLabels:
    app: nginx-replicaset
```
- 때문에 기존에 실행 중인 파드를 중단하거나 재시작 하지 않고 컨트롤러를 변경, 삭제할 수 있다.
- 컨트롤러는 자신의 설정 파일에 따라서 파드의 현재 상태를 관리한다.
- 만일 컨트롤러와 동시에 파드를 생성하고 싶다면 파드를 생성하는 template 코드의 metadata.labels 값과 컨트롤러의 selector.matchLabels 값이 동일해야한다.

- 실행 중인 파드의 label 값을 변경하면 해당 파드가 컨트롤러에서 분리된다.
```
$ kubectl edit pod <pod 이름>
```
- 컨트롤러는 자동으로 개수를 맞춰주게 되고, 떨어져 나온 파드는 디버깅 용으로 사용한다.

### Deployment
- 쿠버네티스에서 상태가 없는 앱을 배포할 때 사용하는 가장 기본적인 컨트롤러
- 배포 기능을 세분화하여 롤링 업데이트, 배포 중 일시 정지, 롤백 등을 제공
- deployment는 replicaset을 포함한다. get rs를 해보면 deployment도 함께 조회된다.
- deployment의 설정값을 변경하면 deployment는 새로운 replicaset를 생성하고, 그에 맞춰서 pods들을 변경한다.

### Deployment 변경 및 롤백
```
$ kubectl set image deployment/nginx-deployment nginx-deployment=nginx:1.9.1
$ kubectl edit deploy nginx-deployment
```
- 동작 중인 deployment의 이미지를 다음과 같은 명령어로 수정할 수도 있고, 설정 파일을 수정한 뒤 apply를 통해서도 수정 가능하다.
```
$ kubectl rollout history deploy nginx-deployment
$ kubectl rollout history deploy nginx-deployment --revision=3
```
- 이전에 deployment에 진행한 변경 내역을 확인 가능하다.
```
$ kubectl rollout undo deploy nginx-deployment
$ kubectl rollout undo deploy nginx-deployment --to-revision=3
```
- 위 명령어로 변경 사항을 롤 백 할 수 있다.
- revision 만으로는 변경 사항을 알기 어려우므로 yaml파일에 annotations 필드 값을 추가한다.

### Deployment 스케일 변경, 일시정지, 재개, 재시작
```
$ kubectl scale deploy nginx-deployment --replicas=5
$ kubectl rollout pause deployment/nginx-deployment
$ kubectl rollout resume deployment/nginx-deployment
$ kubectl rollout restart deployment/nginx-deployment
```

### Daemon Set
- 클러스터 전체 노드에 특정 파드를 실행할 때 사용하는 컨트롤러
- 전체 노드에 로그 수집 파드를 추가하는 상황 등에서 사용

### Stateful Set
- replicaset, deployment, statefulset 등은 모두 상태가 없는 파드들을 관리하는 용도
- Stateful Set의 경우 상태가 있는 파드들을 관리하는 컨트롤러
- Volume을 사용해서 데이터를 저장 후, 파드 재시작 시에 데이터를 유지
- 개별 팟들에 대한 볼륨을 관리하기 때문에 상태 저장이 가능하다.
- RDBMS, NoSQL 등을 클러스터에서 운영할 때 유용하다.

### Job
- 실행 후 종료해야하는 성격의 작업을 실행시킬 때 사용하는 컨트롤러
- 단일 잡, 오나료된 잡개수가 있는 병렬 잡, 워크 큐가 있는 병렬 잡이 있다.

### Cronjob
- 잡을 시간 기준으로 관리하도록 생성
