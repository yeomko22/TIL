#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(long long n) {
    string n_str = to_string(n);
    sort(n_str.begin(), n_str.end(), greater<char>());
    long long answer = stoll(n_str);
    return answer;
}
