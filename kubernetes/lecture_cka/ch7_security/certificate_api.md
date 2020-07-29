### Certificate API
- 새 admin을 추가해야할 때 API를 사용할 수 있다.
- 마스터 노드에서 CA를 생성하고 CA Server 역할을 수행한다.
- CERTIFICATES API가 따로 마련되어 있으며, 오브젝트로 생성할 수 있다.
1. Create CertificateSigningRequest Object
2. Review Requests
3. Approve Requests
4. Share Certs to Users
```bash
$ openssl genrsa -out jane.key 2048
$ openssl req -new -ey jane.ey -subj "/CN=jane" -out jane.csr
$ cat jane.csr | base64
// 이렇게 생성한 csr을 가지고 yaml 파일을 작성한다.
apiVersion: certificaes.k8s.io/v1beta1
kind: CertificateSigningRequest
metadata:
  name: jane
spec:
  groups:
  - system: authenticated
  usages:
  - digital signature
  - key encipherment
  - server auth
  request:
    <base64 csr 복사한 내용>
```
```bash
$ kubectl get csr
$ kbuectl certifiacte approve jane
>> jane approved!
$ kubectl get csr jane -o yaml
>> certificate 안에 싸인된 base64 string이 들어있다. 이를 복사할 것
$ echo "복사한 string" | base64 --decode
```
- 즉, yaml 파일로 csr을 오브젝트로 만든 뒤, kubectl 커맨드를 사용해서 싸인해줄 수 있다.

### Certificate API 
- Controller Manager에서 수행되는 것
- 그 안에 CSR-APPROVING, CSR-SIGNING이 작업을 수행해준다.

### Kube Config
- kubectl을 사용하지 않고 curl 만으로 kube-apiserver의 기능을 사용할 수 있다.
```bash
$ curl http://my-kube-playground:6443/api/v1/pods \
  --key admin.key
  --cert admin.crt
  --cacert ca.crt
```
- kubectl을 사용해서도 동일한 작업을 할 수 있으며, 이 때 역시도 서버의 주소라던가 인증서 정보들이 필요하다.
- 매번 kubectl을 입력할 때마다 이런 옵션 값을 주는게 귀찮으므로 이를 별도의 config 파일로 빼내어 관리하며, 이를 kubeconfig 파일이라 부른다.
```bash
// kube config 파일 주소
$HOME/.kube/config
```

### Kube Config 파일 구성
- clusters, contexts, users로 구성
- cluasters: 여러 개의 클러스터 설정 가능, Development, Production, Google
- Users: Admin, Dev User, Prod User 등등 설정 가능
- Context: 이 둘을 묶어주는 역할, ex) Admin@Production, Dev@Google
- 인증서 내용은 Users에, 클러스터 IP는 Clusters에, Contexts에는 User와 Cluaster를 묶어주는 내용이 기재되게 된다.

### Kube Config Yaml
- kube config 역시 yaml 파일이며 오브젝트로 만들어서 관리된다.
```
apiVersion: v1
kind: Config
current-context: dev-user@google
clusters:
- name: my-kube-playground
  clusters:
    certificates-authority: ca.crt
    server: <SERVERIP>
contexts:
- name: my-kube-admin@my-kube-playground
context:
  clustesr: my-kube-playground
  user: my-kube-admin
users:
- name: my-kube-admin
  user:
    client-certificate: admin.crt
    client-key: admin.key
```
- config를 추가하고 싶다면 cluster, user, context로 추가하면 된다.

- context 전환 시에는 아래 명령어를 사용한다.
```bash
$ kubectl config use-context pord-user@production
```
- context 정보 기입 시에 namespace를 기입할 수 있다.
```
context:
  cluster: <CLUSTER>
  user: <USRE>
  namespace: <NAMESPACE>
```



