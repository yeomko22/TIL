### Remote State Management
- 인증 정보들을 버젼 관리 시스템이 트랙킹하지 않도록 주의해야 한다.
- 따라서 인증 정보를 담은 별도의 파일을 만들고, file 함수를 써서 읽어오도록 한 다음, .gitignore에 인증 정보가 담긴 파일을 잡아준다.
- 하지만 인증 정보를 따로 뺀다고 하더라도 terraform apply를 통해서 tfstate 파일이 로컬에 생성되면 그 안에 인증 정보가 담기게 된다. 따라서 tfstate 자체도 버전 관리 시스템이 추적하면 안되며, 별도로 관리해야할 필요가 있다.

### Remote Backend
- 별도의 저장소(remote backends)에 terraform.tfstate 파일만 저장한다.
- 여러 유형이 있지만, AWS를 사용한다면 s3를 사용해서 remote backend를 손쉽게 설정할 수 있다.
- backend 지정 시에는 init을 새로 한 번 수행해주어야 한다.
```
terraform {
  backend "s3" {
    bucket = "mybucket"
    key    = "path/to/my/key"
    region = "us-east-1"
    access_key = "..."
    secret_key = "..."
  }
}
```
- 여기서 key는 별도의 인증 파일을 요구하는 것이 아니라 생성될 tfstate 파일의 이름을 말한다.
- access_key와 secret_key를 직접 넣어주어야 인증이 된다.
- var를 사용해서 변수 주입이 되지 않으니 주의할 것

### State Locking
- tfstate 파일에 쓰기 작업을 수행할 시에 테라폼은 자동으로 락킹을 적용한다.
- terraform plan을 실행하면 tfstate에 락을 건다. 동시에 다른 사람이 terraform plan, apply와 같은 명령어를 수행할 수 없다.
- 이러한 락킹은 backend의 유형에 따라서 지원 여부가 결정된다. s3 backend의 경우에는 지원하지 않는다. 로컬 백엔드는 지원한다.
- s3 백엔드의 경우 dynamodb table을 사용할 경우 락킹의 적용이 가능하다.
```
terraform {
  backend "s3" {
    bucket = "terraform-yeomko"
    key    = "remotedemo.tfstate"
    region = "ap-northeast-2"
    access_key="AKIASBTBRRTLZFVR44EP"
    secret_key="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"
    dynamodb_table = <미리 만들어 놓은 테이블 명>
  }
}
```

### Terraform State Management
- tfstate 파일을 직접적으로 수정하려 하지 말아라. terraform state 명령어를 통해서 수정이 가능하다.
- 파일을 직접적으로 수정하게 되면 상태가 변경되었다고 인식하고 리소스를 삭제하고 새로운 리소스를 생성하게 된다. 이를 피하고 싶다면 tfstate 파일을 직접 수정하는 것은 삼가해야 한다.
- 약간 쿠버네티스의 imperative command의 냄새가 난다. 킁킁
- list, mv, pull 정도만 사용한다. 이 명령어로 직접 리소스를 삭제하는 것은 너무 위험하다. 설령 삭제한다 하더라도 이는 state 파일에서 삭제되는 것이지 실제 인스턴스를 삭제하지 않는다.

### Terraform Import
- IaaS를 사용한다하더라도 팀원 중엔 꼭 수동으로 인프라를 만지는 사람이 있을 것이다.
- 따라서 terraform import를 통해서 현재 상태를 끌어와서 파악하는 것이 중요하다.
