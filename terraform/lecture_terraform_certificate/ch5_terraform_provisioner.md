### Provisioner
- terraform으로 인프라를 만들긴 했으나, 안에는 텅텅 비어있다. 이를 우리가 원하는 애플리케이션을 띄울 수는 없을까? 이 역할을 해주는 것이 Terraform Provisioner!

```
resource "aws_instance" "myec2" {
  ami           = "ami-05a4cce8936a89f06"
  instance_type = "t2.micro"
  key_name = "terraform"

  provisioner "remote-exec" {
    inline = [
      "sudo amazon-linux-extras install =y nginx1.12",
      "sudo systemctl start nginx"
    ]

    connection {
      type = "ssh"
      host = self.public_ip
      user = "ec2-user"
      private_key = file("./terraform.pem")
    }
  }
}
```
- 인프라를 만들고 쉘 스크립트 실행 명령을 전달할 수 있다.
- 이를 앤서블과 같은 설정 관리 도구와 연동하여 사용할 수도 있다.

### Types of Provisioner
- local-exec, remote-exec 두 가지 종류가 있다.
- local-exec는 테라폼이 동작하는 로컬 머신에서 명령어를 실행시킨다.
- remote-exec는 새롭게 만든 리소스에서 동작하는 명령어이다.
- remote-exec로 ansible playbook을 실행시킨다.
