int solution(string &S) {
    if (S.length()%2==0) {
        return -1;
    }
    int middle = S.length() / 2;
    int flag = true;
    for (int i=0; i<middle; i++) {
        if (S[i]!=S[S.length()-1-i]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        return middle;
    }
    return -1;
}
