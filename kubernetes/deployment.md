### 롤백
- deployment로 배포한 파드를 이전 버전으로 되돌리고 싶다면 kubectl 명령어로 가능하다.
```bash
$ kubectl rollout history deployment/{deployment 명}
$ kubectl rollout undo deployment {deployment 명} --to-revision
```
