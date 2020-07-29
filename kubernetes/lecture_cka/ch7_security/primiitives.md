### Security Host
- password based authentication disabled
- ssh key baesd authentification
- kube-apiserver가 보안의 시작점
- kube-apiserver와 다른 컴포넌트 사이에도 보안 통신을 한다.

### Who can access?
- username, password, tokens
- certificates
- service accounts
- external service: LDAP

### What can they do?
- RBAC Authorization
- ABAC Authorization
- Node Authorization
- Webhook

### Authentication
- Cluster 접근자
  - Admins
  - Developers
  - Bots
- User: Admins, Developers
- Service Accounts: Bots

- kubernetes는 내부적으로 사용자 계정을 유지하지 않는다. 그래서 아래와 같은 명령어는 사용 불가능하다.
```bash
$ kubectl create user user1
$ kubectl list users
```
- 대신에 service account는 만들 수 있다.
```bash
$ kubectl create serviceaccount sa1
$ kubectl list serviceaccount
```

### Accounts
- 모든 클러스터에 대한 접근은 kube-apiserver를 통해서 이루어진다.
- kubectl 명령어나 curl https://kube-server-ip:6443 요청은 kube-apiserver로 들어간다.
- kube-apiserver는 먼저 user를 authentificate하고, 그 다음 요청을 수행한다.

### kube-apiserver 사용자 인증 방식
- static password file
- static token file
- certificates
- identity services

### Auth mechanisms - Basic
- 유저 ID와 패스워드를 csv 파일에 담아서 관리
```
// kube-apiserver.service 파일에 csv 파일 경로를 옵션값으로 추가해준다.
ExecStart=...
...
--basic-auth-file=user-details.csv
```
- 혹은 kube-apiserver static pod 생성 yaml 파일에 옵션 값을 직접 추가해주는 방식이 있다.
```
spec:
  containers:
  - command:
    - kube-apiserver
    - ...
    - --basic-auth-file=user-details.csv
```
- 이렇게 설정해주고 curl url에서 user와 password를 실어주면 접속할 수 있다.
```bash
$ curl -v -k https://master-node-ip:6443/api/v1/pods -u "user1:password123"
```
- static passowrd file에 그룹을 설정 가능
- static token file도 구성이 비슷함
- 하지만 이런 단순한 방식은 권장되어지지 않는다.
- 이 방식을 사용할 때에는 auth 파일을 제공하기 위해서 volume을 사용할 것을 권장한다. 
