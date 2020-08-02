### 왜 jsonpath가 필요한가?
- 노드가 100개가 넘어간다면?
- 이를 모두 yaml 형식으로 확인하기 어렵다. jsonpath를 kubectl에서 사용하면 굉장히 편리한 측면이 있다.
- kubectl과 kube-apiserver는 사실 json 포맷으로 데이터를 주고 받는다. 따라서 우리는 kubectl에서 jsonpath를 사용할 수 있다.
```bash
$ kubetl get nodes -o json 
$ kubectl get pods -o=jsonpath='{.items[0].spec.containers[0].image}'
```
- 위 명령어로 json 포맷으로 kubectl 결과 값을 확인할 수 있다.
- 그 다음 jsonpath를 직접 만들어서 조회할 수 있다.

### jsonpath 활용 예시
```bash
$ kubectl get nodes -o=jsonpath='{.items[*].metadata.name}'
$ kubectl get nodes -o=josnpath='.items[*].status.nodeInfo.architecture' 
```

### jsonpath 안에 쿼리 넣는법
```bash
$ kubectl config view --kubeconfig=my-kube-config -o jsonpath="{.contexts[?(@.context.user=='aws-user')].name}" > /opt/outputs/aws-context-name 
```

