// 비어있는 input, 범위를 벗어나는 값에 대한 예외 처리 미숙으로 감점
#include <algorithm>

int solution(vector<int> &A) {
    if (A.size() < 3) {
        return 0;
    }
    sort(A.begin(), A.end());
    long long first = 0;
    long long second = 0;
    long long third = 0;
    for (unsigned int i=0; i<A.size()-2; i++) {
        first = A[i];
        second = A[i+1];
        third = A[i+2];
        if (first+second > third) {
            return 1;
        }
    }
    return 0;
}
