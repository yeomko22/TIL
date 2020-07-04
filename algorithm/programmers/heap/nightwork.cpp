#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

long long solution(int n, vector<int> works) {
    long long answer = 0;
    long long cur_sum = 0;
    priority_queue<int> pq;
    for (int i=0; i<works.size(); i++) {
        pq.push(works[i]);
        cur_sum += works[i];
    }
    if (cur_sum <= n) {
        return 0;
    }
    while (n) {
        int cur_top = pq.top();
        pq.pop();
        pq.push(cur_top - 1);
        n -= 1;
    }
    while (!pq.empty()) {
        answer += (pq.top() * pq.top());
        pq.pop();
    }
    return answer;
}
