### 구조체 임베딩
- go 언어는 클래스를 제공하지 않아서 상속 또한 제공하지 않음
- 구조체 임베딩을 사용하면 상속과 같은 효과를 낼 수 있음
```
type Person struct {
  name string
  age int
}

func (p *Person) greeting() {
  fmt.Println("Hello~")
}

type Student struct {
  Person
  school string
  grade int
}

func main() {
  var s Student
  s.greeting()
}
```
- 구조체 안에 필드 값으로 다른 구조체를 넣어줌 (Person)
- 이를 통해서 상속의 효과를 흉내낼 수 있으며 s.greeting으로 상위 구조체의 메서드를 호출 가능
- 이를 is-a 관계를 맺어준다고 표현하며, 만일 p Person 이렇게 변수로 넣어줄 경우에는 has-a 관계를 맺는다고 표현
- 구조체 임베딩을 사용하면 다중 상속도 구현 가능
- 그러나 go 언어에서는 복잡한 상속 대신 인터페이스를 주로 사용함
- 하위 구조체가 상위 구조체와 같은 이름의 메서드를 가지면 오버라이드 됨

### 인터페이스
- go 언어에서의 인터페이스는 메서드의 집합. 단, 메서드 자체를 구현하지 않는다.
```
type Printer interface {
  Print()
}

type MyInt int

func (i MyInt) Print() {
  fmt.Println()
}

type Rectangle struct {
  width, height int
}

func (r Rectable) Print() {
  fmt.Println(r.width, r.height)
}

func main() {
  var i MyInt = 5
  r := Rectangle{10, 20}
  var p Printer
  p = i
  p.Print()

  p = r
  p.Print()
}
```
- 각각의 구조체는 interface에 정의된 모든 메서드를 구현함

### 덕 타이핑
- 값이나 인스턴스의 실제 타입을 상관하지 않고 구현된 메서드 만으로 타입을 판단하는 것을 덕 타이핑이라 함
- 즉, 어떤 새가 오리처럼 걷고 헤엄치고 꽥꽥 소리 낸다면 그 새를 오리라 부르겠다는 개념
```
type Duck struct {

}

type (d Duck) quack() {
  fmt.Println("꽥!")
}

type (d Duck) feathrers() {
  fmt.Println("오리의 털")
}

type Person struct {

}

func (p Person) quack() {
  fmt.Println("사람이 오리를 흉내")
}

func (p Person) feathers() {
  fmt.Println("사람의 털")
}

type Quacker interface {
  quack()
  feathres()
}

// 인터페이스를 매개 변수로 입력 받는다.
func inTheForest(q Quacker) {
  q.quack()
  q.feathers()
}

func main() {
  var donald Duck
  var john Person
  inTheForest(donald)
  inTheForest(john)
}
```
- 인터페이스를 통해서 오리든 사람이든 inTheForest 함수에 넣을 수 있다.
- 실제로 어떤 구현체 타입이던 간에 구현된 메서드 만으로 타입을 판단한다.
- 빈 인터페이스를 사용하면 모든 타입을 저장할 수 있다.
- 빈 인터페이스에 값을 넘기고, switch 문에서 타입 검사를 통해서 원하는 분기문을 처리할 수 있다.
