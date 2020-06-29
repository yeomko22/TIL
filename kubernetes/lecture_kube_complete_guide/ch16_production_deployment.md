### GCP가 AWS보다 Kubenetes에 적합한 이유
- google이 kubernetes 만들었다.
- AWS는 최근에 kubernetes 지원을 시작했다.
- GCP에서 사용하는게 훨씬 쉽다.
- 초보자를 위한 문서화가 잘되어있다.

### GCP kubernetes 배포 travis yaml 설정
1. gcloud sdk 설치
2. gcloud auth 인증
3. docker cli login
4. build test version images
5. test
6. 성공 시 이미지 배포
7. 모든 이미지 빌드, 태깅, 도커 허브 푸쉬
8. k8s 폴더 내부에 있는 모든 설정 파일 적용
9. Imperatively set latest images on each deployment

### travis에 service-account.json 업로드하기
1. travis-cli를 실행할 수 있는 도커 컨테이너 띄우기
2. volume으로 연결해서 service-account.json 파일 가져오기
3. travis encrypt-file service-account.json -r yeomko22/multi-k8s 명령어로 암화하 하기
4. travis encrypt-file 명령어 결과로 출력된 커맨드를 travis.yml 파일에 추가하기
5. 암호화 된 파일은 남겨두고 원본 service-account.json 파일은 지워주기
-> 즉, travis가 이해할 수 있는 암호화 방식으로 파일을 암호화하고 원본은 지워주는 것이다.

### kubernetes에 최신 컨테이너 배포하기
- 별도의 deploy.sh 스크립트 파일을 작성하여 travis 상에서 실행
- deploy.sh 안에서는 이미지 빌드 시에 SHA 태그를 생성하여 붙여준다.
- 각각의 이미지는 latest와 git의 commit SHA 태그 두 가지 태그를 달고 빌드된다.
- SHA 태그를 이용해서 imperative 하게 kubernetes 상의 deployment의 컨테이너를 변경해주는 명령어를 deploy.sh 안에서 실행하는 것
- latest 태그를 붙인 이미지와 SHA 태그를 붙인 이미지를 모두 dockerhub에 업로드한다. 그래서 항상 latest가 최신 버전의 이미지로 유지되게 한다.

### Helm 사용
- 로컬 minikube 환경에 ingress 설치를 수동으로 진행했었다.
- 이를 gcloud 상에서 진행해야하며 이 때 Helm이라는 kubernetes pakage manager를 사용한다.
- kubernetes cluster 내부에서 사용하는 써드파티 소프트웨어

### Security with BRAC
- GKE는 기본적으로 RBAC(Role Based Access Control) 보안 모듈을 가지고 있다.
- 이는 클러스터 안에서 누가 어떤 접근을 할 수 있는지를 제한하는 장치이다.
- RBAC 구성
  - User Account: 클러스터를 관리하는 사람을 구분
  - Service Account: 클러스터 내부의 pod을 구분
  - ClusterRoleBinding: 전체 클러스터에 걸쳐서 특정 계정이 어떤 행동을 취할 수 있는 지를 인증
  - RoleBinding: 하나의 namespace 안에서 특정 계정이 어떤 행동을 취할 수 있는 지를 인증
