// 시간 복잡도 줄이는 부분이 까다로운 문제
// 특히 제곱 연산을 매 i 마다 수행하는 부분을 미리 N의 스퀘어루트를 구해서 적용하도록 바꿔주어야 
// time complexity 테스트를 통과할 수 있다.

#include <math.h>

using namespace std;

int solution(int N) {
    int factors = 0;
    int squareRootN = sqrt(N);
    if (squareRootN * squareRootN != N) {
        squareRootN++;
    } else {
        factors++;
    }
    for (int i=1; i<squareRootN; i++) {
        if (N % i==0) {
            factors += 2;
        }
    }
    return factors;
}
