// char를 int로 바꿀 때는 (int) 해준 뒤 48을 빼준다. 
// 그냥 (int)를 해버리면 아스키 코드가 나온다.

#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(long long n) {
    vector<int> answer;
    string n_str = to_string(n);
    for (int i=0; i<n_str.length(); i++) {
        int a = (int)n_str[n_str.length() - i -1] - 48;
        answer.push_back(a);
    }
    return answer;
}
