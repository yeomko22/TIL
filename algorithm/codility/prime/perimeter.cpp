#include <math.h>
#include <iostream>

using namespace std;

int solution(int N) {
    int sqrtNum = sqrt(N);
    if (sqrtNum * sqrtNum ==N) {
        return 4 * sqrtNum;
    }
    int answer = 0;
    while (1) {
        if (N % sqrtNum != 0) {
            sqrtNum--;
            continue;
        }
        answer = 2 * ((N / sqrtNum) +  sqrtNum);
        break;
    }
    return answer;
}
