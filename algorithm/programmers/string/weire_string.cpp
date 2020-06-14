// c++에서는 문자열을 대문자로 바꾸기 위해선 꼭 빈 char 하나를 만들어주고 여기에 할당을 해줘야한다.
// 그렇지 않으면 문자가 아니라 숫자가 나온다.
// 또한 글자가 공백인지 비교하려면 c != ' '를 사용한다.
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

string solution(string s) {
    string answer = "";
    char c;
    int count = 0;
    for (int i=0; i<s.length(); i++) {
        if (count%2==0) {
            c = toupper(s[i]); 
        } else {
            c = tolower(s[i]); 
        }
        if (c!=' '){
            count += 1;
        } else {
            count = 0;
        }
        answer += c;
    }
    return answer;
}
