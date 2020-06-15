### 우선순위 큐 응용
프로그래머스 - 라면 공장 문제  
힙에 한꺼번에 공급량을 넣는 것이 아니라 단계적으로 넣는다.  
밀가루가 필요한 시점에 최대 공급량을 꺼내온다.  

### c++에서 문자열 다루기
문자열 -> 숫자: stoi 혹은 stol, 숫자가 크면 stol을 써줘야지 안그러면 에러 발생
숫자 -> 문자열: to_string()
캐릭터 -> 숫자: (int)c - 48, 그냥 int를 취해주면 아스키 코드가 나오기 때문
정렬 -> sort(s.begin(), s.end(), greater<char>()) reverse 옵션이 필요할 경우 greater를 추가해준다.
       문자열 그 자체로도 정렬에 적용할 수 있다.
정렬을 할 경우 #include <algorithm>을 추가해준다.

### c++ math.h 유용한 기능들
C++에서 숫자를 다룰 때에는 자료형에 유의할 것. long long으로 처리해야만 에러가 발생하지 않는다. 
powl을 사용하여 큰 수의 제곱을 구할 수 있다.
sqrt로 제곱근을 구할 수 있다.

### c++ algorithm 유용한 기능들
int min_value = *min_element(arr.begin(), arr.end());
int pos = find(answer.begin(), answer.end(), min_value) - answer.begin();
answer.erase(answer.begin() + pos);
