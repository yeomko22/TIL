// 생각보다 까다로웠던 문제
// 그냥 접근하면 O(n^3)이 나와서 실패한다. 100만개개 최대 개수였는데 통과 못함
// 어느 정도 사전 지식이 필요한데 트릭은 y값 이동 시에 함께 z값도 옮겨주는 것
#include <algorithm>

int solution(vector<int> &A) {
    sort(A.begin(), A.end());
    unsigned int n = A.size();
    unsigned int answer = 0;
    for (unsigned int x=0; x<n; x++) {
        unsigned int z = x + 2;
        for (unsigned int y=x+1; y<n; y++) {
            while (z<n && A[x] + A[y] > A[z]) {
                z += 1;
            }
            answer += (z - y - 1);
        }
    }
    return answer;
}
