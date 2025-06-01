/*
 * @lc app=leetcode id=2145 lang=cpp
 *
 * [2145] Count the Hidden Sequences
 */
#include <vector>
using namespace std;

/*
Daily Coding Challenge Completed!
Completion Streak: 2Days
Consistency is key, see you tomorrow!
Accepted
17ms Beats5.64%
134.74MB Beats5.64%
*/

// @lc code=start
class Solution
{
public:
    int numberOfArrays(vector<int> &differences, int lower, int upper)
    {
        // 都从0开始计算出符合排布的hidden，同时记录最小的与最大的，如有可行的再偏移最小
        // 元素大小和size都是10^5，若每个都是10^5则hidden的最后是10^10超过int表示范围
        vector<long long> hidden{0};
        long long currMax = 0; //case 85有两万多个负十万超出int表示范围
        long long currMin = 0;
        auto result = 0;
        for (auto &&i : differences)
        {
            hidden.emplace_back(hidden.back() + i);
            currMax = hidden.back() > currMax ? hidden.back() : currMax;
            currMin = hidden.back() < currMin ? hidden.back() : currMin;
            // 等于0就不变，如[0,0]，可以表示[7,7,7]，只要7在范围里就OK
        }
        // 偏移到最小符合的，再看此时最大值与上界upper的差距
        long long move = lower - currMin;
        auto movedMax = currMax + move;
        if (movedMax <= upper)
        {
            result = upper - movedMax + 1;
        }
        // else result=0;
        return result;
    }
};
// @lc code=end
