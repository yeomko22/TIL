#include<string>
#include <iostream>
#include <stack>

using namespace std;

bool solution(string s)
{
    bool answer = true;
    stack<char> st;
    for (int i=0; i<s.length(); i++) {
        if (st.empty()) {
            st.push(s[i]);
            continue;
        }
        if (st.top()=='(' && s[i]==')') {
            st.pop();
        } else {
            st.push(s[i]);
        }
    }
    if (!st.empty()) {
        answer = false;
    }

    return answer;
}
