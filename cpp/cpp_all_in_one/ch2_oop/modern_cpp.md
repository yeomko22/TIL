### auto
- c++14부터 사용이 가능, 자동 데이터 타입 추론을 제공
```
std::vector<int> v;
std::vector<int>::interator it = v.begin();

// 이랬던 문법이 아래처럼 간결해진다.
auto it = v.begin();
```
- 굳이 가독성이 그렇게 중요하지 않은 변수에 한해서 사용한다.
```
std::map<int, int> m;
for (const auto& pair: m) {
  ...
}
```
- 이 경우 pair에 대한 자료형 추론을 제공해주어서 개발자가 실수할 가능성을 막아준다.
- 이처럼 복잡한 타입에 대해서 auto를 사용하면 실수를 줄여주는 효과가 있다.

