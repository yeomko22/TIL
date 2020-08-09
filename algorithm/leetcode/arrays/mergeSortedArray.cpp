// 뒤에서부터 큰 숫자 순서대로 쌓아주는 것이 트릭
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int index1 = m - 1;
        int index2 = n - 1;
        for (unsigned int i=0; i < nums1.size(); i++) {
            if (index1 < 0) {
                nums1[nums1.size()-1-i] = nums2[index2];
                index2 -= 1;
                continue;
            } 
            if (index2 < 0) {
                break;
            }
            if (nums1[index1] >= nums2[index2]) {
                nums1[nums1.size()-1-i] = nums1[index1];
                index1 -= 1;
            } else {
                nums1[nums1.size()-1-i] = nums2[index2];
                index2 -= 1;
            }
        }
    }
};
