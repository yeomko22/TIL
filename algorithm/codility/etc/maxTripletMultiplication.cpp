// 쉬운 문제를 너무 어렵게 생각했음

#include <algorithm>

int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    sort(A.begin(), A.end());
    int N = A.size();
    int mulone = A[N-1] * A[N-2] * A[N-3];
    int multwo = A[0] * A[1] * A[N-1];
    return max(mulone, multwo);
}
