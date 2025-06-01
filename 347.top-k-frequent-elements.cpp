/*
 * @lc app=leetcode id=347 lang=cpp
 *
 * [347] Top K Frequent Elements
 */
#include <vector>
#include <algorithm>
using namespace std;

/*
Accepted
0ms Beats100.00%
17.57MB Beats99.53%
*/

// @lc code=start
class Solution
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        // heap? can work，AI说最后可以维持n大小的小根堆，遍历统计结果时弹出目前不够大的
        // 但用的是排序后统计数量，再自定义根据数量排序
        sort(nums.begin(), nums.end());
        vector<int> result;
        // unordered_map<int,int>
        vector<pair<int, int>> countEach{{nums[0], 1}};
        for (auto i = 1; i < nums.size(); i++)
        {
            if (nums[i] == countEach.back().first)
            {
                countEach.back().second++;
            }
            else
            {
                countEach.emplace_back(nums[i], 1); // 相当于emplace_back(make_pair(nums[i], 1))
            }
        }

        sort(countEach.begin(), countEach.end(), [](const pair<int, int> &a, const pair<int, int> &b)
             { return a.second > b.second; });

        while (--k >= 0) // 先自减哦
        {
            result.emplace_back(countEach[k].first);
        }
        return result;
    }
};
// @lc code=end
