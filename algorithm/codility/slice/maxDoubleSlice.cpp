// 정말 애먹은 문제
// 풀이는 생각보다 단순했다. 정방향으로 부분합을 구하고 역방향으로 부분합을 구하는 것
// 일반적인 부분합과 다른 점은 제외하고자 하는 인덱스 바로 주변 값부터 더해줘야한다는 것이다.
// 역시 원리를 이해해야 제대로 문제를 풀 수 있다.

#include <iostream>

int solution(vector<int> &A) {
    if (A.size()==3) {
        return 0;
    }
    vector<int> localmax1(A.size());
    vector<int> localmax2(A.size());
    for (unsigned int i=1; i<A.size()-1; i++) {
        int j = A.size() - 1 - i;
        localmax1[i] = max(localmax1[i-1] + A[i], A[i]);
        if (localmax1[i]<0) {
            localmax1[i] = 0;
        }
        localmax2[j] = max(localmax2[j+1] + A[j], A[j]);
        if (localmax2[j] < 0) {
            localmax2[j] = 0;
        }
    }
    int answer = 0;
    for (unsigned int i=1; i<A.size()-1; i++) {
        answer = max(answer, localmax1[i-1] + localmax2[i+1]);
    }
    return answer;
}
