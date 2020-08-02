### Kubernetes 수동 설치
- 먼저 마스터 노드와 워커 노드를 준비, 이는 vagrant와 virtual box를 이용해서 프로비저닝
- 마스터 노드에서 ssh-keygen을 이용해서 공개키와 개인키를 생성. 다음 명령어로 나머지 노드들에 마스터 노드의 공개키를 저장하면 마스터 노드에서 나머지 노드들에 ssh 접속이 가능함.
```bash
$  cat >> ~/.ssh/authorized_keys << EOF
<마스터 노드의 공개키>
EOF
$ ssh worker-1, ssh master-2 등의 명령어 만으로 ssh 접속이 가능해짐
```
- 그 다음 openssl을 이용해서 selfsigned CA를 만든다.
- CA를 이용해 이제 쿠버네티스의 각 컴포넌트들의 인증서를 만들어준다.
- 그리고 이렇게 생성한 인증서 파일들을 다른 마스터 노드에도 동일하게 복사해준다.

