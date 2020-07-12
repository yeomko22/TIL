// 예외처리가 많아서 100%를 클리어하는데 애먹었던 문제
// 최대한 많은 경우의 수를 생각해 볼 것

#include <iostream>

int solution(int A, int B, int K) {
    int answer = 0;
    if (A==B) {
        if (B % K == 0) {
            answer += 1;
        }
        return answer;
    }
    int divB = B / K;
    if (A==0) {
        answer += (divB + 1);
    } else {
        int divA = (A - 1) / K;
        answer += (divB - divA);
    }
    return answer;
}
