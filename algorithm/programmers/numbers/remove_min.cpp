#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> arr) {
    vector<int> answer = arr;
    int min_value = *min_element(arr.begin(), arr.end());
    int pos = find(answer.begin(), answer.end(), min_value) - answer.begin();
    answer.erase(answer.begin() + pos);
    return answer.empty() ? vector<int>(1, -1) : answer;
}
