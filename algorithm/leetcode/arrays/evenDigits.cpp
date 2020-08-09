// to_string 함수를 통해서 숫자를 문자열로 바꿀 수 있음
using namespace std;

class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int answer = 0;
        for (unsigned int i=0; i<nums.size(); i++) {
            if (to_string(nums[i]).length() % 2==0) {
                answer += 1;
            }
        }
        return answer;
    }
};
