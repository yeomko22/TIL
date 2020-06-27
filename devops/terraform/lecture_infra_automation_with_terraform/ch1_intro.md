### Terraform이란?
- Infra as code, 인프라 자동화
- infra를 특정한 상태로 맞춰줌
- 예를 들어 인스턴스 2개에 로드 밸런서 1개라고 설정하면 이 상태로 항상 유지되도록 맞춰줌
- 인프라를 auditable하게 맞춰줌
- git 등의 버전 관리 툴로 인프라를 관리할 수 있다.
- Ansible, Chef, Puppet 같은 툴들은 설치와 설정에 포커스가 맞춰져있다.
- Terraform은 인프라의 프로비져닝을 자동화한다.

### Terraform HCL(Hashicorp Configuration Language)
```
$ terraform console
> var.myvar
```
- terraform은 .tf 확장자로 설정 파일을 만들며, 자체 콘솔에서 이 파일에서 정의한 변수를 사용할 수 있다.

### Terraform plugin
- terraform에는 여러 provider들이 있으며 aws도 그 중 하나이다.
- provider를 이용하려면 플러그인을 설치해야하고, 아래 명령어로 설치가 가능하다.
```
$ terraform init
```
