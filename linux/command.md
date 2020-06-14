### Linux 기본 명령어 정리
```
$ touch
```
파일의 날짜 시간 정보를 변경하는 명령어. 아무런 옵션없이 사용하면 서버의 현재 시간으로 파일의 최근 사용한 시간과 최근 변경 시간을 변경한다. 특정 옵션이 적용되지 않는다면 크기가 0인 빈 파일을 생성한다. -t 옵션을 주면 지정된 시간으로 파일의 날짜 시간 정보를 변경한다.

```
$ yum list | grep '라이브러리명'
```
yum을 통해서 설치한 패키지가 제대로 깔려있는지 확인하는 명령어

```
# nginx 프로세스가 잘 살아있는지 확인
$ systemctl status nginx

# firewall process 종료
$ systemctl stop firewalld
```

