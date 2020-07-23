### defer
- 함수가 끝나기 직전에 특정 함수를 실행하는 기능
- 여러개의 defer 호출이 있다면 LIFO 방식으로 동작함

### panic & recover
- 에러가 발생한 뒤 종료되는 상황을 패닉이라 함
- out of index 에러가 대표적
- panic(에러 메세지) 키워드를 사용하여 직접 발생시킬 수도 있음
- recover 함수를 사용하면 패닉이 발생했을 떄 프로그램이 바로 종료되지 않고 예외 처리가 가능함
- recover를 실행하면 panic에서 설정한 에러 메세지를 받아올 수 있음.
```
func f() {
  defer func() {
    s := recover()
    fmt.Println(s)
  }()
  panic("Error!")
}

func main() {
  f()
  fmt.Println("Hello World!")
}
```

### 포인터 사용
```
var numPtr *int = new(int)
*numPtr = 1
fmt.Println(*numPtr)
```
```
var num int = 1
var numPtr *int = &num
fmt.Println(numPtr) // 메모리 주소 출력
fmt.Println(&num) // 동일한 메모리 주소 출력
```
- go 언어는 메모리 주소를 직접 대입하거나 포인터 연산을 허용하지 않음
- 매개변수에서 일반 자료형을 사용하면 값의 복사 발생, 매개 변수에 새로운 값 대입해도 원래 값 영향없음
- 매개변수로 포인터를 전달 시에는 원래 값 변경이 가능함

### 구조체 사용
```
type Rectangle struct {
  width int
  height int
}

rect := Rectangle{45, 62}
```
- new 함수로 구조체의 메모리 할당과 동시에 값을 초기화 하는 방법은 없음
- 그러나 New 패턴을 통해서 다른 언어의 생성자를 흉내낼 수 있음
```
func NewRectangle(width, height int) *Rectangle {
  return &Rectangle{width, height}
}

func main() {
  rect := NewRectangle(20, 10)
  fmt.Println(rect)
}
```
- go 언어에서 지역 변수를 계속 참조하고 있다면 스코프를 벗어나더라도 변수가 할당 해제되지 않음
- 구조체를 함수의 매개변수로 넘기고 싶을 때에는 포인터를 사용하자

### 구조체에 매서드 연결하기
- go 언어에는 클래스가 없음. 단, 구조체에 메서드를 연결 할 수 있음
```
func Rectangle struct {
  width int
  height int
}

func (rect *Rectangle) area() int {
  return rect.width * rect.height
}

func main() {
  rect := Rectangle{10, 20}
  fmt.Println(rect.area())
}
```
- func 키워드와 함수명 사잉에 리시버 정의 부분을 추가
- 메서드 안에서 리시버 젼수를 통해 현재 인스턴스의 값에 접근이 가능함
- 리시버 변수를 받을 때에도 포인터를 받거나 일반 변수를 받을 수 있음
- 일반 값 전달 시에는 값의 복사가 일어나서 원래 구조체 인스턴스의 값을 메서드에서 변경이 불가
