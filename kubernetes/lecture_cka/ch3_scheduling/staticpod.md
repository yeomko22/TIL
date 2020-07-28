### Static Pod이란?
- 마스터 노드도 없고 다른 워커 노드도 없다면? -> 하나의 워커 노드에서 kubelet이 모든 관리를 다한다.
- kubeapi 서버가 없는 상황에서 어떻게 yaml 파일에 저장된 파드의 명세를 kubelet에게 전달할 것인가?
- 각 노드의 /etc/kubernetes/manifest는 설정 파일들을 모아놓는 폴더이다. 이 폴더에 yaml 파일을 넣어두면 해당 노드의 kubelet에서 읽을 수 있다.
- kubelet은 주기적으로 이 폴더를 읽어와서 파드를 생성하며, 모니터링 한다.
- 폴더에서 파일을 지우면 비로소 파드를 삭제한다.
- 다른 컨트롤러는 이러한 방식으로 생성이 불가, 오직 파드만 가능하다. kubelet이 파드 레벨에서만 동작하기 때문이다.
- kubelet.service의 pod-manifest-path에서 이 폴더의 경로를 변경해줄 수 있다.
- kubelet.service에 config 옵션으로 커스텀 옵션을 넣어줄 수 있다. 여기서 staticPodPath 값을 전달해준다.
- 스태틱 파드를 생성한 뒤에는 docker ps로 확인할 수 있다.
- 스태틱 파드는 API서버를 통해서 삭제가 불가능, 노드의 파일시스템의 설정 파일을 삭제해야 지워짐

### static pod 용도
- static pod는 kubernetes controll plane와는 분리되어 있음. 그래서 control plane 자체의 배포를 위해서 사용한다.
- 즉, 마스터 노드에 kubelet을 먼저 설치하고, 나머지 컴포넌트들의 매니패스트만 특정 폴더안에 넣어주면 손쉽게 설치가 끝난다.

### static pod vs daemonset
- static pod: kubelet이 생성, kubernetes control plane 배포에 사용
- daemonset: kube-apiserver가 생성, 모니터링, 로깅 에이전트 배포에 사용

### static pod 생성
- static pod로 만들면 파드명 뒤에 master가 붙는다.
- /etc/kubernetes/manifest 폴더 안에 새로운 yaml 파일을 추가만 해주면 된다.
- 기존에는 etcd, kube-apiserver, kube-controller-manager, kube-scheduler가 들어있다.
