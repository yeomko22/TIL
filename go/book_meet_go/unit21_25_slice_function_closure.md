### 슬라이스
- 배열과 같지만 길이가 고정되어 있지 않으며 동적으로 크기가 늘어남
- 배열과 달리 레퍼런스 타입
- 아래와 같은 문법으로 생성이 가능
```
var a []int = make([]int, 5)
var b = make([]int, 5)
c := make([]int, 5)
```
- 용량 설정이 가능, 용량은 실제 메모리에 할당된 공간, 용량이 가득 찰 경우 자동으로 늘어남
```
var s = make([]int, 5, 10) // 10이 용량
cap(s) // 10 출력 됨
```
- append 함수를 사용하여 슬리이스 뒤에 값을 추가 가능
```
a :- []int{1, 2, 3}
a = append(a, 4, 5, 6)
```
- 슬라이스는 레퍼런스 타입으로 내장된 배열에 대한 포인터를 담는다.
- 따라서 슬라이스 요소를 복사하고 싶다면 copy 문법을 사용해야함
```
a := []int{1, 2, 3, 4, 5}
b := make([]int, 3)
copy(b, a)
```

### 맵
- go언어는 기본 자료형으로 맵을 지원, 해시테이블 또는 딕셔너리라고도 부름
- 키-벨류 형태로 값을 저장
- 레퍼런스 타입
```
var a map[string]int = make(map[string]int)
var b = make(map[string]int)
c := make(map[string]int)
d := map[string]int {
  "hello": 10,
  "world": 20
}
```

### 맵 세부 기능
- range 문법으로 순회 가능
```
for k, v := range myMap {
  fmt.Println(k, v)
}
```
- delete 구문으로 원하는 키값만 삭제가 가능
```
delete(myMap, 삭제하고 싶은 키 값)
```
- 맵 안에 맵이 들어갈 수도 있음
```
map[키 자료형]map[키 자료형]값 자료형
```
### 함수
- 함수 리턴 값에 이름을 붙일 수 있음. 그 경우 return만 호출하면 해당 변수 명이 그대로 리턴됨
```
func sum(a, b int) (r int) {
  r := a + b
  return // r 값을 그대로 리턴, 왜? 리턴 값에 이름을 붙여줬기 때문
}
```
- 함수 자체를 변수에 저장 가능
```
func sum(a, b int) int {
  return a + b
}
func main() {
  var hello func (a, b int) int = sum
  world := sum
  fmt.Println(hello(1, 2))
  fmt.Println(world(1, 2))
}
```
- 변수 뿐만 아니라 슬라이스에도 함수 간단하게 저장이 가능
- 익명 함수의 사용이 가능하며, defer, goroutine, closure에서 유용하게 사용이 가능함
```
func (s string) {
  fmt.Println(s)
}("Hello World")
```
### 클로저
- 클로저란 함수 앙ㄴ에서 함수를 선언 및 정의할 수 있고, 바깥쪽 함수에 선언된 변수에도 접근할 수 있는 함수를 가리킴
```
func main() {
  a, b := 3, 5
  f := func () int {
    return a + b
  }
  y := f()
}
```
- 함수 호출 시에 할당되는 지역 변수는 함수 실행이 끝나면 소멸함
- 클로저를 이용하면 지역 변수가 소멸하지 않고 함수 호출시마다 계속 가져다 쓸 수 있음
- 즉, 함수가 선언될 떄의 환경을 계속 유지하며, 프로그램의 흐름을 변수에 저장이 가능
- 클로저는 함수형 언어의 큰 특징이며 go 언어에서는 클로저를 통해 함수형 언어의 기능을 구현하는 것
