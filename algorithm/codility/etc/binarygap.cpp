#include <deque>
#include <algorithm>

using namespace std;

int solution(int N) {
    int curCount = 0;
    int binaryGap = 0;
    bool flag = false;
    while (1) {
        if (N==1) {
            binaryGap = max(binaryGap, curCount);
            break;
        }
        int rest = N % 2;
        N = N / 2;
        if (rest==0) {
            if (flag) {
                curCount += 1;
            }
        } else {
            flag=true;
            binaryGap = max(binaryGap, curCount);
            curCount = 0;
        }
    }
    return binaryGap;
}
