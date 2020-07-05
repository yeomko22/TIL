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
