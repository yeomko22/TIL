#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int scoville_index(int first, int second) {
    return first + (second * 2);
}

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int> pq;
    for (int i=0; i< scoville.size(); i++) {
        pq.push(-1 * scoville[i]);
    }
    while (true) {
        int pq_first = -1 * pq.top();
        pq.pop();
        if (pq_first >= K) {
            break;
        }
        if (pq.empty()) {
            return -1;
        }
        int pq_second = -1 * pq.top();
        pq.pop();
        pq.push(-1 * scoville_index(pq_first, pq_second));
        answer++;
    }
    return answer;
}
