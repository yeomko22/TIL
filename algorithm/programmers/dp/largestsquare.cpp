// 맨 처음 윈도우에 대한 검사를 별도로 진행해서 초기 값을 설정해주어야함.
#include <iostream>
#include<vector>
using namespace std;

int solution(vector<vector<int>> board)
{
    int answer = 0;
    int initial_value = 0;
    if (board.size()==1 and board[0].size()==1) {
        initial_value = board[0][0];
    } else {
        initial_value = max(board[0][0], board[0][1]);
        initial_value = max(initial_value, board[1][0]);
    }
    answer = initial_value;
    for (int i=1; i<board.size(); i++) {
        for (int j=1; j<board[0].size(); j++) {
            if (board[i-1][j-1] > 0 and board[i][j-1] >0 and board[i-1][j] >0 and board[i][j] > 0) {
                int cur_min = min(board[i-1][j-1], board[i][j-1]);
                cur_min = min(cur_min, board[i-1][j]);
                board[i][j] = cur_min + 1;
            }
            answer = max(answer, board[i][j] * board[i][j]);
        }
    }

    return answer;
}
