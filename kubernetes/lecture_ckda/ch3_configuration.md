### Docker Entrypoint & command
```
FROM Ubuntu
ENTRYPOINT ["sleep"]
CMD ["5"]
```
- docker 파일에서 위처럼 설정해주면 컨테이서 시작시에 sleep 5 명령어를 수행한다.
- 만일 컨테이너 런 명령어를 아래와 같이 실행하면 파라미터 오버라이딩이 가능하다.
```bash
// 파라미터 값을 CMD 값에 덮어씀. 그 결과 sleep 10 수행
$ docker run ubuntu-sleeper 10 
```

### Kubernetes Command & Arguments
```
apiVersion: v1
kind: Pod
metadata:
  name: ubuntu-sleeper-pod
spec:
  containers:
  - name: ubuntu-sleeper
    image: ubuntu-sleeper
    command: ["sleep2.0"]
    args: ["10"]
```
- command 명령어를 전달하면 ENTRYPOINT를 오버라이딩한다.
- args 값을 변경하면 CMD 파라미터 값을 오버라이딩 한다.
- 그 결과로 위 yaml 파일을 실행하면 우분투 컨테이너는 sleep 2.0 10 명령어를 실행하게 된다.

### Docker Security
- 도커를 돌리고 있는 호스트가 있고 그 위에 도커 데몬과 컨테이너 프로세스가 돈다.
- 도커는 호스트의 네임스페이스에 의해서 격리된다. 네임 스페이스에 의해 격리된 컨테이너는 같은 네임 스페이스에 속한 리소스들만 볼 수 있다.
- 프로세스는 네임 스페이스에 따라서 다른 PID를 지닐 수 있다. 즉, 컨테이너 내부에서 동작 중인 프로세스는 컨테이너 내부에서는 PID가 1이지만, 외부에서는 다른 PID를 갖는다.
- 기본적으로 컨테이너 내부에서 동작하는 프로세스는 root 유저가 실행하도록 설정되어 있다.
- 아래 명령어처럼 컨테이너를 실행하면 다른 유저로 컨테이너를 실행할 수 있다.
```
// user 옵션 값으로 user id 번호를 넣어준다.
$ docker run --user=1000 ubuntu sleep 3600
```
- 혹은 도커 파일 단에서 설정할 수 있다.
```
FROM ubuntu
USER 1000
```
- 리눅스는 capability라는 제도를 운영하며, 이는 각 유저가 어떠한 역할을 할 수 있는지를 명시한다.
- 기본 옵션으로 컨테이너를 실행하면 할 수 있는 명령어에 제한이 생긴다. 이를 --cap-add 옵션 값을 집어넣어주어 생성이 가능하며, 쿠버네티스 yaml 파일에서는 security context를 통해 가능하다.

### Kubernetes Security Context 
- kubernetes에서는 컨테이너는 파드로 감싸준다.
- 파드의 사용자를 설정하면 컨테이너에 자동으로 반영된다.
```
spec:
  securityContext:
    runAsUser: 1000
```
- 파드 레벨에서 securityContext를 설정해 줄 수도 있고, 컨테이너 레벨에서 설정해줄 수도 있다.

### Service Account
- 쿠버네티스는 User 계정과 Service 계정이 있다.
- User 계정은 개발자가, Service 계정은 봇들이 사용한다. 예를들어 prometheus 같은 모니터링 솔루션들이 서비스 계정을 활용하여 쿠버네티스 클러스터에 접근한다.
- 좀 더 디테일하게 보면 모니터링 툴이 메트릭을 수집하기 위해서는 kube-apiserver에 요청을 보내야 하며, 이 때 인증 과정을 거친다. 이 인증에 사용하는 것이 ServiceAccount이다.
- serviec acocunt는 kubectl에서 바로 생성이 가능하다.
```bash
$ kubectl create serviceaccount <SERVICE-ACCOUNT>
```
- service account는 생성과 동시에 토큰을 생성하며, 이 토큰을 활용하여 인증 과정을 처리한다. 토큰 자체는 secret object로 저장되며, service account 오브젝트에는 이 시크릿의 이름 값이 저장된다.
- 이 토큰 값을 header 값에 추가한 뒤, kube-apiserver에 요청을 보내면 정상적으로 인증을 완료할 수 있다.
```bash
$ curl https://<matser-node-ip>:6443/api -insecure --header "Authorization: Bearer <YOUR-SERVICE-ACCOUNT-TOKEN>" 
```
- kubernetes의 모든 namespace는 기본적으로 default 서비스 계정을 갖는다.
- 아무 추가적인 설정없이 파드를 생성하면 default 서비스 계정이 자동으로 파드의 volume 형태로 마운트 된다.
- service account token은 ca.crt, namespace, token으로 구성된다.
- 자체 생성한 service account를 사용하고 싶다면 spec 아래에 적어주면 된다.
```
spce:
  serviceAccount: <MY-SERVICE-ACCOUNT>
```

### Resource Limits
- 파드는 자신이 필요로하는 리소스를 명시할 수 있으며, CPU, MEM, DISK 등이 포함된다.
- CPU는 숫자로, MEM은 숫자 뒤에 단위를 적어주어 설정이 가능하다.
- cpu 숫자는 코어 수를 나타내며 0.1은 100m과 같다. 설정 가능한 최소 단위는 1m이다.
- 이 코어 단위는 클라우드 프로바이더에 따라서 달라질 수 있다.
- 메모리를 나타내는 단위로는 G, M, K, Gi, Mi, Ki가 있다.
- G: 1,000,000,000 bytes
- M: 1,000,000 bytes
- K: 1,000 bytes
- Gi: 1,073,741,824 bytes
- Mi: 1,048,576 bytes
- Ki: 1,024 bytes
```
spec:
  containers:
  - name: 
    resources:
      requests:
        cpu: 1
        memory: "1Gi"
      limits:
        cpu: 2
        memory: "2Gi"
```
- cpu 리미트를 넘어서려 하면 throttle을 발생시켜 리미트를 넘어서지 않으려 한다.
- memory의 경우에는 OOM이 발생하여 파드가 꺼지게 된다.

### taint, toleration
- taint에는 NoSchedule, PreferSchedule, NoExecute 세 가지 효과가 있다.
- taint는 해당 노드에 파드가 스케쥴 되지 않도록 보장하는 장치이므로 toleration이 설정된 파드가 반드시 taint가 설정된 노드에 스케쥴 될 것이라 보장할 수는 없다. toleration이 없는 파드가 스케쥴 되지 않는 것을 보장할 뿐이다.

### node selector
- 노드 라벨을 이용해서 파드가 스케쥴 될 노드를 선택할 수 있다.
- 하지만 노드 셀레터는 단일 라벨만 사용할 수 있다.  node affinity는 이러한 문제점을 operator를 통해서 극복한다.

### node affinity
- node affinity의 주된 목적은 파드를 원하는 노드에 배포되도록 지정하는 것이다.
- operator를 통해서 or나 not과 같은 로직을 적용할 수 있다.
```
spec:
  nodeAffinity:
    requiredDuringSchedulingIgnoredDuringExecution:
      nodeSelectorTerms:
      - matchExpressions:
        - key: size
          operator: In
          values:
          - Large
          - Medium
```
- operator에는 In, NotIn, Exists(키 값만 검사함)
- 만일 조건에 맞는 노드가 없다면?
  - requiredDuringSchedulingIngoredDuringExecution: 조건 맞는 노드가 없으면 스케쥴링 안함
  - prefferedDuringSchedulingIgnoredDuringExcution: 조건 맞는 노드 없으면 걍 스케쥴링 해버림
  - requiredDuringSchedulingRequiredDuringExecution(구현 예정): 파드가 배포되어 동작 중에 노드 라벨이 바뀌어서 affinity와 매치되지 않는다면 다른 노드로 쫓아냄

### Taint & Affinity
- 각각은 파드를 어느 노드에 배치할 것인가에 대한 속성들이지만, 초점이 다르다.
- Taint는 특정 노드에 파드가 스케쥴 되지 않도록, Affinity는 특정 노드에 파드를 스케쥴 하도록 설정할 때 사용한다.
- 그러므로 Taint와 Affinity를 적절하게 섞어서 사용할 줄 아는 것이 중요하다.
