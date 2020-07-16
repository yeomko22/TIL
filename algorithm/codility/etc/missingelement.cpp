// flags 크기 최대값 설정을 잘못해주어 런타임 에러가 발생, 이 부분 신경쓰자!
#include <vector>

int solution(vector<int> &A) {
    int answer = 1;
    vector<int> flags(1000001, 0);
    for (unsigned int i=0; i<A.size(); i++) {
        if (A[i]<=0) {
            continue;
        }
        flags[A[i]] = 1;
    }
    for (unsigned int i=1; i<flags.size(); i++) {
        if (flags[i]==0) {
            answer = i;
            break;
        }
    }
    return answer;
}
