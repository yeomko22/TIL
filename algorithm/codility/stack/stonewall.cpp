#include <stack>
int solution(vector<int> &H) {
    stack<int> st;
    int answer = 0;
    for (unsigned int i=0; i<H.size(); i++) {
        while (1) {
            if (st.empty()) {
                st.push(H[i]);
                break;
            }
            if (st.top()==H[i]) {
                break;
            }
            if (st.top()<H[i]) {
                st.push(H[i]);
                break;
            }
            if (st.top()>H[i]) {
                st.pop();
                answer += 1;
            }
        }
    }
    answer += st.size();
    return answer;
}
