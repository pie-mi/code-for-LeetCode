/*
 * @lc app=leetcode id=31 lang=cpp
 *
 * [31] Next Permutation
 */
#include <algorithm>
#include <utility>
#include <vector>
using std::vector, std::swap, std::reverse;
// @lc code=start

/*
Accepted
266/266 cases passed (0 ms)
Your runtime beats 100 % of cpp submissions
Your memory usage beats 67.73 % of cpp submissions (15.7 MB)
*/

class Solution
{
public:
    void nextPermutation(vector<int> &nums)
    {
        // 因为不久前看过动态规划例子，想到了从后往前
        // 原地算法，不是DP，label是“技巧”
        // 交换两者，最小已在最后、最大还在最后？ "bubble" queue?
        // 没有想到，去看答案解法

        /*
        1.从后向前 查找第一个 相邻升序 的元素对 (i,j)，满足 A[i] < A[j]。此时 [j,end) 必然是降序
        2.在 [j,end) 从后向前 查找第一个满足 A[i] < A[k] 的 k。A[i]、A[k] 分别就是上文所说的「小数」、「大数」
        3.将 A[i] 与 A[k] 交换
        4.可以断定这时 [j,end) 必然是降序，逆置 [j,end)，使其升序
        如果在步骤 1 找不到符合的相邻元素对，说明当前 [begin,end) 为一个降序顺序，则直接跳到步骤 4
        */

        int i, j;
        i = nums.size() - 2;
        j = i + 1;

        // 找两个相邻升序的，即后面都是降序的了
        while (i > -1)
        {

            if (nums[i] < nums[j])
            {
                j = nums.size() - 1;
                while (j > i)
                {
                    if (nums[j] > nums[i]) // 不能j--，还没有swap呢
                    {
                        swap(nums[i], nums[j]);
                        break;
                    }
                    j--;
                }

                break;
            }
            else
            {
                i--;
                j--;
                continue;
            }
        }

        // 交换之后后面的再排序，sort空间不是O(1),逆序即可
        auto start = nums.begin() + i + 1; // i+1就是原来的j
        reverse(start, nums.end());
    }
};
// @lc code=end
