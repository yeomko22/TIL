### 버츄얼 박스 centos 설치
- Ansible 강의 듣기 위해서 설치 진행
- 설치를 다 마친 후에 reboot 수행 시 다시 설치 화면이 뜨는 현상 발생
- 설치 이후에는 ISO 파일을 언마운트 해주어야 부팅이 됨

### Ansible 실험 환경을 위한 가상머신 구축
네트워크: NAT -> 브리지
처음 열어보면 IP가 할당되지 않는 것을 확인 가능
가상 머신 복제 시에 모든 네트워크 어댑터 MAC 포함 설정

hostnamectl set-hostname "원하는 host명"
```bash
$ route get default: 맥북에서 기본 게이트웨이 주소 확인
$ nmtui -> edit connection -> ethernet -> 
  IPv4: 원하는 IP 주소/netmask 비트수 ex) 192.168.1.10/24
  gateway: 192.168.0.1
  automatically connect -> 스페이스 바로 체크
$ systemctl restart NetworkManager
$ ip add를 치면 입력한 ip 주소가 보여야함
$ ping 게이트웨이 ip를 통해 서버가 네트워크 통신을 하는지 확인
```

### 가상머신 DNS 서버 IP 입력
```
$ vi /etc/resolv.conf -> KT 공개 DNS 서버 주소 입력, 168.126.63.1
$ ping google.com을 통해서 DNS 서버를 제대로 이용하는지 확인
$ yum repolist를 통해서 저장소 목록을 제대로 읽어오는지 확인
$ yum install epel-release -y (ansible 패키지를 담고 있는 저장소를 추가해주는 작업)
$ yum install ansible
```
### Ansible 기본 사용
```
$ ansible all -m ping -k
$ vi /etc/ansible/hosts -> 통신하고자 하는 노드들의 IP 주소 값을 입력함
$ ansible all -m ping -k
```
이 떄 host key 교환 에러가 뜨는데 이는 /etc/ansible/ansible.cfg 에서   
host_key_checking = false 부분 주석을 해제해주면 해결

### vim plug 및 ansible vim 설치
1. vim plug 설치 (curl 이용)
2. ~/.vimrc 파일을 생성하고 양식에 맞게끔 내용을 채워 넣음. 핵심은 맨 윗줄과 아랫줄을 기입하고 중간에 설치하고 싶은 플러그인들을 채워넣는다. 여기서는 ansible-vim을 설정
```
call plug#begin('~/.vim/plugged')
Plug 'pearofducks/ansible-vim'
call plug#end()
```
3. vim 설치 및 플러그인 설치 
```
$ yum install vim-enhanced
$ yum install git
$ vim
$ :PlugInstall
```
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

### playbook
계획이 담겨있는 문서. 설치, 파일 전송, 서비스 재시작 등의 모든 과정을 하나의 파일을 통해서 수행이 가능함.

### playbook 멱등성(idempotent)
연산을 여러번 적용하더라도 결과가 달라지지 않는 성질
ex) echo -e "[bloter]\n192.168.1.13" >> /etc/ansible/hosts  
위 명령어를 여러번 실행하면 누적되어 기록되게 되어 사용자의 의도와 맞지 않게됨.  
이를 플레이북으로 만들게 되면 중복 실행해도 전혀 문제가 없다.  

```
playbook yml 파일 예시
---
- name: Ansible_vim
  hosts: localhost

  tasks:
    - name: Add ansible hosts
      blockinfile:
        path: /etc/ansible/hosts
        block: |
          [bloter]
          192.168.1.13
```
tasks: 수행할 작업 목록
hosts: 작업을 수행할 호스트들
blockinfile: 파일 안에 내용을 추가하겠다.
block: | 블록을 설정, 실제 파일에 기록할 내용

playbook 실행 예시
```
$ ansible-playbook bloter.yml
```

### playbook으로 3대의 노드에 웹 서비스 설치 및 기동
```
---
- hosts: nginx
  remote_user: root
  tasks:
    - name: install epel-release
      yum: name=epel-release state=latest
    - name: install nginx web server
      yum: name=nginx state=present
    - name: upload default index.html for web server
      copy: src=index.html dest=/usr/share/nginx/html/ mode=0644
    - name: start nginx web server
      service: name=nginx state=started
```
방화벽 해제
```
$ ansible nginx -m shell -a "systemctl stop firewalld" -k
```

