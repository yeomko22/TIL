#include <algorithm>
#include <vector>

using namespace std;

int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    vector<pair<long long, long long>> intervals;
    for (unsigned long long i=0; i<A.size(); i++) {
        intervals.push_back(make_pair(i - A[i], i + A[i]));
    }
    sort(intervals.begin(), intervals.end());
    int answer = 0;
    for (unsigned int i=0; i<intervals.size(); i++) {
        int intersect = 0;
        for (unsigned int j=i+1; j<intervals.size(); j++) {
            if (intervals[j].first <= intervals[i].second) {
                intersect += 1;
            } else {
                break;
            }
        }
        answer += intersect;
        if (answer > 10000000) {
            return -1;
        }
    }
    return answer;
}
