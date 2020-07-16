#include <stack>

int solution(string &S) {
    stack<char> st;
    for(unsigned int i=0; i<S.length(); i++) {
        if (S[i]=='(' || S[i]=='{' || S[i]=='[') {
            st.push(S[i]);
        } else {
            if (S[i]==')') {
                if (st.top()=='(') {
                    st.pop();
                } else {
                    return 0;
                }
            } else if (S[i]=='}') {
                if (st.top()=='{') {
                    st.pop();
                } else {
                    return 0;
                }
            } else if (S[i]==']') {
                if (st.top()=='[') {
                    st.pop();
                } else {
                    return 0;
                }
            }
        } 
    }
    if (st.empty()) {
        return 1;
    }
    return 0;
}
