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

### 예외 처리
문제 풀이를 시작할 때부터 인풋값 범위 확인, 비어있는 인풋, 0으로 구성된 인풋, 짧은 인풋 등에 대한 예외처리를 진행해 줄 것

### 최소값
answer 같은 값의 최소값을 설정할 때에는 0으로 하지말고 반드시 limits.h를 include한 다음, INT_MIN 혹은 LLONG_MIN 같은 값으로 설정해줘야한다.

### c++ map 사용
키 값을 지우는 erase는 시간 소요가 많이 된다. 그냥 값을 누적시켜 업데이트 하는 방식으로 접근하는 것이 좋다.

### 자료형 유의할 점
sum을 다룰 때에는 항상 longlong으로 다룰 것, sum을 구할 때 사용하는 변수도 long long으로 잡아주어야 값이 제대로 나옴
```
int solution(vector<int> &A) {
    long long N = A.size() + 1;
    long long sum = (N * (N + 1)) / 2;
    long long curSum = 0;
    for (unsigned int i=0; i<A.size(); i++) {
        curSum += A[i];
    }
    return sum - curSum;
}
```
long long으로 덧셈을 하려거든 미리 따로 빼주어야 한다. 헷갈리기 쉬우니 명심 또 명심하도록
```
#include <algorithm>

int solution(vector<int> &A) {
    if (A.size()<3) {
        return 0;
    }
    sort(A.begin(), A.end());
    for (unsigned int i=0; i<A.size()-2; i++) {
        long long a = A[i];
        long long b = A[i+1];
        long long c = A[i+2];
        if (a + b > c) {
            return 1;
        }
    }
    return 0;
}
```

### 반복할 횟수 잘못 계산
마지막 한 칸 전에서 멈춰야 했었는데 마지막까지 반복해버려서 오답 발생
```
int solution(vector<int> &A) {
    int left = 0;
    int right = 0;
    for (unsigned int i=0; i<A.size(); i++) {
        right += A[i];
    }
    int answer = INT_MAX;
    for (unsigned int i=0; i<A.size()-1; i++) {
        left += A[i];
        right -= A[i];
        answer = min(answer, abs(left - right));
    }
    return answer;
}
```

### 연속된 숫자 중 비어있는 숫자 찾기
쉬운 문제인 줄 알았으나 상당히 까다롭다. 특히 범위를 벗어나는 값의 등장이나 sum이 동일한 테스트 케이스에 대해서 제대로 처리해주지 않는다면 감점을 당하기 매우 쉽다.
```
int solution(vector<int> &A) {
    vector<bool> flag(A.size(), false);
    for (unsigned int i=0; i<A.size(); i++) {
        if ((long long)A[i]>(long long)A.size()) {
            return 0;
        }
        flag[A[i]-1] = true;
    }
    for (unsigned int i=0; i<flag.size(); i++) {
        if (!flag[i]) {
            return 0;
        }
    }
    return 1;
}
```
### 유효 범위 넘어간 값 처리
문제를 잘 읽어봐야한다. 유효한 범위를 넘어서면 -1을 리턴하라는 유형이 있다. 이걸 안해서 감점 당하면 너무 억울할 것이다.

### 리턴값 주의
답이 없을 경우 -1을 리턴해야하는데 문제 안읽어보고 바로 0을 리턴해서 틀림
```
from collections import Counter

def solution(A):
    if not A:
        return -1
    counter = Counter(A)
    dominator = None
    half = len(A) // 2
    for key in counter:
        if counter[key] > half:
            dominator = key
            break
    if not dominator:
        return -1
    return A.index(dominator)
```
### 가장 큰 부분합
```
#include <algorithm>

int solution(vector<int> &A) {
    int maxSum = A[0];
    int subSum = A[0];
    for (unsigned int i=1; i<A.size(); i++) {
        subSum = max(subSum + A[i], A[i]);
        maxSum = max(maxSum, subSum);
    } 
    return maxSum;
}
```
단순한 dp 문제였으며, 혼자서 너무 어렵게 생각해서 안풀렸던 듯
