### GKE에서 CloudSQL 연결
- 공식 문서: https://cloud.google.com/sql/docs/mysql/connect-kubernetes-engine?hl=ko
- 파드 안에 cloudproxy 컨테이너를 띄워서 접속하는 방법을 권장, 이를 사이트카 패턴이라 함
- cloudshell 상에서 gcloud iam api를 이용해서 서비스 계정 json을 다운로드 받음
- 그 다음 kubectl create secret generic을 이용해서 json을 secret으로 등록해주고 json은 삭제
- 그 다음 deployment 설정 yaml에서 volume으로 secret을 mount해서 사용하며, 자세한 내용은 소스코드 참고
- 핵심은 수동으로 서비스 계정을 클러스터 내에서 다운로드, 암호화하여 secret으로 등록, 이를 볼륨으로 마운트
