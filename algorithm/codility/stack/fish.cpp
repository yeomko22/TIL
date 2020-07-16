#include <stack>
#include <vector>

int solution(vector<int> &A, vector<int> &B) {
    stack<int> st;
    int answer = 0;
    for (unsigned int i=0; i<A.size(); i++) {
        int index = A.size() -1 -i;
        if (B[index]==0) {
            st.push(A[index]);
        } else {
            while (1) {
                if (st.empty()) {
                    answer += 1;
                    break;
                }
                if (A[index] > st.top()) {
                    st.pop();
                } else {
                    break;
                }
            }
        }
    }
    answer += st.size();
    return answer;
}
