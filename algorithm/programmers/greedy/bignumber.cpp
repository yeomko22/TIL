#include <string>
#include <vector>
#include<iostream>
using namespace std;

string solution(string number, int k) {
    string answer = "";
    int n = number.size();
    int a = -1;
    int mm = -1;
    int nj;
    int nn = n - k;
    for(int i=0; i < nn; i++){
        for(int j = a+1; j < n - (nn - i) + 1; j++){
            if(mm < number[j] - '0') {  //string의 원소 문자를 int형으로 변환.
                mm = number[j]-'0';   //atoi는 string을 통으로 int로 변환할때.
                nj = j;
            }
        }
        answer.append(to_string(mm));  
        a = nj;
        mm = -1;  //mm초기화
    }
    return answer;
