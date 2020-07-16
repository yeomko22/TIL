### 인증
- 쿠버네티스 API에 접근하려면 인증을 거쳐야 함
- 외부에서 쿠버네티스 API 접근할 수 있는 기본 포트는 6443, TLS 인증이 적용되어 있다.
- 외부에서 접속하려면 kube-apiserver에 있는 인증서와 클라이언트 인증서 사이의 검증을 통과해야함
- 사용자 계정과 서비스 계정으로 인증을 요청
- 사용자 계정: 구글 계정이나 오픈스택의 키스톤, LDAP 등 별도의 외부 인증 시스템에 있는 사용자 정보를 연결해서 사용. 쿠버네티스는 기본적으로 사용자 정보를 저장하지는 않음
- 서비스 계정: 쿠버네티스가 직접 관리하는 사용자 계정

### kubectl config 파일에 있는 TLS 인증 정보 구조