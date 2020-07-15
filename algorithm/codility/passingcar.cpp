int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    int answer = 0;
    int west = 0;
    for (unsigned int i=0; i<A.size(); i++) {
        int direction = A[A.size() -1 -i];
        if (direction==1) {
            west += 1;
        } else {
            answer += west;
            if (answer > 1000000000) {
                return -1;
            }
        }
    }
    return answer;
}
