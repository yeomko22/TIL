## 1.1. ML workflow
- ML workflow: 문제 해결을 위한 데이터를 분석/가공하고 학습시켜 모델을 최적화 시킴. 모델들을 서버에 배포시켜 예측을 하는 일련의 과정
- 크게 experiment와 production 단계로 나뉨
- 워크 플로우 기술로는 airflow, argo flow가 많이 사용됨
- 그러나 이러한 워크플로우 기술들은 리소스 관리/스케쥴링 기능은 지원하지 못함. 
- 그래서 리소스 오케스트레이션 플랫폼인 쿠버네티스 위에서 실행되는 ML workflow가 kubeflow이다.

## 1.2. kubeflow
- kubeflow 의 목표는 ML 워크플로우에 필요한 서비스를 만드는 것이 아닌, 각 영역에서 가장 적합한 오픈 소스 시스템들을 제공하는 것
- 새로운 서비스가 아닌 기존에 있던 오픈 소스들의 묶음
- 아래와 같은 컴포넌트들을 제공
    - jupyter notebook
    - main dashboard
    - hyperparameter tuning (kativ)
    - pipeline (kubeflow 핵심)
    - serving (tensorflow serving, shelldon serving, pytorch serving 등을 kubeflow 위에서 할 수 있게 해줌)
    - training
    - etc


