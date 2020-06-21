#include <iostream>
#include <string>
#include <stack>
using namespace std;

int solution(string s)
{
    int answer = 0;
    stack<char> st;
    for (int i=0; i<s.length(); i++) {
        if (st.empty()){
            st.push(s[i]);
            continue;
        }
        char cur_top = st.top();
        if (cur_top==s[i]) {
            st.pop();
        } else {
            st.push(s[i]);
        }
    }
    if (st.size()>0) {
        answer = 0;
    } else {
        answer = 1;
    }
    return answer;
}
