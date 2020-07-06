### docker compose gcp cloud sql proxy
- docker compose로 개발용 컨테이너들을 엮어서 띄워야 하는 상황
- cloud-sql-proxy 컨테이너가 먼저 떠야지만 api 컨테이너가 이를 통해서 디비에 붙는다.
- 이 때 실행 우선순위를 정해주어야한다.
- 이는 docker-compose.yml에서 depends_on을 설정해주면 해결할 수 있다.
```
depends_on:
  - cloud-sql-proxy
```
