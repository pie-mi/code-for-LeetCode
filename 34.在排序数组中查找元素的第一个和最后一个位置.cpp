/*
 * @lc app=leetcode.cn id=34 lang=cpp
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 */
/*
#include <vector>
#include <algorithm>
using namespace std;
*/
// @lc code=start
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        bool exist; //是否存在
        vector<int> result;
        exist = binary_search(nums.begin(), nums.end(), target);
        if (!exist)
        {
            result.push_back(-1);
            result.push_back(-1);
            return result;
        }
        int low, high;
        //lower_bound返回>=目标的指针，与数组头相减刚好是下标int类型
        low = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
        high = upper_bound(nums.begin(), nums.end(), target) - nums.begin() - 1;
        result.push_back(low);
        result.push_back(high);
        return result;
    }
};
// @lc code=end

