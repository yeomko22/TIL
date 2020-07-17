#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> solution(int N, vector<int> &A) {
    vector<int> answer(N, 0);
    int curMax = 0;
    int lastMax = 0;
    for(unsigned int i=0; i<A.size(); i++) {
        if (A[i]==N+1) {
            lastMax = curMax;
        } else {
            if (answer[A[i]-1] < lastMax) {
                answer[A[i]-1] = lastMax + 1;
            } else {
                answer[A[i]-1] += 1;
            }
            curMax = max(curMax, answer[A[i]-1]);
        }
    }
    for (unsigned int i=0; i<answer.size(); i++) {
        if (answer[i] < lastMax) {
            answer[i] = lastMax;
        }
    }
    return answer;
}
