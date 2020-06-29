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
```bash
$ cat /etc/passwd # 사용자 목록 확인
$ cat /etc/group # 그룹 목록 확인
```
- useradd/adduser: 레드햇 계열에서는 동일한 의미, 데비안 계열에서는 다른 의미
- 데비안에서 adduser 명령어로 사용자 계정을 추가하면 자동으로 홈 디렉터리 생성해주는 등 추가 기능 지원
```bash
$ 
```
