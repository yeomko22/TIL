### Label
- 파드에 다양한 라벨을 붙이고 기준별로 조회할 수 있다.

### Rolling Update, Rollback
```bash
$ kubectl rollout status deployment/myapp-deployment
```
- 한 큐에 업데이트 하는 방법과 점차 업데이트 하는 방법이 있다.
- rolling update를 수행하면 무중단 배포를 수행할 수 있으며, Deployment의 default 옵션이다.

### Jobs
- Deployment 같은 것들은 오랜 기간동안 동작해야하는 것들이다.
- 그 외에 분석 작업을 수행하는 등의 작업은 해당 작업만 수행하고 종료되어야 한다.
```
apiVersion: batch/v1
kind: Job
metadata:
  name: math-add-Job
spec:
  completion: 3
  paralleism: 3
  template:
    spec:
      containers:
      - name: math-add
        image: ubuntu
        command: ['expr', '3', '+', '2']
      restartPolicy: Never
```
```
apiVersion: batch/v1beta1
kind: CronJob
metadata:
  name: cron-job
spec:
  schedule: "*/1 * * *"
  jobTemplate:
    spec:
      completions: 3
      parallelism: 3
      template:
        spec:
          containers:
          - name:
            image:
            command: ['expr', '3', '+', '2']
          restartPolicy: Never
```
