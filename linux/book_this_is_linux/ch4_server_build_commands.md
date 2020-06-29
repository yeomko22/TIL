## 4장 서버 구축 시 알아야할 필수 개념과 명령어
### 시작과 종료
```bash
# 종료
$ poweroff
$ shutdown -P now # 지금 종료
$ shutdown -P +10 # 10분 뒤 종료

# 재부팅
$ reboot
$ shutdown -r
$ shutdown -r +10 # 10분 뒤 재부팅

#  기타
$ shutdown -c # 예약된 shutdown 명령어 취소
```

### 사용자 관리
- 현재 사용자 및 그룹 목록 확인 커맨드
```bash
$ cat /etc/passwd # 사용자 목록 확인
$ cat /etc/group # 그룹 목록 확인
```
- useradd/adduser: 레드햇 계열에서는 동일한 의미, 데비안 계열에서는 다른 의미
- 데비안에서 adduser 명령어로 사용자 계정을 추가하면 자동으로 홈 디렉터리 생성해주는 등 추가 기능 지원
- 사용자 생성 커맨드
```bash
$ useradd newuser
$ useradd -u 1111 newuser # 사용자 추가하면서 id를 1111로 지정
$ useradd -g mygroup newuser # 사용자 추가하면서 mygroup에 포함시킴
$ useradd -d /newhome newuser # 사용자 추가하면서 홈 디렉터리를 지젖ㅇ
```
- 그 외 사용자 관련 커맨드
```bash
$ passwd newuser # 사용자 패스워드 지정
$ usermod -g mygroup newuser # 사용자 그룹 변경
$ userdel -r newuser # 사용자 삭제하고 홈 디렉터리까지 삭제
$ groups newuser # 사용자가 속한 그룹 보여줌
$ groupadd newgroup # 그룹 생성
$ groupmod -n mygroup newgroup # 그룹의 속성 변경, 여기서는 이르므 변경
$ groupdel newgroup # 그룹 삭제
$ groupwd newgroup# 그룹 암호 설정 및 그룹 관리 수행
```

### 파일 권한
- -rw-r--r--: 이런식으로 7개의 글자로 표현, 파일 유형, 사용자 권한, 그룹 권한, 그 외 사용자 권한 의미
- 파일 유형에는 d(디렉터리), -(일반 파일), b(블록 디바이스), c(문자 디바이스), I(링크)가 있다.
- chown {사용자 이름} 파일 이름: 파일 소유자 변경
- chgrp {그룹이름} 파일 이름: 파일 소유 그룹 변경

### 링크
- inode: 리눅스 파일 시스템에서 사용하는 자료 구조로 파일의 메타 데이터를 저장
- hard link 생성하면 원본 파일의 inode를 공유하는 파일을 생성하는 것
- symbolic link를 생성하면 새로운 inode2를 생성하고 여기에 원본 파일의 포인터를 담는다.
```bash
$ ln {링크대상파일명} {링크파일명} # 하드 링크
$ ln -s {링크대상파일명} {링크파일명} # 소프트 링크
```

### RPM과 DNF
- RPM은 yum 이전의 패키지 매니저이다.
- RPM은 의존성 문제가 있었는데 이를 DNF가 해결했다.
- DNF는 RPM과 별도라기 보다는 RPM을 설치하는 편리한 도구이다.
- DNF는 centOS8부터 도입된 yum의 기능을 대폭 개선한 패키지 매니저이다.

### 패키지 저장소
- /etc/yum.repos.d/ 디렉터리 안에 파일들이 담겨져 있음
- 파일 안에는 저장소의 이름, url, 각종 설정 값들이 담겨져 있음
- dnf install {패키지 이름} 실행 방식
  - 1. 먼저 /etc/yum.repos.d 안의 파일들에서 저장소들의 url 목록을 가져옴
  - 2. 그 다음 원격 저장소들에서 다운로드 가능한 패키지들의 목록을 가져옴
  - 3. 패키지 목록에서 현재 설치하고자 하는 패키지와 관련된 패키지들의 주소만 추려냄
  - 4. 다운로드 해야할 패키지들을 원격 저장소에 요청
  - 5. 원격 저장소로부터 자동으로 다운로드 및 자동 설치 진행
