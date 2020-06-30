### ConfigMap
- 환경 변수 값들을 담은 설정 파일
```
apiVersion: v1
kind: ConfigMap
metadata:
  name: config-dev
data:
  DB_URL: localhost
  DB_USER: myuser
```
- 다른 오브젝트에서는 아래와 같이 컨피그 맵의 값들을 불러와서 사용 가능
```
env:
  - name: DB_URL
    valueFrom:
      configMapKeyRef:
        name: config-dev
        key: DB_URL
```
### Secret
- DB 패스워드 처럼 보안에 민감한 정보는 암호화가 적용되는 Secret 오브젝트에 담아서 사용한다.
- 이 때 Imgerative 한 명령어로 생성한다.
```
$ kubectl create secret generic <secret_name> --from-literal key=value
ex) kubectl create secret generic config-dev-secret --from-literal DB_PASSWORD=password
```
- ConfigMap과 마찬가지로 이를 불러와서 사용 가능
```
env:
  - name: DB_PASSWORD
    valueFrom:
      secretKeyRef:
        name: config-dev-secret
        key: DB_PASSWORD
```
<<<<<<< Updated upstream
=======
- 이 외에도 시크릿을 프라이빗 이미지를 pull 받을때 사용할 수도 있음
- HTTPS 인증서를 저장하는 용도로도 시크릿 사용이 가능함

>>>>>>> Stashed changes
