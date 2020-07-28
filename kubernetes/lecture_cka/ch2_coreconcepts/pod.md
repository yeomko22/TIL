### Pod yaml로 생성하기
```
apiVersion:
kind:
metadata:
spec:
```
- 모든 쿠버네티스 yaml 파일은 위 4개의 필드 값을 가진다.

### 예시 명령어
```
$ kubectl run nginx --image nginx
$ kubectl get pods -o wide // 파드 생성 시에 무슨 이미지가 쓰였는지 확인하는 명령어
```
