### kubeadm
- 쿠버네티스 클러스터 구성을 쉽게 수행할 수 있도록 도와주는 도구
- 공식 도큐먼트에 kubeadm을 설치할 수 있는 명령어가 있다
- 그리고 마스터 노드에서 kubeadm init을 하면 control-plane-node를 설정할 수 있다. init이 완료되면 추가적으로 수행해야할 명령어가 출력되며 이를 복붙하면 된다.
- kubadm init 결과로 어떻게 클러스터에 join할 수 있는지 명령어와 토큰이 출력된다. 추가하고 싶은 노드에 접속해서 해당 명령어를 입력해주면 클러스터에 노드를 추가할 수 있다.

### End to end test
- 쿠버네티스 클러스터를 구성한다는 것은 굉장히 복잡한 일이며, 제대로 설치한게 맞는지 테스트 해볼 필요가 있다.
```bash
$ kubectl get nodes
$ kubectl get pods
$ kubectl get pods -n kube-system
$ service kube-apiserver status
$ service kube-controller-manager status
$ service kube-scheduler status
$ service kubelet status
$ service kube-proxy status
$ kubectl run nginx
$ kubectl get pods
$ kubectl scale --replicas=3 deploy/nginx
$ kubectl expose deployment nginx --port=80 --type=NodePort
$ kubectl get service
$ curl https://worker-1:31850
```
- 이런식으로 쿠버네티스의 각종 기능들을 직접 테스트하는 스크립트를 짤 수도 있다.
- 하지만 쿠버네티스의 기능들을 방대하고, 그 모든 기능을 이런식으로 테스트하기란 매우 힘들기 때문에 이를 대신해주는 도구가 kubetest이다.
- kubetest는 1000개 가까이되는 end2end 테스트를 수행한다.
- conformance test는 어떤 클러스터가 쿠버네티스 클러스터라고 불리기 위해서는 적어도 만족해야하는 테스트들을 말한다.
- 전체 테스트를 다 수행하려면 12시간이 걸린다.
- conformance test만 수행하면 1~2시간 정도 걸린다.

### kubetest 작동 방식
- 테스트를 위한 네임 스페이스를 만든다.
- 테스트용 파드를 테스트용 네임스페이스에 만든다.
- curl을 이용해서 파드에 요청을 보낸다.
- 결과를 기록한다.

### kubernetes test infra
- build, deploy, test, cleanup

### Run & Analyze E2E test
```bash
$ go get -u k8s.io/test-infra/kubetest
$ kubetest --extract=v1.11.3
$ cd kubernetes
$ export KUBE_MASTER_IP="192.168.26.10:6443"
$ export KUBE_MASTER=kube-master
$ kubetest --test --provider=skeleton > testout.txt
$ kubetest --test --provider=skeleton --test_args="--ginkgo.focus=Secrets" > testout.txt
$ kubetest --test --provider=skeleton --test_args="--ginkgo.focus=\[Conformance\]" > testout.txt
```
