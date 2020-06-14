### why ansible?
puppet, chef, salt, ansible: 구성 관리의 4대천왕
puppet: 가장 먼저 나옴. 기술적으로 복잡함.
chef: 두번째로 등장. 기술적으로 복잡함.
salt: 정보량이 많지 않고 발전 속도가 빠르지 않음. 에이전트를 필요로 함.
ansible: 에이전트 설치가 필요하지 않다. 관리 받는 대상에 아무런 프로세스가 올라가 있지 않아도 관리 가능.

### Ansible  구성파일
- /etc/ansible/ansible.cfg: 환경 설정 파일
- /etc/ansible/hosts: ansible이 접속하는 호스트들에 파일

### ansible 실행 옵션
- -i: 적용될 호스트들에 대한 파일 (이 값을 설정 안해주면 /etc/ansible/hosts를 읽어오고, -i 값이 설정되어 있다면 해당 파일 안에 입력되어 있는 호스트들에 대해서만 명령어를 수행한다.) 비슷하게 all 옵션 대신에 그룹명(ex. nginx)을 입력해주면 /etc/ansible/hosts 파일에서 해당 그룹의 호스트 주소만 읽어와서 명령어 실행
- -m: 모듈을 선택할 수 있도록
- -k: 패스워드를 물어보도록 설정
- -K: 관리자로 권한 상승
- -list-hosts: 적용되는 호스트들을 확인

### 어떻게 Ansible을 활용할 수 있나요?
- uptime 확인하기
- 디스크 용량 확인
- 메모리 상태 확인
- 새로운 유저 만들기
- 파일 전송하기
- 서비스 설치

```
$ ansible all -m shell -a "uptime" -k
$ ansible all -m shell -a "df -h" -k
$ ansible all -m shell -a "free -h" -k
$ ansible all -m user -a "name=bloter password=1234" -k
```
여러 대의 노드에 대해서 중앙 관리가 가능  
기존에 bash shell 쓰는 거보다 훨씬 편리하다.  

```
$ cat /etc/passwd (생성된 유저 목록 조회)
```

### Ansible의 장점
쉘 커맨드를 여러 노드에 동시에 날리는 툴은 이미 존재한다. 하지만 ansible을 사용하면 해당 커맨드들의 수행 결과를 한 곳에서 모아볼 수 있다.  
때문에 관리자가 더 편리하게 수백 수천대의 서버를 관리할 수 있게 된다.

### 플레이북이란?
플레이북이란 계획이 담겨있는 문서. YAML로 작성  
ex) 대량의 서버에 웹 서비스를 설치 및 기동해야할 때
많은 서버에 NGINX 설치 -> 파일 전송 -> NGINX 서비스 재시작
