#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(int n) {
    vector<int> dp;
    for (int i=0; i<n+1; i++) {
        dp.push_back(0);
    }
    dp[1] = 1;
    dp[2] = 2;
    for (int i=3; i<n+1; i++) {
        dp[i] = (dp[i-1] + dp[i-2]) % 1000000007;
    }
    int answer = dp.back();
    return answer;
}
