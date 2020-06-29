### 리소스 생성
- 1. IAM 사용자 계정 생성 및 권한 부여, 여기서는 Administrator 전체 권한을 부여
- 2. IAM 사용자 계정의 ACCESS_KEY와 SECRET 키를 가지고 terraform 파일 작성
```
provider "aws" {
  access_key = ""
  secret_key = ""
  region      = "ap-northeast-2"
}

resource "aws_instance" "example" {
  ami           = "ami-0d777f54156eae7d9"
  instance_type = "t2.micro"
}
```
- ami 이미지 값은 ami locator 사이트에서 검색하여 찾는다. (어지간하면 공식 AWS에서 제공하는 것을 기반으로 하는 것이 에러의 위험이 적다. 이것 때문에 꽤나 애먹음)
- terraform apply 적용하면 ec2 instance가 생성
- terraform destroy 적용하면 인스턴스 제거
- terraform plan은 실제 변화를 적용하지 않고 어떤 변화를 적용할지 보여줌. 이를 파일에 담은 다음 terraform apply <파일명>을 적용도 가능

### Terraform Variable Type
- String
- Number
- Bool
- List(type): 항상 정렬된다.
- Set(type): 순서를 보장하지 않으며, 중복 허용하지 않는다.
- Map(type)
- Object: map 같지만 value의 type이 달라질 수 있다.
- tuple: list 같지만 element의 타입이 달라질 수 있다.
- list, map이 제일 자주 사용된다.

### Terraform 개념 정리
- infra provisioning을 자동화 해주는 도구이다.
- infra의 변화를 기록하는 도구이다.
- infra automation 팀이 협업 시에 사용 가능한 도구이다.
- infra의 remote state를 관리하는 도구이다.
- terraform은 configuration management 도구는 아니다. Ansible/Puppet/Chef가 이 분야에서는 더 뛰어나다. Terraform은 infra level의 설정을 관리하는 것이지 software level의 설정을 관리하지 않는다.

