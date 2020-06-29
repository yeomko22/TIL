# AWS 접속, 키페어 생성, 보안 그룹 생성
# SSH 키 값과 보안 그룹을 적용하여 ec2 인스턴스 생성하는 tf 파일 예시
# 보안 그룹은 반드시 직접 만든 그룹과 default 그룹을 동시에 적용해 줄 것
provider "aws" {
  profile = "default"
  access_key = var.AWS_ACCESS_KEY
  secret_key = var.AWS_SECRET_KEY
  region  = "ap-northeast-2"
}

resource "aws_key_pair" "example" {
  key_name   = "example"
  public_key = file("~/.ssh/terraform.pub")
}

resource "aws_security_group" "ssh" {
  name = "allow_ssh_from_all"
  description = "Allow SSH, HTTP port from all"
  ingress {
    from_port = 22
    to_port = 22
    protocol = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }
  ingress {
    from_port = 80
    to_port = 80
    protocol = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }
}

data "aws_security_group" "default" {
  name = "default"
}

resource "aws_instance" "example" {
  ami = "ami-01af223aa7f274198"
  instance_type = "t2.micro"
  key_name = aws_key_pair.example.key_name
  vpc_security_group_ids = [
    aws_security_group.ssh.id,
    data.aws_security_group.default.id
  ]
  provisioner "file" {
    source      = "script.sh"
    destination = "/tmp/script.sh"
  }
  provisioner "remote-exec" {
    inline = [
      "chmod +x /tmp/script.sh",
      "sudo sh /tmp/script.sh",
    ]
  }
  connection {
    host        = self.public_ip
    type        = "ssh"
    user        = "ec2-user"
    private_key = file("~/.ssh/terraform")
  }
}
