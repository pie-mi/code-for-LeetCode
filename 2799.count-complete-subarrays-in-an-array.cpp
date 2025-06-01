/*
 * @lc app=leetcode id=2799 lang=cpp
 *
 * [2799] Count Complete Subarrays in an Array
 */
#include <vector>
#include <unordered_map>
using namespace std;

/*
Accepted
1074 / 1074 testcases passed
1258ms Beats 20.88%
489.84MB Beats 8.97%
*/

// @lc code=start
class Solution
{
public:
    // 与2537题有类似，应该也是双指针(之前用滑动窗口，原理类似)
    int countCompleteSubarrays(vector<int> &nums)
    {
        // 先统计一次完整数组含有不同元素的数目
        unordered_map<int, int> category;
        for (auto &&i : nums)
        {
            category[i]++;
        }
        auto diffElem = category.size();
        int count = 0;

        for (auto i = 0; i < nums.size(); i++)
        {
            unordered_map<int, int> classify(category);
            for (auto j = nums.size() - 1; j >= i; j--) // j从末尾开始往回，直到不满足不同元素要求
            {
                if (classify.size() == diffElem)
                {
                    count++;
                    classify[nums[j]]--;
                    if (classify[nums[j]] == 0)
                    {
                        classify.erase(nums[j]);
                    }
                }
                else
                    break;
            }
            category[nums[i]]--; // 前头的开头的子数组已遍历完，下一round i+1开头了，i的元素减少1个
            if (category[nums[i]] == 0)
            {
                // 这样初始化下一round的classify的size才会减，不然只是i这个键值对是i,0
                category.erase(nums[i]);
            }
        }
        return count;
    }
};
// @lc code=end

int Solution::countCompleteSubarrays(vector<int> &nums)
{
    // 先统计一次完整数组含有不同元素的数目
    unordered_map<int, int> category;
    for (auto &&i : nums)
    {
        category[i]++;
    }
    auto diffElem = category.size();
    int count = 0;

    // 按照滑动窗口的双指针，j从前到后
    for (auto i = 0; i < nums.size(); i++)
    {
        unordered_map<int, int> window;
        for (auto j = i; j < nums.size(); j++)
        {
            window[nums[j]]++;
            if (window.size() == diffElem)
            {
                count += nums.size() - j; // n-1-j+1
                break;
            }
        }
        window[nums[i]]--;
        if (window[nums[i]] == 0)
        {
            window.erase(nums[i]);
        }
    }
}