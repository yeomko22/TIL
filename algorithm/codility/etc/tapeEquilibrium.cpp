// 초기 answer 값을 잘못 설정해주어서 살짝 헤맨 문제
// 큰 값이 예상될 경우 long long을 사용해주자
#include <algorithm>
#include <math.h>
#include <limits.h>
#include <vector>

using namespace std;

int solution(vector<int> &A) {
    long long orgSum = 0;
    for (auto elem: A) {
        orgSum += elem;
    }
    long long answer = LLONG_MAX;
    long long curSum = 0;
    for (unsigned int i=0; i<A.size()-1; i++) {
        curSum += A[i];
        orgSum -= A[i];
        answer = min(answer, abs(orgSum - curSum));
    }
    return answer;
}
