/*
 * @lc app=leetcode id=75 lang=cpp
 *
 * [75] Sort Colors
 */
#include <vector>
using std::vector;

/*
Accepted
89/89 cases passed (0 ms)
Your runtime beats 100 % of cpp submissions
Your memory usage beats 97.4 % of cpp submissions (11.5 MB)
*/

// @lc code=start
class Solution {
public:
    void sortColors(vector<int>& nums) {
        //就是排序，不要求稳定，那就遍历一遍，统计0、1、2各几个即可，满足原地
        auto count0 = 0;
        auto count1 = 0;
        auto count2 = 0;
        for (auto &&i : nums)
        {
            switch (i)
            {
            case 0:
                count0++;
                break;
            case 1:
                count1++;
                break;
            case 2:
                count2++;
                break;
            default:
                break;
            }
        }
        nums.clear();
        nums.insert(nums.end(), count0, 0);
        nums.insert(nums.end(), count1, 1);
        nums.insert(nums.end(), count2, 2);
    }
};
// @lc code=end

