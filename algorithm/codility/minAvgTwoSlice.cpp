// 트릭은 가장 작은 평균은 연속한 2개 혹은 3개 값의 평균 중에 있다는 것이다.
// 왜냐하면 4개 이상부터는 ((2개 값 평균) + (2개 값 평균)) / 2가 되므로 절대 최소값이 될 수 없기 때문
#include <iostream>
#include <algorithm>
#include <vector>

int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    int answer = 0;
    double minAvg = 100000;
    for (unsigned int i=0; i<A.size()-1; i++) {
        float avgTwo = (A[i] + A[i+1]) / (double)2;
        float avgTheree = 100000;
        if (i<A.size()-2) {
            avgTheree = (A[i] + A[i+1] + A[i+2]) / (double)3;
        }
        if (avgTwo < minAvg or avgTheree < minAvg) {
            minAvg = min(avgTwo, avgTheree);
            answer = i;
        }
    }
    return answer;
}
