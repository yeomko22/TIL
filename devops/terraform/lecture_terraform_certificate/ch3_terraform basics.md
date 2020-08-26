### Provider
- Terraform은 100개가 넘는 provider를 지원하며, AWS, GCP, Azure 등 메이저 프로파이더를 선택할 수 있다. 

### Terrafom AWS 시작하기
- 연동하고자 하는 AWS 계정에서 사용자 계정을 추가, access key와 secret 키를 생성
- tf 파일을 작성, 원하는 ami 이미지 이름과 인스턴스 타입을 명시
- tf 파일이 담겨있는 폴더로 이동한 다음, terraform init 명령어로 실행에 필요한 플러그인들을 설치
- terraform plan, terraform apply로 인프라 프로비저닝 적용
- terraform destroy로 프로비저닝한 인프라 삭제
- terraform destroy -target=<리소스타입.리소스이름>으로 특정 리소스만 지정해서 삭제가 가능
- 혹은 주석처리하고 terraform apply를 하면 해당 리소스를 삭제한다.

### Providers & Resources
- provider를 적어주고 terraform init을 하면 이 부분을 읽어서 필요한 플러그인을 다운로드하는 것이다.
- provider가 제공해주어야 하는 것들
- 예를들어 aws_instance, aws_alb, iam_user 등이 있다.

### Terraform State Files
- terraform은 우리가 테라폼 파일을 통해서 설정한 상태를 기억하고 있다. 이를 기억하고 있는 것이 바로 terraform state file이다.
- 리소스를 추가하면 state file에 관련 내용을 추가하고, 삭제하면 이를 반영한다.
- terraform plan 시에 (known after apply)로 표기되는 정보들은 리소스를 생성한 후에야 state file에서 확인 가능한 정보들을 의미한다.
- 만일 콘솔 상에서 수동으로 리소스에 변화를 준 뒤, terraform plan을 하면 자동으로 변화를 인식한다. 그 뒤 terraform apply를 하면 tf 파일에 기재되어 있는 상태로 리소스를 되돌린다. 그러므로 terraform을 사용하기로 했다면 수동으로 리소스를 변경하는 것을 지양해야 한다.

### Desired State & Current State
- Desired State는 tf 파일에 기재된 상태를 말한다.
- Current State는 현재 Running 상태로 동작하는 리소스들을 말한다.
- 수동 조작으로 리소스를 변경한다면 Current Desired State와 Desired State와 차이가 날 수 있다.
- terraform refresh 명령어로 Current State를 받아와서 tfstate에 반영할 수 있다.
- terraform plan을 실행하게 되면 자동으로 refresh를 수행한다. 즉, refresh를 통해서 current state를 읽어오고, current state를 desired state와 맞추기 위해서 어떠한 작업을 수행해야 하는지를 결정하는 방식이다.

### Challenges to manage Current State
- 수동으로 새 보안 그룹을 생성하고 이를 적용하였다.
- 그렇다면 Current State에 변화가 발생하고, terraform plan 시에 이를 감지할 수 있어야하지만 No Changes가 뜬다.
- 이는 tf 파일에서 리소스의 이미지, 인스턴스 타입만 명시했기 때문에 그 외 속성들에서 발생하는 변화는 변화로 감지하지 않기 때문이다.

### Terraform Provider Versioning
- provider 자체가 여러 버전을 가질 수 있다. 그리고 각 버전별로 테라폼 플러그인이 각각 릴리즈 된다.
- terraform init 시에 프로바이더의 버전이 명시되어 있지 않다면 그냥 latest 버전의 플러그인을 다운로드 받는다.

### Terraform Provider 종류
- HashiCorp Distributed: terraform init으로 자동으로 다운로드 가능함
- 3rd Party: 써드파티 개발 provider는 terraform init으로 다운로드 불가능
- major cloud는 자동 다운로드가 가능함. community providers는 자동으로 다운로드가 불가능
- 써드 파티 플러그인의 경우 ~/.terraform.d/plugins 아래에 소스 코드를 담아주면 된다.

