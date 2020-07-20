// answer를 0으로 설정해서 정답이 음수인 경우를 틀림
#include <algorithm>
#include <iostream>
#include <limits.h>

using namespace std;

int solution(vector<int> &A) {
    if (A.size()==1) {
        return A[0];
    }
    vector<int> sums(A.size());
    sums[0] = A[0];
    for (unsigned int i=1; i<A.size(); i++) {
        sums[i] = max(sums[i-1] + A[i], A[i]);
    }
    int answer = INT_MIN;
    for (auto elem: sums) {
        answer = max(elem, answer);
    }
    return answer;
}
