#include <set>

using namespace std;

int solution(int M, vector<int> &A) {
    int answer = 0;
    int start = 0;
    set<int> cp;
    for (unsigned int i=0; i<A.size(); i++) {
        if (cp.find(A[i])!=cp.end()) {
            while (!cp.empty()) {
                cp.erase(A[start]);
                start++;
                if (cp.find(A[i])==cp.end()) {
                    break;
                }
            }
        }
        cp.insert(A[i]);
        answer += cp.size();
        if (answer > 1000000000) {
            return 1000000000;
        }
    }
    return answer;
}
