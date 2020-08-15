## Vagrant를 이용한 실습 환경 구성
### why vagrant?
- 프로비져닝이 쉬워진다.
- 프로비져닝: 사용자의 요구에 맞게 시스템 자원을 할당, 배치, 배포해두었다가 필요 시 시스템을 즉시 사용할 수 있는 상태로 미리 준비해두는 것
- 미리 앤서블을 설치한 노드 스펙을 정의해놓고, 원하는 클라우드 프로바이더에 인프라를 띄울 수 있다.

### vagrant 기본 명령어
```
$ vagrant init: 프로비저닝 예제 스크립트 생성
$ vagrant up: 프로비저닝 진행
$ vagrant halt: vagrant 호스트 종료
$ vagrant destroy: 생성한 가상머신 모두 삭제
$ vagrant ssh: vagrant 호스트에 ssh 접속
$ vagrant provision: vagrant 호스트의 설정 변경을 적용
```

### vagrant 파일 다루기
- vagrant init을 하면 해당 디렉터리에 Vagrantfile을 생성
- config.vm.box = "base"에서 base 대신 원하는 OS를 지정
```
Vagrant.configure("2") do |config|
  config.vm.box = "centos/7"
end
```
- 호스트 OS와 가상머신 간의 공유 폴더를 synced_folder 옵션에서 지정할 수 있으며, 강의에서는 일부러 설정 안함.
- vagrant up을 하기에 앞서서 플러그인을 설치, 강의의 경우 virtual box를 가상머신 엔진으로 사용하므로 vagrant-vbguest라는 플러그인을 설치해야한다.
```
$ vagrant plubin install vagrant-vbguest
```

### Vagrantfile 수정해야할 부분
1. vagrant에서 부르는 호스트 이름 작성
2. 버츄얼박스에서 구분하는 호스트 이름 작성
3. 가상머신 호스트 이름 변경
4. 호스트 pc와 가상머신 간에 공유 디렉터리 설정 해제
5. 가상머신에서 인터넷으로 연결되는 IP 설정
6. 호스트 PC의 포스를 IP 주소와 유사하게 변경

### Vagrantfile 샘플
```
Vagrant.configure("2") do |config|
  config.vm.define:"ansible-server" do |cfg|
    cnf.vm.box = "centos/7"
    cnf.vm.provider:virtualbox do |vb|
      vb.name="Ansible-Server(Udemy-Bloter)"
    end
    cfg.vm.host_name="ansible-server"
    cfg.vm.synced_folder ".", "/vagrant", disabled: true
    cfg.vm.network "public_network", ip: "192.168.1.10"
    cfg.vm.network "forwarded_port", quest: 22, host: 19210, auto_correct: false, id: "ssh"
    cfg.vm.provision "shell", path: "bootstrap.sh"
  end
end
```
- do를 선언했다면 반드시 end로 닫아줄 것 (shell script와 유사)
- |config|, |cnf| 아래에 세부 설정 값들을 넣어줄 것
- 인터넷 상에서 패키지를 다운로드 받아야 하므로 public_network와 IP를 지정해준다.
- provision에다가 shell과 미리 만들어놓은 shell script 파일을 넣어주어 프로비져닝을 진행


### bootstrap.sh 생성
- vagrantfile 안에 너무 많은 내용이 담기게 될 경우 관리가 불편해지므로 별도의 쉘 스크립트로 빼준다.
- yum을 통해 EPEL(원격 패키지 저장소), ansible 설치

### ansible playbook을 만들어서 ansible 제작환경 추가
- Vagrantfile에 추가할 내용
  - Ansible_env_ready.yml 파일을 앤서블 서버에 전달
  - Ansible_env_ready.yml 파일을 앤서블 서버에서 실행
- bootstrap.sh에 추가할 내용
  - vim plugin 관련 파일이 저장될 디렉터리 생성
    - /home/vagrant/.vim/autoload
    - /home/vagrant/.vim/bundle
  - vim과 bash의 환경 설정 파일을 생성

### Ansible_env_ready.yml
```

```
- vim-enhanced, git 설치
- pathogen.vim 다운로드
- vim-ansible-yaml을 git clone 통해 다운로드
- vim의 환경설정을 수정
- bash 환경설정을 수정

### bootstrap.sh
```
# ansible 설치
yum install epel-release -y
yum install ansible -y

# ansible-playbook 개발 환경 셋팅
mkdir -p /home/vagrant/.vim/autoload /home/vagrant/.vim/bundle
touch /home/vagrant/.vimrc
touch /home/vagrant/.bashrc
```
- vagrantfile에서 이 쉘 스크립트 파일을 가상머신 호스트에 전달하고 실행한다.
- 이 때 이 쉘 스크립트의 명령어들이 멱등성을 해치지 않도록 주의한다. mkdir -p의 경우 폴더가 이미 존재한다면 다시 생성하지 않고, touch의 경우에도 파일이 이미 존재할 경우 추가 생성하지 않는다. 이처럼 여러번 실행해도 결과가 동일하도록 스크립트를 구성한다.

### 실행 순서
1. vagrantfile을 통해서 가상머신 생성
2. vagrantfile에서 bootstrap.sh 스크립트 호출, ansible 설치 및 ansible-playbook 개발환경 셋팅
3. Ansible_env_ready.yaml 플레이북을 실행해서 vim plugin, vim ansible plugin 등의 설치를 진행
