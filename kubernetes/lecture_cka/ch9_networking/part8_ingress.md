### Ingress
- service와 ingress는 무엇이 다른가?
- 도메인 이름도 넣고 싶고, 트래픽도 분산 시키고 싶고, 포트 매핑도 해주고 싶고, 라우팅도 분리시키고 싶고, ssl도 적용하고 싶다.
![networking_ingress](../../../images/networking_ingress.png)
- 위와 같이 로드밸런서를 붙이고, 로드밸런서들을 다시 이어붙이는 수고를 쿠버네티스 클러스터 내부에서 설정 파일 하나만 가지고 하고 싶어서 만든게 인그레스
