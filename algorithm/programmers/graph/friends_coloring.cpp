#include <vector>
#include <stack>
#include <set>
#include <iostream>

using namespace std;

int dfs(pair<int, int> index, vector<vector<int>> picture, set<pair<int, int>> *visited,  int number_of_area) {
    stack<pair<int, int>> st;
    st.push(index);
    int v = picture[index.first][index.second];
    int area = 0;
    int cnt = 0;
    while (!st.empty()) {
        pair<int, int> i = st.top();
        st.pop();
        if (visited->find(i)==visited->end()) {
            area += 1;
        }
        visited->insert(i);
        if (i.first > 0 && picture[i.first - 1][i.second]==v) {
            pair<int, int> candidate = make_pair(i.first - 1, i.second);
            if (visited->find(candidate)==visited->end()) {
                st.push(candidate);
            }
        }
        if (i.first < picture.size() - 1 && picture[i.first + 1][i.second]==v) {
            pair<int, int> candidate = make_pair(i.first + 1, i.second);
            if (visited->find(candidate)==visited->end()) {
                st.push(candidate);
            }
        }
        if (i.second > 0 && picture[i.first][i.second - 1]==v) {
            pair<int, int> candidate = make_pair(i.first, i.second-1);
            if (visited->find(candidate)==visited->end()) {
                st.push(candidate);
            }
        }
        if (i.second < picture[0].size() && picture[i.first][i.second + 1]==v) {
            pair<int, int> candidate = make_pair(i.first, i.second+1);
            if (visited->find(candidate)==visited->end()) {
                st.push(candidate);
            }
        }
    }
    return area;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    
    set<pair<int, int>> visited;
    for (int i=0; i<picture.size(); i++) {
        for (int j=0; j<picture[0].size(); j++) {
            if (picture[i][j]==0) {
                continue;
            }
            if (visited.find(make_pair(i, j)) != visited.end()) {
                continue;
            }
            number_of_area += 1;
            int area = dfs(make_pair(i, j), picture, &visited, number_of_area);
            if (area > max_size_of_one_area) {
                max_size_of_one_area = area;
            }
        }
    }
    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}
