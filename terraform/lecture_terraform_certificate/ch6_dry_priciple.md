### DRY principle이란?
- don't repeat yourself! 반복을 줄여라
- source에 정보를 담아놓고, 이를 동적으로 할당해주어라
```
module "myec2" {
  source = "../../modules/ec2"
}
```
- 위 처럼 필요한 블럭을 그 때마다 정의하는 것이 아니라, 미리 모듈화 시켜놓고 이를 불러와서 사용한다. 아래는 실제 modules/ec2 예시
```
resource "aws_instance" "myweb" {
  ami = "ami-asdfjlkjf"
  instance_type = "t2.micro"
  security_groups = ["default"]
  key_name = "remotepractical"
}
```
- 모듈을 사용하기 위해서는 terraform init을 다시 수행하여 모듈을 설치해야한다. terraform init <디렉터리 경로>. 이때 모듈 경로는 상대 경로로 적어주면 모듈을 요청하는 파일을 기준으로 상대 경로를 계산하여 모듈을 설치한다.

### Terraform Module에 var 사용하기
- 모듈에 특정 속성을 variable을 이용해서 동적으로 사용하고 싶다면 모듈 정의시에 해당 속성을 variable로 남겨 놓고 모듈을 불러오는 쪽에서 variable 값을 설정해주면 된다.
```
resource "aws_instance" "myec2" {
  ami           = "ami-05a4cce8936a89f06"
  instance_type = var.instance_type
}
```
```
variable instance_type {
  default = "t2.large"
}

module "myec2" {
  source = "../../modules/ec2"
}
```
- 불러오는 측에서 variable을 설정해주면 알아서 모듈에 적용이 된다.

### Terraform Registry
- 테라폼 모듈들을 모아놓은 저장소로 스크래치 단부터 굳이 모듈을 작성하지 말고, registry에서 가져와라!
- verified modules는 HashiCorp에 의해서 리뷰 받았으며 꾸준히 메인테인 되는 모듈들이다.

### Terraform Workspace
- 워크 스페이스에 따라서 default 값들을 다르게 적용할 수 있다.
- terraform workspace 명령어로 관리할 수 있다. 이를 통해서 local, dev, staging, prod 등의 인프라를 손쉽게 관리할 수 있다.
- 
```
$ terraform workspace new dev
$ terraform workspace new prod
$ terraform workspace show
```
```
resource "aws_instance" "myec2" {
  ami           = "ami-05a4cce8936a89f06"
  instance_type = lookup(var.instance_type, terraform.workspace)
}

variable "instance_type" {
  type = "map"
  default = {
    default = "t2.nano"
    dev = "t2.micro"
    prod = "t2.large"
  }
}
```
- terraform.workspace로 workspace 변수에 접근할 수 있다.
- variable의 default 값을 지정할 때 <workspace> = "변수명" 이렇게 map을 생성하고, 이를 workspace 이름으로 접근해서 변수를 사용하면 된다.
- 테라폼은 워크스페이스 별로 tfstate를 관리한다.
- default 워크스페이스의 tfstate는 루트 디렉터리에서 관리된다.
