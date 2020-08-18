## Bookinfo 튜토리얼
### istio 설치
- 바이너리 다운로드 후 환경변수에 추가
```
$ curl -L https://istio.io/downloadIstio | sh -
$ cd istio-1.6.8
$ export PATH=$PWD/bin:$PATH
```
- istio 설치 후 istio를 사용하고자 하는 namespace에 라벨 추가
```
$ istioctl install --set profile=demo
$ kubectl label namespace default istio-injection=enabled
```
