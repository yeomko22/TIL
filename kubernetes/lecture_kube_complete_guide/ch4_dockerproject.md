### Nodejs Web app project
1. npm install - dependencies 설치
2. npm start - application 실행

```
FROM node:alpine
RUN npm install
CMD ["npm", "start"]
```
이렇게 실행하면 pakage.json이 없다는 에러가 발생한다.
이는 RUN 단계에서 바라보는 이미지는 node:alpine base 이미지이고, 이를 임시 컨테이너로 만들면 당연히 이 컨테이너의 파일 시스템에는 package.json이 들어있지 않다.
```
COPY 'local path' 'path inside container'
```

```
docker run -p 'localport':'containerport' 'container id'
```
포트 포워딩은 dockerfile 안에서 정의하지 말고 런타인에 따른다. 왜? 런타임에 따라서 달라질 수 있기 때문.
따라서 -p 옵션을 사용해서 컨테이너의 포트를 연결해주어라.

캐시를 최대한 활용할 수 있게끔 package.json만 먼저 복사해서 install을 진행한 다음 나머지 소스코드를 복사해도록하자.
