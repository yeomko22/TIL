#include <string>
#include <vector>
#include <math.h> 
#include <queue>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    deque<int> dq;
    for (int i=0; i<progresses.size(); i++) {
        dq.push_back(ceil((100 - progresses[i]) / speeds[i]));
    }
    int count = 0;
    int curTop = dq.front();
    while (!dq.empty()) {
        if (dq.front() > curTop) {
            curTop = dq.front();
            answer.push_back(count);
            count = 0;
        } else {
            count += 1;
            dq.pop_front();
        }
    }
    if (count != 0) {
        answer.push_back(count);
    }
    return answer;
}
