#include <string>
#include <vector>
#include <math.h>

using namespace std;

long long solution(long long n) {
    long long answer = sqrt(n);
    if (powl(answer, 2) == n) {
        return powl(answer + 1, 2);
    }
    return -1;
}
