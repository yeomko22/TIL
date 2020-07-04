### 볼륨
- 컨테이너는 기본적으로 상태가 없어서 컨테이너 삭제 시에 저장된 데이터도 삭제됨
- 볼륨을 사용하면 컨테이너를 재시작하더라도 데이터를 유지
- 퍼시스턴트 볼륨을 사용하면 데이터를 저장했던 노드가 아닌 다른 노드에서 컨테이너를 재시작 하더라도 유지 가능
- 쿠버네티스에서 사용 가능한 볼륨 플러그인의 종류는 다양, 클라우드 서비스 제공자에서 제공하는 것들도 있다.
  - awsElasticBlockStore
  - hostPath
  - azureDisk
  - nfs
  - gcePersistentDisk
  - etc
- nfs 볼륨 플러그인을 이용하면 하나의 컨테이너에 볼륨을 붙여서 NFS 서버로 설정하고, 다른 컨테이너에서 이를 가져다 쓸 수 있도록 설정이 가능
- spec.container.volumeNounts.mountPropagation 옵션 사용하면 파드 안의 컨테이너들끼리 혹은 같은 노드에 실행된 파드들끼리 볼륨 공유가 가능

### emptyDir
- 파드가 실행되는 호스트의 디스크를 임시로 컨테이너에 볼륨으로 할당해서 사용하는 방법
- 파드가 사라지면 emptyDir도 사라짐
- 메모리와 디스크를 함께 이용하는 대용량 데이터 계산에 사용

### hostPath
- 파드가 실행된 호스트의 파일이나 디렉터리를 파드에 마운트
- 파드 재시작 시에도 호스트에 데이터가 남는다.
- 도커 시스템용 디렉터리를 컨테이너에서 사용할 때나 시스템용 디렉터리를 마운트해서 시스템 모니터링 용도로 사용 가능

### nfs
- 기존에 사용하는 NFS 서버를 이용해서 파드에 마운트하는 것
- NFS 클라이언트 역할을 수행한다.
- 여러개 파드에서 볼륨 하나를 공유해 읽기/쓰기를 동시에 할 때 사용
- 파드 하나에 안정성이 높은 외부 스토리지를 볼륨으로 설정한 후 해당 파드에 NFS 서버를 설정
- 다른 파드는 해당 파드의 NFS 서버를 nfs 볼륨으로 마운트
-> 이 부분은 직접 프로젝트에 적용해보면서 익힐 것. 추가적으로 gcePersistentDisk의 사용법 역시 익힐 것. 최종적으로는 gcePersistentDisk에 NFS를 올리고, 이걸 공유하는 방식으로 구현해볼 것

### PV, PVC
- PV는 리소스를 의미
- 파드와 별개로 관리, 별도의 생명주기가 있음
- PCV는 사용자가 PV에 하는 요청
- 사용하고자 하는 용량, 읽기/쓰기 모드 등 자신이 원하는 요구사항을 담음
- 쿠버네티스는 볼륨을 파드에 직접 할당하지 않고 중간에 PVC를 두어 분리
- 이는 파드가 각각의 상황에 맞게 다양한 스토리지를 사용할 수 있게 함
- PVC를 거쳐서 사용하므로 파드는 어떤 스토리지를 사용하는지 신경쓰지 않아도 됨
- PV와 PVC는 프로비져닝 - 바인딩 - 사용 - 반환의 생명주기를 갖는다.

### 프로비저닝
- 먼저 PV를 만들어야하며 이를 프로비져닝이라 한다.
- 프로비져닝에는 PV를 미리 만들어두고 사용하는 정적 방법과 요청이 있을 때마다 만드는 동적 방법이 있다.
- PVC는 동적 프로비저닝할 때 StorageClass로 PV를 생성
- PV와 PVC를 연결하는 단계
- 만일 PVC가 원하는 PV가 없다면 요청은 실패, 그러나 원하는 PV가 생길때까지 대기하다가 만들어지면 PVC에 바인딩
- PV와 PVC는 1대1 매핑 관계

### 사용
- PVC는 파드에 설정되고 파드는 PVC를 볼륨으로 인식해서 사용
- 사용 중인 PVC는 임의로 삭제가 불가능

### 반환
- 사용이 끝난 PVC는 삭제되고 PVC 사용하던 PV를 초기화
- 초기화 정책으로 Retain, Delete, Recycle이 있다.