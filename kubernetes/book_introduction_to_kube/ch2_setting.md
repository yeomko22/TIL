### gcp compute engine을 이용한 클러스터 구축
- 먼저 ubuntu 이미지를 기반으로 compute engine 5대 생성
- 1대의 VM에서 ssh-keygen -t rsa로 ssh키 생성
- gcp > compute engine > metadata에 가보면 ssh키라는 메뉴가 있고 여기에 생성한 ssh 키 값 추가
- 그러면 각각의 compute engine의 ~/.ssh/authorized_keys에 해당 키 값이 추가되어 있음
- ssh 키 값 생성한 노드에서 아래 명령어로 접속이 가능
```
$ ssh {호스트 명 ex. instance-3} hostname
```

### kubespray sample
- group_vars: 클러스터 설치에 필요한 설정 내용
- inventory.ini: 설치 대상 서버들의 정보를 설정

