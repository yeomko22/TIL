#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 1;
    for (int i=1; i<n/2 + 1; i++) {
        int cur_sum = i;
        bool flag = true;
        for (int j=i+1; j<n; j++) {
            if ((cur_sum + j)>n) {
                flag = false;
                break;
            }
            if ((cur_sum + j)==n) {
                break;
            }
            cur_sum += j;
        }
        if (flag) {
            answer += 1;
        }
    }
    return answer;
}
