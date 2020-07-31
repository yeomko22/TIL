#### Certificate Object 생성 방법
https://kubernetes.io/docs/tasks/tls/managing-tls-in-a-cluster/

### kube config context 바꾸기
```bash
// 특정 파일을 전달해주고 그 안에서 특정 컨텍스트를 찾아내서 적용함
$ kubectl config --kubeconfig=/root/my-kube-config use-context research
```

### role이 어느 사용자에게 부여되어 있는지 확인하기
```bash
$ kubectl describe rolebinding kube-proxy -n kube-system
```
### 특정 유저가 파드 get 할 수 있는지 확인하기
```bash
$ kubectl get pods --as dev-user
```

### apigroup 확인하기
```bash
$ kubectl api-resources
>> 여기서 특정 리소스의 APIGROUP 확인해서 clusterrole과 clusterrolebinding을 작성 가능
```

### 현재 context 확인하기
```bash
$ kubectl config view | grep current
```

### kubeconfig 관련 문서
https://kubernetes.io/docs/tasks/access-application-cluster/configure-access-multiple-clusters/

### 파드의 컨테이너 안에서의 사용자 확인
```
$ kubectl exec <파드명> -- whoami
```

### 인터넷 접속 시에 기본 게이트웨이 확인하기
```bash
$ ip route show default 
```
### kube-sheduler가 마스터 노드와 통신시에 사용하는 포트 확인
```bash
$ netstat -nplt 
```
- 그냥 파드를 검사하면 kube-scheduler가 외부 요청을 수신하는 포트만 확인할 수 있으며 10259를 사용한다.
- 마스터 노드와의 통신은 10251 포트를 사용한다.

### ETCD port
- 2379 포트는 컨트롤 플레인 컴포넌트들과 통신할 때 사용하며 kube-apiserver가 주된 상대이다.
- 2380 포트는 같은 ETCD 노드 간의 통신에 사용하므로 2379 포트로 들어오는 트래픽이 더 많다.

### 프로세스 시작 시 옵션 보기
```bash
$ ps -aux | grep kubelet 
```
- ps -aux 명령로 조회하면 프로세스 시작 당시 전달된 파라미터들을 볼 수 있다.
- 쿠버네티스 네트워크 플러그인의 종류를 확인하려면 kubelet 실행 옵션 중에서 --cni-bin-dir의 값을 살펴보면 된다.

### 현재 사용 중인 CIN 플러그인 확인하기
```bash
$ ls /etc/cni/net.d/ 
```

### 컨테이너 시작 시에 실행되는 weave 플러그인의 바이너리 파일 이름은?
![weave_plugin](../../../images/weave_plugin.png)
- type 아래에 설정된 weave-net이 실행된다.
