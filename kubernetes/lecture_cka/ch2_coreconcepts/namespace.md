### Namespace
- 집이 두 개가 있다고 생각, 같은 집 안에서는 first name 만으로 서로를 부를 수 있다.
- 각각의 집은 고유한 리소스가 있다.
- pod, deployment, replicaset 등과 같은 오브젝트들은 namespace에 속하며 별다른 설정을 하지 않을 시 default에 속한다.
- 쿠버네티스가 자체적으로 관리하는 서비스나 오브젝트들을 유저가 실수로 지우는 일을 방지하기 위해서 네임 스페이스를 구분하며, kube-system 네임 스페이스가 이에 해당한다.
- kube-public, kube-system, default 이렇게 세 종류의 네임 스페이스가 기본으로 제공된다.
- 클러스터가 커지면서 커스텀 네임 스페이스를 만들고 관리해야할 필요성이 생겨난다.
- 예를 들어서 dev, prod 네임 스페이스를 나눠서 관리하면 prod의 리소스를 실수로 지우는 일이 발생하지 않는다.
- 각 네임스페이스 별로 누가 무엇을 할 수 있는 지를 지정할 수 있다.
- 각 네임 스페이스 별로 클러스터의 자원을 얼만큼 사용할 수 있는지도 정할 수 있다.

### DNS
- 같은 네임 스페이스 안의 오브젝트들은 서로를 name으로 구분할 수 있다.
- 다른 네임 스페이스 안의 오브젝트들은 네임스페이스를 포함한 풀 네임을 기재해줘야 한다.
```
// 동일 네임 스페이스 내의 db-service
$ mysql.connect("db-service")
// 다른 네임 스페이스 내의 db-service (cluster.local은 도메인 네임, svc는 서비스임을 명시, dev는 네임스페이스)
$ mysql.connect("db-service.dev.svc.cluster.local")
```
### 네임스페이스 운용
- 파드 생성 시에 네임 스페이스 지정 하고 싶다면 metadata에 기재해라
```
metadata:
  namespace: dev
```
- 네임 스페이스도 yaml 파일을 통해서 생성이 가능하다.
```
apiVersion: v1
kind: Namespace
metadata:
  name: dev
```
- 혹은 단순한 명령어로도 namespace 생성이 가능하다.
```
$ kubectl create namespace dev
```

### Switch
- default namespace에서 전환하려면 아래 명령어를 입력
```
$ kbuectl config set-context $(kubectl config current-context) --namespace=dev
```
- 그러면 kubectl get pods를 해도 지정한 namespace에서 정보를 가져와 보여줌. 굳이 옵션을 붙여주지 않아도 된다.
```
$ kubectl get pods --all-namespaces
```

### Resource Quota
```
apiVersion: v1
kind: ResourceQuota
metadata:
  name: compute-quota
  namespace: dev
spec:
  hard:
    pods: "10"
    requests.cpu: "4"
    requests.memory: 5Gi
    limits.cpu: "10"
    limits.memory: 10Gi
```
