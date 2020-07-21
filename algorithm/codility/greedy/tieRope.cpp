int solution(int K, vector<int> &A) {
    int answer = 0;
    int curRope = 0;
    for (unsigned int i=0; i<A.size(); i++) {
        if (A[i] >= K) {
            answer += 1;
            curRope = 0;
            continue;
        } else {
            curRope += A[i];
            if (curRope>=K) {
                answer += 1;
                curRope = 0;
            }
        }
    }
    return answer;
}
