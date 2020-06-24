### Flow
1. push to github
2. travis automatically pulls repo
3. travis builds a test image, test code
4. travis builds prod imgages
5. travis push built prod images to docker hub
6. travis push project to AWS EB
7. EB pulls images from dockerhub, deploys

### production 환경 react 앱 배포
![production_react](../../../images/production_react.png)
- react 앱 빌드 후 nginx 이미지에서 카피해와서 서빙
- 이 때 포트를 3000번으로 개방
- 그리고 앞단에 nginx proxy를 두어서 라우팅을 연결해준다.
- 즉, nginx 프로세스가 총 두개 뜨게 되는 것

### travis error
- create-react-app으로 프로젝트를 생성하면 자동으로 .git 폴더를 생성
- 이는 자동으로 submodule이 잡히면서 travis에서 docker build 시에 에러를 유발
- 따라서 자동으로 생성되는 .git 폴더를 지워줘야 한다.
- travis에서는 sync github으로 변화를 반영해준다.

### AWS Elastic Container Service
- Beanstalk는 multi container 서빙에 적합하지 않다.
- Dockerrun.aws.json 파일을 추가적으로 작성해서 사용이 가능하며, 이는 docker-compose.yml과 유사한 기능을 한다.

### Dockerrun.aws.json
```
{
  "AWSEBDockerrunVersion": 2,
  "containerDefinitions": [
    {
      "name": "client",
      "image": "yeomko/multi-client",
      "hostname": "client"
      "essential": true
    }
  ]
}
```
- 여기서 hostname이란 aws container service에서 컨테이너끼리 서로 접속할 때 사용하는 이름으로 docker-compose에서는 서비스명에 해당한다고 보면 된다.
- essential 필드가 true인 경우 해당 컨테이너가 크래시가 나면 나머지 컨테이너들도 자동으로 꺼지게 된다.
- containers에서 적어도 하나는 essential로 설정해주어야 하며 예제에서는 nginx 프록시를 essential로 설정

### cloud db 솔루션을 사용하는 이유
- postgresql과 redis 인스턴스를 사용하기 위해서 AWS RDS와 elastic cache를 사용
- 이런 솔루션들은 프러덕션 배포에 최적화 된 셋팅 값을 제공한다.
- 규모를 키우기에도 쉽다.
- 보안이 더 좋다.
- Elastic Beanstalk에 띄우는 것보다 마이그레이션 하기가 쉽다.
- 자동 백업과 롤백을 제공한다.

### AWS VPC
- 기본 옵션으로는 AWS EB에서 RDS나 EC에 접속할 수 없으므로 추가적으로 설정이 필요하다.
![vpc](../../../images/vpc.png)
- 각 리젼 별로 VPC가 생성되며 별다른 설정을 안하면 default vpc에 인스턴스가 생성된다.

### Security Group(Firewall Rules)
- 어떤 소스의 인터넷 트래픽이 VPC 내의 서비스에 접속할 수 있는가를 설정하는 것
- 여기서는 모든 IP들이 80 포트로 들어오는 트래픽을 허용하며 EB instance에 연결해주어야 함
- Security Group을 하나 생성해주며, 이는 다른 AWS 서비스로부터의 요청을 허용해주는 권한을 갖고 있다.
- 이 Security Group을 모든 인스턴스들에게 부여해줌으로써 외부에서의 접속은 차단하지만, VPC 내부에서는 서로 접속이 가능하게끔 만든다.

### 보안 그룹 생성 및 설정
- vpc 탭에서 security groups로 이동
- 새 보안 그룹 생성
- inbound 규칙에서 개방하고자 하는 포트를 입력하고 소스를 보안 그룹으로 지정한다.

### Elastic Beanstalk
- 이유는 알 수 없으나 EB 단에 최종 배포에서 계속 에러가 발생
- 에러 로그도 제대로 확인이 불가하여 궃이 여기에 시간 쏟지 않고 넘어가려 함
- 핵심은 멀티 컨테이너로 프로젝트를 구성하고, 클라우드 환경에 띄우고 연결하는 것!
