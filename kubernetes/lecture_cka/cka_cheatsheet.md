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
