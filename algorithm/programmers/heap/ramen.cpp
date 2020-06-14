#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int stock, vector<int> dates, vector<int> supplies, int k) {
    int answer = 0;
    priority_queue<int> pq;
    int dates_index = 0;
    for (int i=0; i<k; i++) {
        stock -= 1;
        if (dates[dates_index]==i) {
            pq.push(supplies[dates_index]);
            dates_index += 1;
        }
        if (stock < 0) {
            stock += pq.top();
            pq.pop();
            answer += 1;
        }
    }
    return answer;
}
