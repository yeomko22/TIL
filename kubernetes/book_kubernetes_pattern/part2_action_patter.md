## 7-8장 batchjob, cronjob
### 문제
- batch job 패턴은 독립된 원자 작업단위 관리 시에 적합하다.
- 파드는 기본적으로 장기 실행 프로세스이다. 
- 그러나 일정 시간의 작업단위를 안정적으로 실행한 후 컨테이너를 종료하는 것도 필요하며, 이때 job을 사용한다.

### job
- restartPolicy를 반드시 onFailure나 Never 값 중에 하나를 사용한다.
- 일시적인 in-memory 작업이 아니라 클러스터 재시작에도 살아남는 지속적인 작업이다.
- 잡은 완료되면 삭제되지 않고 추적 목적으로 유지된다.
- completions, parallelism 등의 설정이 가능하다.

### cronjob
- 주기적으로 실행해야하는 job의 경우 cronjob을 활용할 수 있다.
- 매우 강력한 잡 스케쥴링 시스템이다.

### 9장 데몬 서비스
- 데몬 서비스 패턴은 주로 관리자가 쿠버네티스 플랫폼 기능을 향상시키기 위해서 노드에 특화된 파드를 실행하는 데 사용된다.
- 운영 시스템 레벨에서 데몬이란 백그라운드 프로세스로 실행되는 장기 실행, 자가 회복 프로그램이다.
- 쿠버네티스의 데몬 서비스는 분산 플랫폼에 맞추어 백그라운드 기능을 제공하는 파드라고 생각하면 된다.

### Daemonset
- 데몬세트의 주요 목적은 모든 노드 혹은 특정 노드 위에 단일 파드를 계속 실행시키는 것이다.
- nodeSelector 필드에 라벨 값을 부여해서 특정 노드 위에만 데몬 세트를 통해 파드를 띄울 수 있다.
- 로그 수집기, 메트릭 익스포터, 큐브 프록시 등을 이러한 형태로 배포한다.

## 10장 싱글톤 서비스
- 싱글톤 패턴은 동시에 하나의 애플리케이션 인스턴스만 활성화시키지만 고가용성을 보장한다.
- 싱글톤 패턴은 다음과 같은 상황에서 필요하다.
  - 주기적으로 실행되는 작업이며, 한번에 하나의 작업만 수행되어야 한다.
  - 특정 자원에 대해 폴링을 수행하는 서비스
  - 메세지 브로커로부터 순차적 메세지 컨슘

### replicaset을 이용한 싱글톤
- replicaset의 replica 개수를 1로 설정하여 싱글톤을 구현
- 하지만 이는 엄격한 의미에서의 싱글톤이 아니다.
- replica의 의미는 최대한이 아닌 최소한으로, 상황에 따라서 1개 이상의 파드가 실행될 수 있다.
- 엄격한 의미의 싱글톤을 구현하려면 statefulset를 사용해야한다.

## 11장 스테이트풀 서비스
- 스테이트풀 애플리케이션의 모든 인스턴스는 고유하며 오래 지속되는 특성을 지닌다. 또한 다른 파드로 대체 불가하다.
- 몽고디비, 레디스, mysql과 같은 것들이 해당한다.

### 스테이트풀 요구사항
- 스테이트풀 애플리케이션은 각자 고유한 스토리지 영역이 필요하다.
- 만일 레플리카세트에 볼륨을 마운트할 경우 모든 인스턴스들이 동일한 스토리지 공간을 공유하게 된다.
- 스테이트풀 애플리케이션은 각자 고유한 네트워크 식별자가 필요하다. 일반적인 서비스를 연결할 경우 로드밸런싱을 통해 각각의 애플리케이션을 구분할 수 없다.
- 이러한 요구사항을 StatefulSet가 만족시킬 수 있다.

### StatefulSet
```
apiVersion: apps/v1
kind: StatefulSet
metadata:
  name: rg
spec:
  serviceName: random-generator
  replicas: 2
  selector:
    matchLabels:
      app: random-generator
  template:
    spec:
      conatainers:
      - image:
        name:
        volumeMounts:
        - name:
          mountPath: 
  volumeClaimTemplates:
  - metadata:
      name: logs
    spec:
      accessModes: ["ReadWriteOnce"]
      resources:
        requests:
          storage: 10Mi
```
- volumeClaimTemplate로 각 파드별 pvc를 만들어준다.
- 서비스의 경우 헤드리스 서비스를 정의해준다. 이는 kubeproxy에 의해 처리되지 않으며, ClusterIP의 할당이나 로드 밸런싱이 되지 않는다.
- 헤드리스 서비스를 정의하면 파드 이름으로 도메인을 사용할 수 있다.
- 최대한 1개의 조건을 만족시킬 수 있어서 엄격한 싱글톤 패턴의 구현이 가능하다.

## 12장 서비스 디스커버리
- 쿠버네티스에 배포된 애플리케이션은 클러스터 내 다른 서비스나 외부 시스템과 상호작용해야한다.
- 쿠버네티스 안에서 파드는 배포되는 노드가 변경될 수 있고 이에 따른 IP도 변경될 수 있다.
- 이렇게 동적인 쿠버네티스 파드의 종단점을 추적, 등록, 디스커버리하는 것은 어려운 일이며, 이를 서비스 디스커버리 패턴이 수행한다.

### 서비스 디스커버리
- 쿠버네티스에서 클러스터 내 다른 서비스를 호출할 경우 먼저 kube-proxy에 요청을 보낸다.
- kube-proxy는 서비스 레지스트리에 요청을 보내어 요청을 수신할 파드의 IP를 획득한다.
- 그 후 선택된 엔드포인트에 요청을 보내게 된다.
- 쿠버네티스는 dns 서버로 서비스 레지스트리를 구성하고, coredns가 현재 그 역할을 수행한다.
- 외부에서 쿠버네티스 클러스터 내 서비스 디스커버리를 하는 방법으로는 nodeport, load balancer, ingress가 있다.
- ingress의 경우 ingress controller deployment 필요하다. 실질적으로 외부 트래픽을 수신해서 클러스터 내로 전달해주는 작업은 컨트롤러가 수행하며, 클라우드 제공자에 따라서 다르므로 주의한다.
- ingress object는 ingress controller에게 rule을 주입하는 것으로, 이를 통해 도메인 적용, ssl 적용, 라우팅을 수행할 수 있다.

## 13장 자기 인식
- 파드 설정에 런타임 시에 알 수 있는 정보들을 넣고 싶을 수 있다. 가령 Ip, host, pod name 등이 그러하다.
- 이를 자기 인식이라고 하며 쿠버네티스에서는 downward api를 통해 구현할 수 있다.
- downward api는 파드가 생성된 이후 kube-apiserver에 요청을 보내고, 이를 환경 변수의 형태로 파드에 주입시키는 방식으로 동작한다.
```
spec:
  env:
  - name:
    valueFrom:
      fieldRef:
        fieldPath: status.podIP
  - name:
    valueFrom:
      resourceFieldRef:
        containerName:
        resource: limits.memory
```
- fieldRef 필드 아래에 status.podIP 값으로 자기 자신의 정보를 넣는다.
- resourceFieldRef 값을 활용해 특정 컨테이너의 정보를 넣는다.
```
volumes:
- name: pod-info
  downwardAPI:
    items:
    - path: matchLabels
      fieldRef:
        fieldPath: metadata.labels
```
- volume을 사용해서 downwardAPI를 사용할 수도 있다.
