### 객체 지향 개괄
- 객체 지향과 절차 지향은 일종의 패러다임이다. 이 둘은 명확하게 구분되는 것이 아니다.

### cpp에서 struct와 class의 차이
- struct는 아무 설정도 없이 멤버 변수를 설정하면 모두 public이다.
- 반면 class는 아무 설정 없이 멤버 변수를 설정하면 모두 private이다.

### cpp 객체 초기화
```
  5 class Player
  6 {
  7 private:
  8     int _health;
  9     int _power;
 10     const string _name;
 11 public:
 12     Player(): Player(100, 50, "noname")
 13     {
 14     }
 15
 16     Player(int health, int power, string name) : _health(health), _power(power), _name(name)
 17     {
 18     }
 19
 20     void print()
 21     {
 22         cout << _name << " : "<<  _health << ":" << _power << endl;
 23     }
 24 };
```
- 위임 생성자(delegating constructor): Player: Player(100, 50, "noname") 문법으로 사용 가능 
- 그냥 생성자를 쓰게 되면 변수를 기본값으로 초기화 한 다음, 대입 연산을 하게 되는 것이다. 따라서 성능이 안좋고, const 변수 초기화를 못하는 한계점이 있다.
- 대신에 member initializer list를 사용하게 되면 성능 상의 이점을 얻을 수 있다.

### 자동으로 생성되는 생성자 삭제
```
Player() = delete;
```
- 기본 생성자를 delete로 두게 되면 컴파일러가 기본으로 생성하는 생성자를 삭제하겠다는 의미

### 소멸자
- 생성자와 마찬가지로 사용자가 직접 정의하지 않을 경우 컴파일러가 자동으로 만들어주며, 마찬가지로 delete로 지정 가능
- new 명령어를 통해서 동적으로 프로그래머가 생성한 객체는 delete 명령어로 직접 삭제를 해주어야 한다. 안그러면 메모리 상에서 할당 해제가 되지 않는다.
- Player player5(5); 처럼 정적으로 생성한 객체는 스코프가 끝남과 동시에 파괴자가 실행되면서 메모리 상에서 할당 해제 된다.
- static 명령어를 붙여서 생성한 객체는 프로그램이 실행되는 동안 한번만 할당이 된다.
```
  1 #include <iostream>
  2
  3 using namespace std;
  4
  5 class Player
  6 {
  7 private:
  8     int _num;
  9 public:
 10     Player(int num): _num(num)
 11     {
 12         cout << "Constructor : " << _num << endl;
 13     }
 14     ~Player()
 15     {
 16         cout << "Destructor : " << _num << endl;
 17     }
 18 };
 19
 20 Player player0(0);
 21 Player* player1 = new Player(1);
 22
 23 void func()
 24 {
 25     static Player player2(2);
 26 }
 27
 28 int main()
 29 {
 30     Player player3(3);
 31     Player* player4 = new Player(4);
 32     {
 33         Player player5(5);
 34         Player* player6 = new Player(6);
 35     }
 36     delete player4;
 37     func();
 38     func();
 39 }

// 출력 결과
Constructor : 0
Constructor : 1
Constructor : 3
Constructor : 4
Constructor : 5
Constructor : 6
Destructor : 5
Destructor : 4
Constructor : 2
Destructor : 3
Destructor : 2
Destructor : 0
```

### 클래스 선언 분리 
- .h 파일을 생성하여 클래스의 정의를 분리한다.
- cpp 파일에서는 헤더 파일을 include 하여 사용한다.
- 만일 헤더 파일에 컴파일 에러가 있다면 이를 include 하는 파일을 저장하는 시점에서 vim이 컴파일 에러를 알려준다.
- 헤더 파일은 컴파일의 대상이 아니다. 복사 붙여넣기를 위해서 존재한다고 보면 된다.

### 헤더 파일을 이용한 함수 선언, 정의 분리
- 단일 정의 원칙 (one definition rule)에 의해서 동일한 함수는 프로그램에서 한번만 정의되어야 한다.
- 만일 특정 cpp 파일이 함수의 정의를 포함하고 있다면, 그 함수를 포함하는 헤더 파일은 한번만 include 되게 된다.
- 그러므로 헤더 파일에는 함수의 이름만 적어놓고, 정의부는 cpp 파일에다가 적는 패턴을 사용한다.

### 헤더 파일 사용법
- Person.h라는 헤더 파일을 만들었다고 가정하자
- 그러면 보통 Person.cpp 파일을 생성하고, 이것이 Person.h를 include 한다.
- 함수의 선언은 헤더 파일에, 함수의 정의는 본체 cpp 파일에 넣어준다.
- 마찬가지로 클래스를 구성하는 함수들도 정의 부분을 cpp 파일로 옮겨준다. 그러면 헤더 파일에는 클래스의 뼈대만 남게 된다.

### 구현과 선언의 분리의 장점
- 누군가가 특정 클래스를 사용하고 싶을 때, 정의 부분을 모른채로 c++ 헤더만 include 하면 된다.
- 약간 자바에서의 인터페이스나 추상 클래스가 떠오른다. 아마도 이러한 c++의 패턴에서 착안한 개념이 아닐까.

### 전방 선언
- 헤더 파일에서 다른 파일에서 정의된 클래스를 사용해야하는 상황에서는 #include를 통해서 읽어오는 것보다 전방 선언을 사용하는 것이 좋다.
```
// Vileage.h
// 1. include를 사용하는 방식

#include "Person.h"

class Viliage
{
private:
  std::vector<Person> persons;
public:
  void add(Person);
}

// 2. 전방 선언을 사용하는 방식

class Person;
class Viliage
{
private:
  std::vector<Person> persons;
public:
  void add(Person);
}

```
- 헤더 파일을 include 한다는 것은 해당 파일의 내용을 현재 파일에 복사 붙여넣기하는 작업을 의미한다. 이는 곧 파일 간에 의존 관계가 생긴 다는 의미이다.
- 프로젝트 규모가 커지면 컴파일 시간이 길어진다. 따라서 이러한 패턴을 잘 활용하는 것이 중요하다.

### pragma once
- 이 헤더파일을 include할 때 컴파일러가 한번만 복사하라라고 지정하는 의미
- 왜냐면 파일 간에 의존관계가 얽히게 되면 특정 헤더파일이 중복되어 복붙이 될 수 있다. 이 경우 one definition rule을 위배한 것이므로 컴파일이 되지 않는다. 이를 미연에 방지하기 위한 장치가 #pragma once이다.
- 그러나 #pragma는 비표준이다! 

### this pointer
- 클래스 내에서 해당 객체 자체를 가리킴
- 자신의 멤버 변수에 접근할 때 this pointer를 사용해서 좀 더 명확하게 표현할 수 있다.
- 자기 자신을 리턴해야하는 경우에 유용하게 사용할 수 있다.
```
Person& compete(Person& person) {
  if (this->getBMI() < person.getBMI())
      return *this;
  else
      return person;
}
```
- this 포인터를 이용한 빌더 패턴
```
    TransactionBuilder& setToID(int toID) {
        _toID = toID;
        return *this;
    }

    TransactionBuilder& setValue(int value) {
        _value = value;
       return *this;
    }
};


int main() {
    Transaction tx = TransactionBuilder()
        .setFromID(1212)
        .setToID(4321)
        .setValue(4321)
        .build();
}
```

### 클래스 내부에서 const의 사용
- 멤버 함수의 뒤에 const를 붙일 수 있다.
```
float getWeight() const {
  ...
}

// 이는 아래 함수와 동일하다.
float getWeight(const Person* this) {

}
```
- 이렇게 const로 지정된 멤버 함수 내에서는 멤버 변수를 변경할 수 없다.
- 특정한 객체를 const로 지정하면 해당 객체의 멤버 변수들은 read-only로 지정된다.
- 바꾸고 싶지 않은 객체는 const 객체로 만들어주어라. 그리고 멤버 변수에 const를 잘 적용해주는 것이 중요하다. 작성자의 의도를 드러내고, 개발자의 실수를 컴파일 타임에 체크해 줄 수 있는 문법을 잘 사용하는 것이 중요하다.

### 정적 멤버
- 프로그램 실행 시에 메모리가 한번 할당되고, 프로그램 종료시에 할당해지 되는 변수
- 멤버 함수를 static으로 설정하면 this 포인터가 넘어가지 않는다. 이는 즉, 멤버 변수에도 접근이 불가능함을 의미한다. 메모리에 올라가는 시점이 다르고, 할당되는 메모리 공간이 다르기 때문!

