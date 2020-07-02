### bash shell 기능
- alias
- history
- 연산 기능
- job control
- 자동 이름 완성
- 프롬프트 제어
- 명령 편집

### 셸 프로그래밍 실행
- sh 스크립트파일명 으로 실행 가능
- 실행 권한을 변경한 후에는 ./스크립트파일 명령으로 실행이 가능

### 셸 프로그래밍에서의 변수
- 변수를 미리 선언하지 않는다. 값을 바로 할당한다.
- 변수에 넣는 모든 값은 문자열로 취급한다.
- 변수 이름은 대소문자를 구분한다.
- 변수 대입 시에는 = 양옆에 공백을 없앤다.
- 앞에 $를 붙여서 변수 값을 출력할 수 있다.
```
$ testval=7+5
$ echo $testval # 7+5가 출력 됨
```

### 셸 프로그래밍 숫자 계산
- expr 키워드를 사용하여 숫자 계산이 가능
- 괄호나 * 기호 사용 시에는 반드시 역슬래쉬를 붙여줄 것
```
#!/bin/sh
num1=100
num2=$num1+200
echo $num2 # 100+200 출력
num3=`expr $num1 + 200`
echo $num3 # 300 출력
num4=`expr \($num1+200\)/10\*2`
```
### 파라미터
- 공백을 기준으로 $0, $1, $2, $3에 해당함
```
$ dnf($0) -y($1) install($2) gftp($3)
```

### if문
- 조건 단어 사이에 공백이 있어야 함
- fi 문으로 꼭 if문이 끝났음을 명시해주어야 함
```
#!/bin/sh
if [ "woo" = "woo"]
then
  echo "참입니다"
else
  echo "거짓입니다"
fi
exit 0
```
- =, !=, -n, -z은 문자열 비교시에 사용
- 100 -eq 200 처럼 산술 비교에는 다른 구문 사용
- -eq, -ne, -gt, -ge, -lt, -le, ! 등을 산술 비교 시에 사용
- 파일 처리 해주는 조건문도 사용이 가능, 디렉터리일 경우 참, 읽기 가능이면 참 등의 연산 수행

### case문
- 각 분기문에 ;; 두개씩 붙여주는 것을 잊지 말자
```
#!/bin/sh
case "$1" in
  start)
    echo "시작";;
  stop)
    echo "중지";;
  restart)
    echo "다시 시작";;
  *)
    echo "뭔지 모름";;
esac
exit 0
```

### AND, OR 관계 연산자
```
#!/bin/sh
echo "filename"
read fname
if [ -f $fname ] && [ -s $fname ] ; then
  head -5 $fname
else
  echo "파일이 없거나 크기가 0입니다."
fi
exit 0
```

### for ~in문
```
#!/bin/sh
hap=0
for i in 1 2 3 4 5 6 7 8 9 10
do
  hap=`expr $hap + $i`
done
echo "1부터 10까지의 합: "$hap
exit 0
```
### while문
```
#!/bin/sh
hap=0
i=1
while [ $i -le 10 ]
do
  hap=`expr $hap + $i`
  i=`expr $i + 1`
done
echo "1부터 10까지의 합: "$hap
exit 0
```

### 사용자 정의 함수
- 함수를 만든 뒤에 호출 시에는 함수명만 적어주면 됨
```
#!/bin/sh
myFunction () {
  echo "함수 안으로 들어왔다"
  return
}
echo "프로그램을 시작"
myFunction
echo "프로그램을 종료"
exit 0
```
- 파라미터 전달 시에는 쉘 창에 명령어 적듯 공백으로 구분하여 전달하고, 함수 안에서는 $1 $2 이렇게 수신
```
#!/bin/sh
hap() {
  echo `expr $1 + $2`
}
hap 10 20
exit 0
```

### 그 외 구문들
- break, continue, exit, return 사용이 가능
- until: while 문의 반대로 동작, 조건이 참이 될 때까지 반복 수행
- eval: 문자열 명령문을 인식하고 실행
```
#!/bin/sh
str="ls -l eval.sh"
eval $str
exit 0
```

### printf
- c 언어에서처럼 printf를 사용 가능함
```
#!/bin/sh
var1=100.5
var2="재미있는 리눅스"
printf "5.2f \n\n \t %s \n" $var1 "$var2"
exit
```
