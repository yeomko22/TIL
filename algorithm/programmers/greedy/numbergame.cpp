#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> A, vector<int> B) {
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    int indexB = 0;
    int answer = 0;
    for (int i=0; i<A.size(); i++) {
        while (1) {
            if (indexB > B.size() - 1) {
               break;
            }
            if (B[indexB] <= A[i]) {
                indexB += 1;
                continue;
            } else {
                answer += 1;
                indexB += 1;
                break;
            }
        }
    }
    return answer;
}
