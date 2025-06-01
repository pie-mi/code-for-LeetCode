/*
 * @lc app=leetcode id=274 lang=cpp
 *
 * [274] H-Index
 */
#include <vector>
#include <algorithm>
using namespace std;

/*
Accepted
83/83 cases passed (0 ms)
Your runtime beats 100 % of cpp submissions
Your memory usage beats 64.67 % of cpp submissions (12.3 MB)
*/

// @lc code=start
class Solution
{
public:
    int hIndex(vector<int> &citations)
    {
        // 想法是排序，从后往前，size-下标就是比当前更高引用的数量
        sort(citations.begin(), citations.end());
        // 另一方式如果从n开始试，每次都二分查找，就n次log n
        // 如果是5000个1引用，那就太浪费了
        // 其实结果就要么是vector里有的数，要么是不够引用数本身多的份数
        int h_index = 0;
        int n = citations.size();
        for (auto i = 0; i < n; i++)
        {
            if (citations[i] == 0)
                continue;
            int count = n - i; // 多少个引用大于等于当前
            // 如 1 1 1 1 1 5 5 5 5，H=4
            if (count >= citations[i])
            {
                h_index = citations[i];
            }
            else if (count > h_index)
            {
                // 本来卡在区分是高引用数不够还是发paper数少，如 5 5 6 6
                // 改了一下第一个例子发现了修改地方，顺便解决了
                // 如0 4 5 5 6，4时是4，到5只剩3篇了，以后再高引用都量不够的了
                h_index = count;
                break;
            }
        }
        return h_index;
    }
};
// @lc code=end
