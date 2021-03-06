## 프로젝트 전반
### Q: 가장 기억에 남는 프로젝트는 무엇인가?
- 네이버 클로바에서 인턴쉽을 진행하면서 맡았던 vincent job-manager가 가장 기억에 남는다. 당시 처음 배워보는 go 언어로 개발을 해야했다. 또한 협업을 처음 경험했고, tdd, CI/CD, docker 등의 개념들을 익히면서 개발을 수행해야 했다. 힘든 순간들도 많았지만 많은 것들을 배울 수 있는 시간이었다. 또한 성능 최적화 작업을 처음 수행해보면서 소프트웨어의 구조와 알고리즘에 대해서 치열하게 고민하는 경험을 쌓았다. 개발자로서 한 단계 성장할 수 있었던 기회였기에 기억에 남는다.

### Q: 협업 시 어떤 갈등을 겪었고 어떻게 해결했는가?
- 커뮤니케이션이 힘든 팀원과의 갈등을 겪었고, 대화와 명확한 문서, r&r을 통해 해결했다. 네이버 인턴쉽 기간 당시 내가 맡았던 프로젝트에 뒤늦게 합류한 외국인 팀원이 있었다. 무뚝뚝한 친구였고 초기에 의사소통이 힘들었다. 당시 프로젝트가 어느 정도 진행된 상황이었고 꽤 복잡한 로직을 처리하고 있었다. 문서도 한국어였기에 처음 프로젝트에 대해서 전달하는 것에 어려워 갈등을 겪었다. 이러한 문제에 대해서 해당 팀원과 솔직한 대화를 나누었고, 문제를 반복하지 않도록 명확한 문서를 영문으로 작성했다. 또한 각자가 잘 할 수 있는 영역에서 역할 분담을 새로 하여 갈등 상황을 해결할 수 있었다.

### Q: 어떤 devops 스킬들을 사용할 수 있는가?
- CICD 파이프라인을 구축해봤다.
- 쿠버네티스 클러스터를 구축하고 서비스를 배포할 수 있다.
- terraform, ansible로 인프라의 구성과 설정을 자동화 할 수 있다.

### Q: terraform의 숙련도는 어떻게 되는가?
- 아직 강의를 통해서만 연습해보았다. AWS와 연결하여 인프라를 구성해보았고, tfstate 파일을 클라우드 환경에서 관리할 수 있다. 아직 실제 프로젝트를 진행해보지는 못하였다.

### Q: ansible의 숙련도는 어떠한가?
- 가상 머신을 만들고 ansible playbook을 작성하여 초기 셋팅을 진행해보았다. 마찬가지로 강의만 수강한 상태이고 아직 실제 프로젝트에 적용해보지는 못하였다.

### Q: c++ 코딩 경험이 있는가?
- 알고리즘 문제 풀이를 꾸준히 c++로 하고 있다. 이전에 notaAI라는 회사에 있을 떄 기존 c++ 서버 프로젝트를 분석하고 수정한 경험이 있다.

## groove
### Q: 쿠버네티스 클러스터 구성은 무엇을 참고했는가?
- 책과 강의, 쿠버네티스 샘플 코드를 참고했다.

### Q: 별도의 nfs 파드를 사용한 이유는?
- fileupload pod는 스트리밍 포맷의 파일을 업로드 하고, stream pod는 이를 서빙한다. 이 둘은 공유 파일 시스템이 필요했다. GCP에서 제공하는 Persistent Volume은 ReadWriteOnce 모드 밖에 지원하지 않아서 적절하지 못했다. 서로 다른 노드에 배포된 두 파드에서 모두 접근이 가능하게 만들어 주기 위해서 nfs pod를 만들어서 마운트 시켰다. 

### Q: 프로젝트를 진행하면서 가장 어려웠던 점은 무엇이었는가?
- MSA를 기반으로 전체 서비스의 구조를 설계하는 것이 어려웠다. 특히 스트리밍 서비스를 처음 구현해보아서 먼저 스트리밍에 대해서 이해를 해야했고, 이에 적합한 구조를 고민해봐야 했다. 사운드클라우드라는 서비스의 아키텍쳐를 많이 참고했다.

### Q: 동시 접속자를 얼마나 처리할 수 있는가?
- 현재는 마스터 노드 한대, 워커 노드 3대를 사용하고 있으며, 워커 노드는 1코어를 사용한다. 스트림을 제공하는 파드를 1개 배포해 놓은 상태이고 CPU limit를 0.5로 설정하였다. 실험 결과 브라우저 20개에서 동시에 음악을 재생할 시 stream 파드의 CPU 사용량이 0.1 증가하였으며, 0.5일 경우 100명의 동시 접속자 처리가 가능하다. 코어의 수를 늘려주거나 스트림 파드의 수를 늘려주면 더 많은 동시 접속자를 처리할 수 있을 것이다.

### Q: nginx-rtmp를 설명할 수 있는가?
- nginx의 extension으로 rtmp, hls, dash와 같은 스트리밍 프로토콜을 지원한다. groove는 그 중 hls 프로토콜을 사용하였다. nginx를 선택한 이유는 스트리밍 파일의 서빙 역시 서버의 정적 컨텐츠 서빙이라 생각하였고, nginx에 관련된 기능이 있을 것이라 생각하여 조사 후 적용하게 되었다.

### Q: hls 프로토콜을 사용한 이유를 설명할 수 있는가?
- 기존 음악 스트리밍 서비스들을 분석하여 선택하게 되었다. 사운드 클라우드, 스푼 라디오 등의 서비스를 분석하였고 그 결과 hls 프로토콜을 사용한다는 것을 알았다. 가장 대표적인 프로토콜이기도 하고 ffmpeg 라이브러리를 통해 사용하기도 편리하여 선택하게 되었다.

### Q: 어떻게 프로메테우스와 그라파나를 구축하였는가?
- GKE에서 제공하는 기능을 통해 설치하고 그라파나로 메트릭들을 시각화 해봤다. 하지만 프로메테우스를 돌리는데 들어가는 리소스가 서비스가 요구하는 리소스보다 커서 배보다 배꼽이 크다고 판단하여 내리게 되었다.

### Q: GCP를 선택한 이유가 있는가?
- 크레딧 때문이다. 클라우드 환경에서 쿠버네티스를 운영하려면 적어도 1대의 마스터 노드와 1대 이상의 워커 노드를 운영해야하며 비용적인 부담을 느꼈다. AWS의 경우 EKS가 프리티어 적용이 되지 않았고, 여러대의 워커 노드를 운영하기에 비용 부담이 컸다. 반면 GCP는 300달러 크레딧을 지급해주어 선택하게 되었다.

### Q: 쿠버네티스는 어떻게 공부했는가?
- 강의, 책, 프로젝트, 자격증 취득 순으로 공부를 했다. 먼저 쿠버네티스가 무엇인지 알기 위해 책과 강의를 통해 공부를 했다. 하지만 예제 코드를 따라해보는 것만으로는 체화시키기가 힘들었고 프로젝트를 진행하게 되었다. 그 후 쿠버네티스를 더 깊이있게 이해하기 위해서 CKA 자격증 공부를 하게 되었다.

### Q: CI/CD 파이프라인을 구축했다고 하는데 설명해보아라
- travisCI, Kubernetes를 엮어서 CI/CD 파이프라인을 구축했다. 먼저 github 상에서 dev 브랜치에 마지가 되면 트리거가 발동한다. travisCI 상에서 도커 컨테이너를 빌드하고 이를 도커 허브에 업로드한다. 그리고 쿠버네티스 imperative command를 활용하여 최신 버전의 이미지로 배포되어 있는 deployment들의 이미지를 업데이트 해준다. 

### Q: secret을 사용하여 민감한 정보를 관리했다고 하는데 보안 상의 문제는 없는가?
- 이 부분은 당시 secret이 암호화 기능을 제공하는 줄 알아서 이렇게 서술했다. secret은 base64를 기반으로 데이터를 인코딩 한 후 저장하는 방식으로 보안에 취약하다. 때문에 민감한 정보를 관리할 시에는 추가적인 조치가 필요하다고 생각한다.

### Q: 어떠한 조치를 취할 수 있는가?
- 애플리케이션 레벨에서 암호화를 적용할 수 있다. 예를들어 travisCI에서 사용하는 구글 서비스 계정 json은 travisCI가 제공하는 암호화를 적용하였다. 그 외에 조치로는 vault와 같은 서비스를 이용할 수 있을 것 같다.

### Q: 그렇다면 secret이 configMap과 다른 점은 무엇인가?
- secret은 etcd 상에 저장될 때 암호화 된 뒤 저장된다.
- 또한 노드의 디스크 공간에 저장이 되지 않고, 노드가 삭제될 때 함께 삭제된다.

## 빅데이터 플랫폼
### Q: 가게 단위로 처리할 경우 문제가 발생하지 않는가?
- 맞다. 가게마다 거래 건수가 달랐고 가장 많은 가게의 경우 30만건 가량의 거래 데이터가 있었다. 하지만 생산해야하는 통계 지표는 가게 단위로 바운드가 걸려있는 것이 많았다. 하나의 가게에서 발생한 거래를 다시 쪼개서 분산 처리 할 경우 난이도가 지나치게 높아져서 가게 단위로 진행하였다.

## 기타 인성
### Q: 당신을 꼭 뽑아야 하는 이유는?
- 일을 할 준비가 되어있다. DevOps 기술 스택들을 열심히 익혔고, 프로젝트 경험이 풍부하다. 물론 팀에 합류하게 된다면 많은 것들을 배워야겠지만, 새로운 것들을 빠르게 익히는 것에는 자신이 있다. 신입으로써 어떠한 업무들이 주어질 지 모르지만, devops 분야에 대한 관심과 경험을 바탕으로 주어진 업무들을 잘 소화해 낼 수 있으리라 생각한다. 

### Q: 당신은 얼마나 창의적입니까?


### Q: 당신은 얼마나 빨리 배울 수 있습니까?
