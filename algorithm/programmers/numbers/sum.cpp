// c++에서 숫자를 문자열로 바꿀 때에는 to_string(int)
// string을 숫자로 바꿀 때에는 stoi(str)
// char를 숫자로 바꿀 때에는 (int)c
// 문자열을 인덱스로 접근해서 숫자로 바꿀 때에는 str[i] - '0'

#include <iostream>
#include <string> 

using namespace std;
int solution(int n)
{
    string n_str = to_string(n);
    int answer = 0;
    for(int i=0; i<n_str.length(); i++) {
        answer += (n_str[i] - '0');
    }
    return answer;
}
