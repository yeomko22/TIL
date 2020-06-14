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
