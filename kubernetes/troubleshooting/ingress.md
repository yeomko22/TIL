### ingress 라우팅 설정 문제
- 쿠버네티스 공식 도큐먼트를 보고 minikube에 ingress 셋팅을 시도했으나 실패
- 우선 최신 apiVersion을 사용할 것
- ingress controller 작동 여부를 확인할 것
- annotation의 문제일 수 있으민 잘 확인할 것

### rewrites target 문제
- rewrite target을 그냥 단순히 /로 하면 나머지 패쓰들에 제대로 라우팅이 되지 않는다.
```
nginx.ingress.kubernetes.io/rewrite-target: /$2
spec:
  rules:
    - http:
        paths:
          - path: /upload(/|$)(.*)
```
### GKE ingress 문제
- GKE 상에서 ingress를 사용하려면 ingress-nginx를 먼저 설치해야한다.
- 이는 GCP loadbalancer를 통해 쿠버네티스 내부로 트래픽을 전달하는 입구역할을 한다.
- 이 때 설치와 삭제를 반복하면서 ingress service가 적용이 안되는 현상이 발생하였다.

```
$ helm list
$ helm delete <release-name>
$ helm repo add nginx-stable https://helm.nginx.com/stable
$ helm install nginx-ing nginx-stable/nginx-ingress
```

### SSL 인증서 적용 문제
- SecureSign에서 만원 주고 인증서를 발급받았다. 이를 ingress에 적용하는 과정에서 참 많은 삽질을 했다.
- 먼저 crt 파일에는 가장 위에 원래 crt 값을 넣어주고 그 아래로 chain에 해당하는 값들을 차례로 넣어줘야 한다.
- 이 crt 파일과 key 파일을 클러스터에 올리고 secret을 생성하며 명령어는 아래와 같다.
```
$ kubectl create secret tls {secret 이름} --cert {cert 파일명} --key {key 파일명}
```
- 그리고 가장 중요한게 이 부분 때문에 안되었던 건데 ingress에서 rules 아래에 host에 도메인 이름을 적어주지 않으면 ssl이 적용되지 않는다. 너무 단순했고 상상도 못했던 측면이어서 많은 시간을 소요한 듯 하다. 어찌되었든 ssl 적용으로 https가 잘 동작한다.
