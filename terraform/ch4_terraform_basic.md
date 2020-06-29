### 파일 분리
- ACCESS_KEY 같은 값들을 git repository에 업로드 하는 것을 피해야 한다.
- 이를 위해서 설정 값들을 담은 vars.tf 라는 별도의 파일에 변수들을 '선언만' 해놓는다.
```
variable "AWS_ACCESS_KEY" {}
variable "AWS_SECRET_KEY" {}
variable "AWS_REGION" {
  default = "eu-west-1"
}
```
- terraform.tfvars 파일에 실제 값들을 담는다.
```
AWS_ACCESS_KEY = ""
AWS_SECRET_KEY = ""
AWS_REGION = ""
```
- provider.tf라는 파일을 생성해서 선언 및 정의된 변수들을 가져와서 AWS provider에 주입한다.
```
provider "aws" {
  acess_key="${var.AWS_ACCESS_KEY}"
  secret_key = "${var.AWS_SECRET_KEY}"
  region = "${var.AWS_RETION}"
}
```
- instnace.tf라는 파일을 만들고 여기에 생성하고자 하는 리소스를 명시한다.
- 정리
  - terraform.tfvars: git에 잡히면 안되는 중요 정보
  - vars.tf: 변수 선언
  - provider.tf: AWS 프로바이더에 환경변수 주입해서 연결
  - instance.tf: 생성하고자 하는 인스턴스 규격 명시

### Provisioning이란?
- 미리 준비해놓고 공급하는 것
- own custom AMI를 빌드해놓고 여기에 소프트웨어를 미리 다 깔아놓는것으로 Packer를 사용
- 표준 AMI로 부팅하고 여기에 스크립트를 통해서 소프트웨어를 설치하는 방법, 이 때 Ansible 등을 사용한다.
- terraform으로 인프라 만들고 ansible로 추가적인 설치를 진행할 수 있다. 즉, 이 둘은 짝궁

### File Upload
- 미리 작성해놓은 conf 파일이나 스크립트 파일을 SSH 프로토콜로 생성한 인스턴스에 업로드 할 수 있다.
- 이 때 로컬 환경에서 rsa 키를 생성하여 tf 파일에 넣어주며, 이 키값을 통해서 생성한 인스턴스와 SSH 통신을 할 수 있게 된다.
```
provisioner "file" # 파일 업로드
provisoner "remove-exec" # 원격 파일 실행
```

### output
```
output "ip" {
  value = aws_instance.example.public_ip
}
```
- 위 예제 코드처럼 output에서 생성한 인스턴스의 ip를 리턴하도록 설정할 수 있다.
- 이를 Ansible-Playbook으로 넘겨서 설정 작업 등을 진행하게 된다.

### Terraform State
- 테라폼은 infra의 원격 상태를 모니터링한다.
- 이를 terraform.tfstate라는 파일에 기록한다.
- apply을 적용하면 새로운 terraform.tfstate와 bacup 파일이 쓰여지게 된다.
- 원격 상태가 변화하였고 apply가 실행되었다면 terraform은 원격지의 상태를 다시 원상 복구 시키는 방향으로 동작한다.
- 버전 컨트롤 툴을 통해서 관리가 가능하다.
- 이 terraform state을 원격에 저장 가능하며 이 때 backend 기능을 사용한다.
- 즉, 여러 사람이 협업을 할 수 있으므로 terraform state를 내 로컬이 아닌 팀원들과 함께 공유 가능한 저장소에 저장해야한다.

### Remote Terraform State
- S3와 같은 저장소를 디스크 공간으로 활용이 가능하다.
- terraform state 뿐만 아니라 민간한 정보들도 backend 저장소에 저장이 가능하다.
- backend 설정 시에는 terraform init을 다시 입력해주어야 한다.
- backend에 잡아주기만 하면 추가적인 설정없이 state 파일을 s3에 저장한다.

### Datasources
- 동적인 정보들을 제공해준다. 
- 예를 들면 AMI의 리스트나 AZ의 리스트를 AWS provider로부터 동적으로 가져올 수 있다.
- 이는 특정 지역의 ec2 ip만 접속을 허가하는 보안 그룹을 만드는데 활용이 가능하다.

### Terraform Template
- customized configuration 파일들을 만들 수 있도록 도와주는 템플릿을 가리킴
- 사용자가 직접 작성한 스크립트 파일을 tf 파일에서 읽어올 수 있으며, 여기에 tf 변수들을 전달하여 가공할 수 있다.
- 그리고 이렇게 사용자 스크립트를 통해 가공한 데이터를 리소스 정의에 사용할 수 있다.

### Other providers
- Google Cloud
- Azure
- Heroku
- Digital Ocean
- Datadog - monitoring
- Github - version control
- Mailgun
등등등 그들의 API를 terraform에 오픈한 프로바이더들이 많이 있다.

### Module
- 모듈로 깔끔하게 코드를 정리할 수 있다.
- 써드파티 모듈들도 사용이 가능하다.
```
module "module-example" {
  source = "github 주소"
}
```
### Terraform Command Overview
- resource definition에 초점을 맞춤
- resource definition을 수정하거나 새로 만드는 기능은 한정적임
- terraforming이라는 툴이 있으며 이러한 기능을 보완해주는 역할을 수행함

```
terraform apply
terraform destroy
terraform fmt
terraform get: 모듈 다운로드
terrafrom graph: 설정 및 실행 계획 시각화
import [options] ADDRSS ID: 특정 아이디 값을 가지고 tfstate 파일을 뒤져서 리소스 값을 찾는다.
output [NAME]: 리소스 값 중에 원하는 값을 출력
terraform plan
terraform refresh: 원격지 상태를 새로고침
terraform remote: 원격 저장소 설정시에 사용
terraform state: advanced state management 시에 사용
terraform taint: 미래에 제거될 것이라 표시해놓는 것
terraform validate: terraform syntax 점검 
```
