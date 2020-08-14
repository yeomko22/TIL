### Access Key 관리하기
- aws cli를 설치해서 access key와 secret key를 등록하면 굳이 소스 코드에 이를 기입하지 않아도 된다.

### Resources in Multiple Regions
- 지금까지는 인스턴스 생성 시에 region을 지정하였으나, 지정하지 않을 경우 생성 시점에 유저에게 물어본다.
- region 별로 provider를 생성한다. 그리고 리소스의 속성 값에 provider를 지정해주면 multi region 관리가 가능하다.
```
provider "aws" {
  region = "us-west-1"
}

provider "aws" {
  alias = "mumbai"
  region = "ap-south-1"
}
```
```
resource "aws_eip" "myeip" {
  vpc = "true"
}

resource "aws_eip" "myeip01" {
  vpc = "true"
  provider = "aws.mumbai"
}
```
### Profile
- 하나의 테라폼 프로젝트에서 여러 개의 계정을 사용해야 하는 상황이 있을 수 있다.
- 이 때 profile 속성을 이용하면 된다.
```
provider "aws" {
  alias = "mumbai"
  region = "ap-south-1"
  profile = "account02"
}
```

### Terraform with STS
- 하나의 계정은 권한을 나타내는 role을 가질 수 있다.
```
resource "aws_eip" "myeip" {
  vpc = true
}
```
```
// provider.tf
provider "aws" {
  region = "us-west-1"
  assume_role {
    role_arn = "<원하는 role arn>"
    session_name = "<원하는 세션 이름>"
  }
}
```
- 즉, 테라폼 단계에서 사용자 계정과 role을 연결해서 사용할 수 있다.

### Sensitive Parameter
```
output "db_password" {
  value = local.db_password
  sensitive = true
}
```
- sensivie 표시를 하면 cli output에 출력되지 않는다.
