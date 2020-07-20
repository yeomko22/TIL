#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<int> &A) {
    if (A.size()<2) {
        return 0;
    }
    vector<int> profits(A.size());
    int minprice = A[0];
    for (unsigned int i=1; i<A.size(); i++) {
        minprice = min(minprice, A[i]);
        if (minprice==A[i]) {
            profits[i] = profits[i-1];
        } else {
            profits[i] = max(profits[i-1], A[i] - minprice);
        }
    }
    int answer = profits[profits.size() - 1];
    if (answer < 0) {
        return 0;
    }
    return answer;
}
