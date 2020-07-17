#include <stack>

int solution(string &S) {
    stack<char> st;
    for (unsigned int i=0; i<S.length(); i++) {
        if (S[i]=='(') {
            st.push(S[i]);
        } else {
            if (st.empty()) {
                return 0;
            }
            st.pop();
        }
    }
    if (st.empty()) {
        return 1;
    }
    return 0;
}
