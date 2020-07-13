// 범위를 벗어나는 값은 처리하지 않는 조건문의 순서를 헷갈려서 감점
// 이러한 경우 줄 수가 늘어나더라도 조건문을 이어붙이지 말고 나눠주도록 하자
#include <vector>

int solution(vector<int> &A) {
    int N = A.size();
    vector<int> flags(N+1, 0);
    for(unsigned int i=0; i<A.size(); i++) {
        if (A[i]>N || flags[A[i]]!=0) {
            break;
        }
        flags[A[i]] = 1;
    }
    int answer = 1;
    for(unsigned int i=1; i<flags.size(); i++) {
        if(flags[i]==0) {
            answer = 0;
            break;
        }
    }
    return answer;
}
