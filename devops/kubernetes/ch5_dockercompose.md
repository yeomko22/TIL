### Docker Composer
여러 도커 컨테이너를 서로 묶어준다. docker cli의 network features로 묶을 수도 있으나, 난이도가 높아 docker compose를 사용한다.

Docker compose의 역할
- 여러 컨테이너를 동시에 시작시킬 때 사용
- docker run에 전달되는 여러 옵션들을 자동화할 때 사용

### services
docker-compose를 쓰기 시작하면서 자주 등장할 용어. docker-compose 안에 redis-server 컨테이너와 node-app 컨테이너를 띄운다면 2개의 services를 갖는다고 말한다.더 자세한 내용은 향후 추가.

### yml 작성 요령
- yml 파일 안에서 -는 뒤에 배열 형태의 정보가 들어갈 수 있다는 의미이다.

### docker compose로 묶어준 redis-server 접근 방법
```
const client = redis.createClient({
    host: 'redis-server',
    port: 6379
});
```
host에 redis-server(docker compose에 입력한 서비스 이름)라고 입력해주면 된다.

### docker compose commands
```
$ docker-compose up (== docker run myimage)
$ docker-compose up --build (== docker build . && docker run myimage)
```
--build 옵션을 넣어주면 빌드 과정을 명시적으로 다시 실행한다. 해당 옵션 없이 실행하면 미리 빌드한 이미지가 있을 경우 이를 시작한다.

### redis docker password 설정
아무 설정 없이 그냥 실행하면 레디스가 protected mode로 실행되면서 접속이 불가능해진다. 아래처럼 커맨드에 --requirepass 1234 옵션을 추가하여 비밀번호를 설정한다.
```
    redis-server:
        image: redis
        container_name: cache
        command: redis-server --requirepass 1234
        ports:
            - "6379:6379"
```

### nodejs 측에서 redis 컨테이너 접속
강의에서는 단순히 서비스 명으로 접속하라고 하지만 좀 더 일반적인 방법으로 REDIS_URL을 환경변수에 넣어주고, 이를 읽어와서 접속하는 방식을 사용하였다.
```
    node-app:
        build: .
        ports:
            - "3000:3000"
        environment: 
            - NODE_ENV=development
            - PORT=3000
            - REDIS_URL=redis://:1234@cache
```
```
redis url 구성: redis://{사용자명}:{패쓰워드}@{컨테이너이름}:{포트, 기본값 6379}
```

### docker-compose 한꺼번에 켜고 끄기
```
$ docker-compose up -d
$ docker-compose down
```

### Automatic Container Restart

exitcode
```
0: 우리가 원해서 종료한 경우
1, 2, 3, etc: 뭔가 잘못되서 종료된 경우
```
restart policies
```
no: 컨테이너가 종료되거나 크래쉬 발생 시에 재시작을 하지 않겠다.
always: 어떠한 경우에도 재시작을 한다.
on-failure: 에러 코드 발생 시에만 재시작을 한다.
unless-stopped: 개발자가 직접 stop을 하지 않는한 항상 재시작을 한다.
```
restart 옵션은 docker-compose 파일에서 아래와 같은 옵션을 주어 설정 가능
```
node-app:
    restart: always
```
