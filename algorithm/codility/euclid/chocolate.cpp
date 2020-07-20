// 최소 공배수가 long long 타입임을 처리해주지 못해서 감점 받음

int gcd(int N, int M) {
    while (1) {
        if (N % M == 0) {
            break;
        }
        int mod = N % M;
        N = M;
        M = mod;
    }
    return M;
}

long long scm(int N, int M) {
    long long gcdNum = gcd(N, M);
    long long scmNum = (N / gcdNum) * (M / gcdNum) * gcdNum;
    return scmNum;
}

int solution(int N, int M) {
    long long scmNum = scm(N, M);
    int answer = scmNum / M;
    return answer;
}
