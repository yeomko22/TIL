#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    sort(people.begin(), people.end());
    int i = 0;
    int j = people.size()-1;
    for (j; j>i; j--) {
        if (people[i] + people[j] <= limit) {
            i++;
        }
        answer++;
    }
    if (i==j) {
        answer++;
    }
    return answer;
}
