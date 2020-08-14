### Terraform functions
- 사용자가 직접 함수를 만들 수 없다. built-in function만 이용 가능하다.
```
locals {
  time = formatdate("DD MMM YYYY hh:mm ZZZ", timestamp())
}
```
- 이처럼 내장 함수를 사용할 수 있다. 공식 문서를 잘 참고할 것

### Data Sources
```
data "aws_ami" "app_ami" {
  most_recent = true
  owners = ["amazon"]

  filter {
    name = "name"
    values = ["amzn2-ami-hvm"]
  }
}
```
- 필요한 데이터를 원격에 요청해서 동적으로 받아올 수 있다.
- 예를들어 기본 ami 이미지 정보는 리젼마다 다르고, 수시로 변경될 수 있다.
- 이를 하드코딩 할 수 있지만, 그보다는 동적으로 리젼에 해당하는 ami 이미지 명을 받아오는 것이 좋다.

### Debugging Terraform
- TF_LOG를 활용해서 디버깅이 가능하다.
```
// 테라폼 상세 로그 확인이 가능
$ export TF_LOG=TRACE
// 상세 로그를 파일에 저장
$ export TF_LOG_PATH=<로그 파일 경로>
```

### Terraform format
- terraform fmt로 가독성을 개선할 수 있다.

### Validating Terraform Configuration Files
- terraform validate 명령어로 신택스 검사를 할 수 있다.

### Load Order & Semantics
- 테라폼은 디렉터리 안의 파일들을 알파벳 순으로 로드한다.
- provider.tf, variable.tf, ec2.tf, iam.tf와 같이 종류별로 파일을 나눠준다.

### Dynamic Block
```
variable "ingress_ports" {
  type = list(number)
  default = [8200, 8201, 8300, 9200, 9500]
}

dynamic "ingress" {
  for_each = var.ingress_ports
  iterator = port
  content {
    from_port = port.value
    to_port = port.value
    protocol = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }
}
```
- 여러 블럭을 쓰기보다 다이나믹 블럭 하나를 만들고 list variable을 이용해서 리소스를 생성할 수 있다.

### Tainting Resources
- 테라폼 리소스를 taint를 하게 되면 다음 terraform apply 시에 해당 리소스를 파괴하고 다시 생성한다.
- 기존에 동작 중인 리소스를 수정할 경우 taint를 적용하고 파괴한 뒤 다시 만드는 것이 일반적이다.
```
$ terraform taint aws_instance.myec2
```
### Splat Expression
```
resource "aws_iam_user" "lb" {
  name = "iamuser.${count.index}"
  count = 3
  path = "/system/"
}

output "arns" {
  value = aws_iam_user.lb[0].arn
}
```
- output에서 index를 지정해서 원하는 정보만 빼내올 수 있다.

### Terraform graph
- 손쉽게 다이어그램을 생성할 수 있으며, 이를 통해 리소스 간의 의존 관계를 확인할 수 있다.
- terraform graph > graph.dot 명령어로 그래프 설정 파일을 생성할 수 있다.
- 시각화는 graphviz 라이브러리를 사용하면 된다.
-  cat graph.dot | dot -Tsvg > graph.svg 명령어로 svg 파일로 바꿔준 뒤, 브라우저를 통해서 렌더링하면 그래프 이미지를 볼 수 있다.

### Saving Terraform Plan to a File
- terraform plan -out=<plan 파일 경로>
- terraform apply <plan 파일 경로>
- 소스 코드 자체는 계속해서 변화할 수 있다.
- 그러므로 plan을 파일로 만들어 놓고, 추후에 적용하고 싶을 때 파일 경로로 apply할 수 있다.

### Terraform Output
- state 파일에서 특정 output variable을 가져올 때 사용한다.
```
resource "aws_iam_user" "lb" {
  name = "iamuser.${count.index}"
  count = 3
  path = "/system/"
}

output "iam_names" {
  value = aws_iam_user.lb[*].name
}

output "iam_arn" {
  value = aws_iam_user.lb[*].arn
}
```
- terraform output iam_arn을 입력하면 그에 해당하는 variable 값을 가져올 수 있다.
