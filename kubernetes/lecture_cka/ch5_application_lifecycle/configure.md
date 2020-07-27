### commands
- 도커 컨테이너를 실행시킬때 수행하는 명령어를 다르게 주고 싶다면?
```
FROM Ubuntu
ENTRYPOINT ["sleep"]

// ENTRYPOINT에 주어진 명령어 뒤에 파라미터를 덧붙인다.
$ docker run unbuntu-sleeper 10
```
- 그런데 만일 파라미터를 안붙여준다면?
```
FROM Ubuntu
ENTRYPOINT ["sleep"]
CMD ["5"]
```

### kubernetes commands
```
apiVersion: v1
kind: Pod
metadata:
  name: ubuntu-sleeper-Pod
spec:
  containers:
  - name: ubuntu-sleeper
    image: ubuntu-sleeper
    command: ["sleep2.0"]
    args: ["10"]
```

### 환경 변수 주입 방법
```
// 방법 1. 그냥 키벨류 포맷으로 넣어주기
env
- name: APP_COLOR
  value: pink

// 방법 2. configMap 사용
env
- name: APP_COLOR
  valueFrom:
    configMapKeyRef:

// 방법 3. secret 사용
env
- name: APP_COLOR
  valueFrom:
    configMapKeyRef:
```

### configMap 사용하기
- kubectl create configMap
```
$ kubectl create configmap <config-name> --from-literal=<key>=<value>
$ kubectl create configmap <config-name> --from-file=<path-to-file>
```
- 혹은 yaml 파일로 생성
```
apiVersion: v1
kind: ConfigMap
metadata:
  name: <CONFIGMAP-NAME>
data:
  <KEY>: <VALUE>
```
- configMap 생성한 후에 envFrom 명령어로 한꺼번에 불러올 수가 있음
```
envFrom:
- configMapRef:
    name: myconfig
```

### Secret 만들기
- stringData로 설정하는 것에 유의할 것
```
apiVersion: v1
kind: Secret
metadata:
  name: <SECRET-NAME>
type: Opaque
stringData:
  <KEY>: <VALUE>
```
