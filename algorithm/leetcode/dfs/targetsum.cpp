// recursion 방식으로 쉽게 풀이가 가능했음.
class Solution {
public:
    int answer = 0;
    int findTargetSumWays(vector<int>& nums, int S) {
        dfs(nums, 0, 0, S);
        return answer;
    }
    void dfs(vector<int>& nums, int pos, int curSum, int target) {
        if (pos==nums.size()-1) {
            if (curSum + nums[pos]==target) {
                answer++;
            }
            if (curSum - nums[pos]==target) {
                answer++;
            }
            return;
        }
        dfs(nums, pos+1, curSum+nums[pos], target);
        dfs(nums, pos+1, curSum-nums[pos], target);
    }
};
