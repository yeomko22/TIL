### Infrastructure as a Code tools
- IaaS 툴들은 Terraform 외에도 많이 존재한다. 
  - Terraform
  - Ansible
  - Chef
  - Puppet
  - Cloud Formation
- 특히 Ansible 같은 경우에는 Configuration Management 툴로 알려져 있으나, 인프라를 배포하는데에도 사용할 수 있다. 그렇다면 이 둘의 차이는 무엇인가?

### Configuration Management vs Infrastructure Orchestration
- Ansible, Chef, Puppet은 Configuration Management 툴로 디자인 되었다. 즉, 이들은 현재 존재하는 서버에 소프트웨어를 설치하고 관리하는데 특화되어 있다.
- Terraform은 infrastructure orchestration 툴로 디자인 되어 있다. 서버와 인프라를 프로비젼 하는데 초점을 맞춘다.
- 테라폼으로 클라우드 상의 인프라를 프로비젼 하고, 그 이후에 앤서블을 통해서 설정을 관리한다.

### Why Terraform?
- 여러 플랫폼을 지원한다. AWS, GCP, Azure 상관없다.
- 자체 Configuaration 언어를 지원하고 배우기 쉽다.
- configuration management 툴과 함께 사용하기에 좋다.
- 다른 플러그인들이 풍부하다.
- 무료다!

### 설치 방법
- 홈페이지에서 최신 버전의 바이너리를 다운 받고, /usr/local/bin 폴더에 넣어준다.

