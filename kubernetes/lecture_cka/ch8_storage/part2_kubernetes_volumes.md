### Volumes in Kubernetes
- 컨테이너는 짧은 기간 동안만 존재하며 실행이 끝나면 제거된다.
- 데이터를 영속적으로 남기고 싶다면 볼륨을 사용해야한다.
```
spec:
  containers:
    volumeMounts:
    - mountPath: /opt
      name: data-volume
  volumes:
  - name: data-volume
    hostPath:
      path: /data
      type: Directory
```
### Persistent Volume
- 볼륨 정의할 때 deployment yaml 파일 안에서 정의할 수도 있다.
- 그러나 규모가 커지면 스토리지만 따로 관리해야할 필요성이 생긴다.
- cluster wide 스토리지 리소스들을 만들어놓고, PVC로 이를 선택해서 사용할 수 있다.

### Persistent Volume claim
- pv와 pvc는 서로 다른 오브젝트이며, 이 둘은 서로 바인딩된다. 1:1로 매핑된다.
- 바인딩 시에는 라벨을 사용한다.
- persistentVolumeReclaimPolicy: retain, delete, recycle 등의 옵션을 선택 가능하다. 
