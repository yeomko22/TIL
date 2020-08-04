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

### 현재 네임 스페이스 변경
```bash
$ kubectl config set-context --current --namespace=<원하는 네임스페이스> 
```

### 파일을 못찾는 에러
- 볼륨이 잘못 지정되어 있을 수 있다.

### 워커 노드 장애
- kubectl describe node <노드 이름>
- top, df -h 
- service kubelet status
- sudo journalctl -u kubelet
- openssl x509 -in /var/lib/kubelet/worker-1.crt -text

### 워커 노드 장애 시 조치
1. 워커 노드 접속
2. kubelet 서비스 상태 확인
```bash
$ service kubelet status
혹은
$ journalctl -u kubelet -f
```
3. kubelet 재시작
```bash
$ service kubelet start 
```

### 워커 노드 kubelet 설정 변경
- /var/lib/kubelet/config.yaml 파일이 위치, 여기서 설정 변경이 가능
- /etc/kubernetes/kubelet.conf 여기서도 마스터 노드 IP와 포트 정보 등을 수정 가능.
- 만일 kubelet 서비스 자체가 먹통이면 yaml 파일의 문제, 서비스 자체는 뜨는데 마스터 노드와 통신을 못한다면 conf 파일 문제를 의심해 볼 수 있다.

### web app frontend
1. curl를 때려서 프런트엔드에 접속해보아라.
2. 만일 동작하지 않는다면 해당 파드에 달려있는 서비스가 제대로 동작중인지, 엔드포인트가 제대로 설정되어 있는지를 보아라. 라벨이 안맞을 수 있다.
3. 그 다음 파드를 보아라. 파드가 restarts를 반복했다면 describe와 logs 명령어로 상태를 확인해보아라.

### 주요 troubleshooting 지점
- 서비스 라벨 매핑
- 서비스 포트 매핑
- 디비 계정 잘못 기입
- 디비 포트 잘못 기입

### 컨트롤 플레인 트러블 슛
- 노드 상태 확인
- kube-system 네임 스페이스의 파드 상태 확인
- 서비스 상태 확인
```bash
$ service kube-apiserver status
$ service kube-controller-manager status
$ service kube-scheduler status
```
- 워커 노드의 kubelet 상태 확인하기 
```bash
$ service kubelet status
$ service kube-proxy status
```
- kube-apiserver 로그 확인
```bash
$ kubectl logs kube-apiserver -n kube-system
$ sudo journalctl -u kube-apiserver 
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

### 워커 노드에서 static pod 생성하기
1. 워커 노드 접속
2. systemctl status kubelet 명령어로 kubelet 상태 확인 및 config 파일 위치 확인 (/var/lib/kubelet/config.yaml)
3. config 파일 내부에 static pod 폴더 경로가 들어있다.
4. 해당 폴더 내에 yaml 파일 생성해주면 끝

### 클러스터 내부에서 특정 서비스가 접근 가능한지 확인하는 방법
```bash
$ nc -z -v -w 2 <service 명> <port 번호>
```

### static 파드 구별법
- 파드 뒤에 -<노드 이름>이 붙으면 스태틱 파드이다.

### multiple scheduler
- 반드시 문서 보고 따라할 것. 그냥 내멋대로 하면 절대로 안됨
- /etc/kubernetes/manifest 안에 들어있는 yaml을 복사한 뒤에 아래 값들을 반드시 추가해 줄 것
```bash
- --leader-elect=false
- --scheduler-name=my-scheduler 
```

### 내 취약점
- upgrade 시에 drain
- deployment record 남기기
