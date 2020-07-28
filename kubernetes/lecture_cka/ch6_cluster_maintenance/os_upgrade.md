### OS upgrade
- 만일 클러스터의 특정 노드가 죽는다면? -> 특정 노드가 5분간 응답이 없으면 해당 노드에서 돌고 있던 파드를 다른 노드에 띄워준다. (타임 아웃 시간도 설정할 수 있다.)
- drain을 사용한다.
```
$ kubectl drain node-1
```
- 특정 노드에 동작 중인 파드들을 다른 노드로 옮기고, 해당 노드를 UnSchedule 되도록 지정한다.
```bash
$ kubectl cordon node-1
$ kubectl uncordon node-1
```
- cordon은 특정 노드에 더 이상 파드가 스케줄링 되지 않도록 한다. 노드를 종료시키거나 동작 중인 파드를 다른 노드에 옮기는 등의 작업을 수행하지는 않는다.
- uncordon을 수행하면 노드를 스케쥴링이 가능한 상태로 변경해준다.

```bash
$ kubectl drain node01 --ignore-daemonsets
```
- 특정 노드를 유지 보수를 위해서 비워주기, 동작 중인 파드를 옮기고 더 이상 스케쥴링 되지 않도록 설정
- 만일 replicaset의 관리를 받지 않는 순수 파드가 떠있다면 --force 옵션을 붙여주어야 한다. force 옵션으로 drain 진행하면 해당 파드는 영영 삭제된다.
- 단순히 스케줄링, 언스케줄링을 조절하고 싶다면 cordon, uncordon을 활용하면 좋다.

### Kubernetes Releases
- v1.11.3 (major, minor, patch)
- minor 버젼은 몇달 간격으로 배포된다.
- patch는 주요 버그 수정해서 배포가 된다.
- 2015년에 처음 v1 버전이 출시되었다.
- alpha 태그가 붙은 버젼은 버그가 있을 수 있다.
- beta 태그가 붙은 버젼은 더 안정화 된 버젼이다.
- 모든 과정을 거치면 stable 버젼에 합쳐진다.
- 쿠버네티스는 여러 컴포넌트로 구성되며, 컴포넌트별로 버젼이 다를 수 있다.
- kube-apiserver가 다른 모든 컴포넌트와 연결되므로, 다른 컴포넌트들은 적어도 kube-apiserver의 버전보다 높아서는 안된다.
- 이렇게 호환을 지원하므로 운영 중에 컴포넌트들의 버전을 업그레이드 할 수 있다.

### When to upgrade version
- 가장 최근 릴리즈 된 3가지 버전만 support한다.
- 업그레이드는 다음 마이너 릴리즈로만 가능하다.
- GCP 같은 서비스를 사용하면 업그레이드 버튼 만으로 가능
- kubeadm으로 설치했다면 kubeadm upgrade plan, apply로 가능
- 그 외로 직접 수동으로 가능하다.

### kubeadm kubernetes version upgrade
- 업그레이드는 마스터 노드와 워커 노드 업그레이도 나뉨
- 먼저 master를 다운시키고 업그레이드를 진행한다. 이 기간 동안에는 클러스터 내부 자원에 kubectl로 접근 불가
- 전체 노드들을 한꺼번에 업그레이드 하는 방법이 있다. 이 경우 서비스 중단이 발생
- 노드 하나씩 업그레이드도 가능, 특정 노드에 동작하는 파드를 다른 노드에 옮기고 해당 노드를 업그레이드 하는 방식
- 다른 방식은 새 버전의 쿠버네티스가 설치된 새로운 노드를 추가하고 기존 파드를 옮겨주는 방식이다.
```
$ kubeadm upgrade plan
$ apt-get upgrade -y kubeadm=1.12.0
$ kubeadm upgrade apply v1.12.0
```
- 업그레이드 가능한 버전들을 보여준다.
- kubeadm을 먼저 업그레이드 한 뒤, kubeadm upgrade apply 명령어를 내려준다.

### kubernetes cluster master 버전업
0. apt 업데이트
1. 마스터 노드 drain
2. 클러스터 버전 확인, 맞추고자 하는 버전으로 kubeadm 설치
```bash
$ apt install kubeadm=<원하는 버전>
```
3. kubeadm apply <원하는 버전> 적용할 것
4. 클러스터 버전업은 한단계씩 진행 가능, 순서에 주의!

### kubernetes cluster worker 버전업
1. kubeadm upgrade node
2. 각 노드에 접속, apt install kubelet=1.18.0-00 명령어로 노드의 kubelet 버전을 클러스터 버전에 맞춰줌

