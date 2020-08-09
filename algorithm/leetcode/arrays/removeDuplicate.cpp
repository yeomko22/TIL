class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int j = 0;
        int num = 0;
        for (int i=0; i<nums.size(); i++) {
            if (i==0 || nums[i] != num) {
                nums[j] = nums[i];
                num = nums[i];
                j++;
            }
        }
        return j;
    }
};
