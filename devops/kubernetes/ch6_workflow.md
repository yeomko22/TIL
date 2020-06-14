### workflow
- development
- test
- deployment
CI 툴로는 travis를 쓸 것
Travis에서 테스트를 거쳐서 AWS로 deploy할 것
AWS는 Beanstalk를 쓸 것

### Docker purpose
CI를 구축하기 위해서 Docker가 필수적인 것은 아니다. 그러나 이 과정을 훨씬 쉽게 만들어준다.

### necessary commands
```
npm run start: for development
npm run test: run tests
npm run build: build production version of the application
```

### Docker Volumns
카피를 해오는게 아니라 참조를 거는 것이다. 로컬 폴더에 참조를 걸고 docker run  실행시에 현재 상태의 소스코드를 가져오는 것.

```
$ docker run -p 3000:3000 -v /app/node_modules -v $(pwd):/app <imageid>
```
첫 번째 -v 옵션을 넣어주지 않으면 실행이 되지 않는다. 왜? 중복 디펜던시 때문에 로컬 환경에서는 node_modules를 지워버렸기 때문에 별도로 -v /app/node_modules를 지정해주어야 한다.

### Docker Volumn 추가 개념
컨테이너 내부에서 파일을 쓰게 되면 writable container layer에 저장이 된다. 그리고 이는 컨테이너가 내려가면 사라지게 된다. data volumn은 호스트의 파일 시스템에 직접 쓰는 것이다.  

컨테이너는 파일을 영속적으로 보관하기 위해 두 가지 방법으로 호스트의 파일 시스템에 파일을 저장한다.
- volumns
- bind mounts
![dockervolumns](../../images/dockervolumns.png)
Volumns는 호스트의 파일 시스템에 도커에 의해 관리되는 영역에 저장한다. (/var/lib/docker/volumns) 도커가 아닌 프로세스는 이 공간을 건드리지 못한다.  

Bind Mounts는 호스트의 파일 시스템 어디에나 파일을 저장할 수 있다. 그리고 도커가 아닌 프로세스도 접근하거나 수정할 수 있다.

volumns 사용 예시
- 여러 컨테이너가 동일한 볼륨을 사용 가능하여 데이터를 공유할 수 있음.
- 도커 호스트가 폴더나 파일 구조를 갖고 있는 것이 보장되지 않을 때 사용. 도커 호스트의 설정과 컨테이너 런타임을 분리시키는데 도움이 됨
- 컨테이너의 데이터를 클라우드나 원격 호스트에 저장하고 싶을 때
- 백업이나 마이그레이션에 유리

```
$ docker run -v: bind mount a volume
$ docker run -v ($pwd):/app
```
즉, COPY 방식은 컨테이너 내부의 파일 시스템에다가 파일을 복사해서 사용하는 방식. 이 경우 소스코드 수정을 반영하기 위해서는 매번 이미지 빌드를 수행해야한다.

그러나 -v 옵션을 쓰는 방법은 volumne에 파일을 올려놓고 이를 docker run 시점에 volume에 올려놓은 파일을 컨테이너 내부로 매핑해와서 사용하는 방식이다.
