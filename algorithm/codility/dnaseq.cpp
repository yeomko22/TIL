// O(n)으로 해결하는 방법을 모르겠어서 힌트를 찾은 문제
// 한번 linear scan하면서 각 위치에서 글자들의 누적 개수를 찾는다.
// 그리고 쿼리로 주어진 인덱스들을 가지고 누적 개수의 차이를 구해서 정답을 찾는다.
// 이 때 두 인덱스가 같은 경우, 시작 인덱스가 1인 경우의 예외 처리를 신경써줘야한다.
#include <iostream>
#include <map>

vector<int> solution(string &S, vector<int> &P, vector<int> &Q) {
    // write your code in C++14 (g++ 6.2.0)
    vector<vector<int>> flags(S.size(), vector<int> (4, 0));
	map<char, int > m;
	m['A'] = 1;
	m['C'] = 2;
	m['G'] = 3;
	m['T'] = 4;
	vector<int> addVec(4, 0);
    for (unsigned int i=0; i<S.length(); i++) {
        int cIndex = m[S[i]] - 1;
        addVec[cIndex] += 1;
        flags[i] = addVec;
    }
    vector<int> answer(P.size(), 0);
    for (unsigned int i=0; i<P.size(); i++) {
        if (P[i]==Q[i]) {
            answer[i] = m[S[P[i]]];
            continue;
        }
        vector<int> cumP;
        if (P[i]==0) {
            cumP = vector<int>(4, 0);
        } else {
            cumP = flags[P[i]-1];
        }
        vector<int> cumQ = flags[Q[i]];
        for (int j=0; j<4; j++) {
            int diff = cumQ[j] - cumP[j];
            if (diff!=0) {
                answer[i] = j + 1;
                break;
            }
        }
    }
    return answer;
}
