### create docker image
도커 이미지의 구성: FS Snapshot + Startup Command
도커 파일 -> 도커 cli -> 도커 server -> usable image

Create a dockerfile
- specify a base image
- run some commnads to install additional programs
- specify a command to run on container startup

### Building a dockerfile
instruction / arguments
```
FROM alpine
RUN apk add --update redis
CMD ["redis-server"]
```
writing a dockerfile == being given a computer with no OS and being told to install Chrome

### build process in detail
1. FROM alpine
- Pulling from librarpy/alpine(이미지 다운로드)
2. RUN apk add --upate redis
- Running in '임시 컨테이너 id'
- 패키지 설치 진행
- 설치 완료, Removing intermediate container '임시 컨테이너 id'
3. CMD ["redis-server"]
- 빌드한 컨테이너에서 실행

컨테이너 빌드 과정
1. base image 받아온다.
2. RUN apk add --update redis 실행 시에는 그 전 스텝을 바라본다. 이전 스텝의 이미지를 본다. 그리고 그 베이스 이미지를 기반으로 한 임시 컨테이너를 만든다. 임시 컨테이너는 베이스 이미지의 파일 시스템 스탭샷을 복사해온다. 그리고 startup command로 RUN 다음에 오는 아규먼트를 실행하여 패키지 설치를 진행한다. 그러면 컨테이너 내의 파일 시스템에 패키지가 깔리게 된다. 그 다음 임시 컨테이너를 멈추고, 그 이미지를 새로운 임시 이미지를 만든다.
3. CMD ['redis-server']을 실행하면 이전에 RUN 단계에서 만든 임시 이미지를 기반으로 임시 컨테이너를 만들고 startup command를 지정한다. 그리고 마찬가지로 임시 컨테이너를 삭제한 뒤, 그 파일 시스템 스냅샷을 최종 이미지로 리턴한다.

### recap
도커 빌드 각 스텝별 세부 사항
1. 이전 단게의 이미지를 가져온다.
2. 임시 컨테이너를 만든다.
3. 해당 스템의 명령어를 수행한다.
4. 임시 컨테이너의 파일 시스템 스냅샷을 뜬다.
5. 임시 컨테이너를 지운다.
6. 복사한 스냅샷으로 다음 스텝에서 쓸 이미지 파일을 준비한다.

### rebuild with cache
빌드 과정에서 각 스텝마다 이미지를 만들었다. 만일 dockerfile의 변경이나 소스 코드의 변경이 일어나서 도커 이미지 빌드를 다시 수행할 경우 캐시를 활용할 수 있다.
그러므로 변경이 자주 일어나지 않는 단계의 명령어부터 위 쪽으로 배치하는 것이 좋다.

### Tagging image
docker id / project name : version(ex. latest)

### Mannual Image generation with docker commit
수동으로 위에서 진행한 과정을 재현할 수 있다.
```
$ docker run -it alpine sh
# apk add --update redis
(another terminal)
$ docker commit -c 'CMD ["redis-server"]'
```
