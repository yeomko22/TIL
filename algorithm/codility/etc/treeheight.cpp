// 간단한 BFS를 짜는 것이었음에도 처음에 100%를 달성하지 못하였음.
// visited를 체크할 필요가 없었는데 체크하는 실수를 범함
// answer의 경우도 max 값을 취했어야 하는데 그냥 그대로 대입하는 바보같은 짓을 함
// 여러모로 허술한 점이 많았다...!
#include <queue>
#include <algorithm>

using namespace std;

int solution(tree * T) {
    if (!T) {
        return -1;
    }
    queue<pair<int, tree*>> q;
    q.push(make_pair(0, T));
    int answer = 0;
    while (!q.empty()) {
        pair<int, tree*> curNode = q.front();
        q.pop();
        answer = max(answer, curNode.first);
        if (curNode.second->l) {
            q.push(make_pair(curNode.first + 1, curNode.second->l));
        }
        if (curNode.second->r) {
            q.push(make_pair(curNode.first + 1, curNode.second->r));
        }
    }
    return answer;
}
