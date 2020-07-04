### ingress 라우팅 설정 문제
- 쿠버네티스 공식 도큐먼트를 보고 minikube에 ingress 셋팅을 시도했으나 실패했다.
- 리액트 앱을 제대로 찾지 못하는 등의 알 수 없는 에러가 반복되었다.
- 해결은 Udemy 강의 내용을 복습하고 해당 강의의 예제 코드를 일부 수정해서 적용해서 해결했다.
- 처음 apiVersion을 가져올 때 extensions/v1beta1을 가져오는 것이 키포인트인 것 같다.
- 또한 로컬 환경에 ingress-nginx 컨트롤러 설치 후 컨테이너가 뜨지 않는 것 같아서 미니큐브를 초기화 한 다음 다시 구성하였다.
- 다시 또 설치할 일이 생긴다면 ingress-nginx 공식 도큐먼트를 보고 따라가자 (쿠버네티스 공식 x)

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
