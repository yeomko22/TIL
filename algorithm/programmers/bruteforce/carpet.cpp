#include <string>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    priority_queue<pair<int, int>> candidates;
    int square = brown + yellow;
    int width = 0;
    int height = 0;
    for (int i=1; i<square + 1; i++) {
        if ((square % i)==0) {
            width = i;
            height =  square / i;
            if (width < height) {
                continue;
            }
            if (width * 2 + height * 2 - 4 > brown) {
                continue;
            }
            candidates.push(make_pair(width, height));
        }
    }
    pair<int, int> answer_pair = candidates.top();
    answer.push_back(answer_pair.first);
    answer.push_back(answer_pair.second);
    return answer;
}
