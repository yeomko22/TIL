### 쿠버네티스에서의 tls
- 세 종류의 인증서들이 있다.
  - Server Certificates
  - CA Certificates
  - Client Certificates
- .crt, .pem은 공개키, .key, -key.pem은 개인키

### 쿠버네티스에서 암호화가 필요한 이유
- 쿠버네티스 클라이언트는 마스터 노드와 워커 노드들로 구성되어 있다.
- 클라이언트와 kube-apiserver 간의 통신, 서버들 간의 통신 모두 보안이 확보되어야 한다.
- 그러므로 서버 인증서, 클라이언트 인증서가 모두 필요하다.

### Server Certificates for Servers
- kube-apiserver: apiserver.crt, apiserver.key
- etcd-server: etcdserver.crt, etcdserver.key
- kubelet: kubelet.crt, kubelet.key
- kube-apiserver과 통신 하는 모든 주체들은 자신만의 crt, key 파일을 가지고 스스로를 인증한다.
![kubernetes_crt](../../../images/kubernetes_crt.png)
