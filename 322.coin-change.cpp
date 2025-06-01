/*
 * @lc app=leetcode id=322 lang=cpp
 *
 * [322] Coin Change
 */
#include <vector>
#include <algorithm>
using namespace std;

/*
Accepted
189 / 189 testcases passed
219ms Beats 6.86%
98.05MB Beats 5.00%
*/

// @lc code=start
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        // 看到动态规划进来的，也在hello algo里看过了，和我的i与j刚好顺序相反，转置了一下
        // 排序先，dp[i,j]代表金额i可以由j种面值的硬币构成的所需最小硬币数量
        // 是从金额遍历吗？记忆化搜索而来，例如已经到11，之前记录了金额为10与1的最小数量，加起来即可，2与9，而10也是这么9与1推出来的
        // 当前的可以由dp[i-coins[j],j-1]+1、dp[i,j-1]较小值转移，看hello algo是dp[i,a - coins[i - 1]] + 1
        // 即“当前目标金额减当前硬币面值和没有当前面值硬币的情况就加一个当前面值硬币”；“不用当前面值硬币也凑出当前目标金额”，两者间最小值
        // ！！！No!!!是dp[i-coins[j-1],j],是“有这个面值但恰好减少对应面值”的情况，否则限制了当前面值只能一个，
        // 如11在遍历到5时得到了1个5面值硬币，到10的时候应该是从有这个5面值的硬币的5情况下跳过来，这样才是正确2个5面值硬币，而不是从用4面值以下凑成的5跳过来
        // 如目标11，当前硬币面值是7，可以由4这种情况+1个当前7硬币得来，也可5+6两种情况得来，
        // 但可能真正面值只有1、5、6，那其实4这种情况是4个1而来的，实际是4+1(1个7面值硬币)=5个硬币
        // dp[i,j-1]就是没有7面值，即5+6凑11，各1个就够了
        // 边界情况是dp[0,j]，目标金额0，那无论面值都是0个硬币；dp[i,0]没有硬币凑出金额，全是-1

        if (amount == 0)
            return 0;
        sort(coins.begin(), coins.end());
        auto cut = unique(coins.begin(), coins.end());
        coins.erase(cut, coins.end()); // 题目没说唯一，去重一下，因为本来同面额硬币数量就不限量
        vector<vector<int>> dp(amount + 1, vector<int>(coins.size() + 1, 0));
        for (auto &&i : dp)
            i[0] = -1;

        dp[0][0] = 0; // dp[0,0]特别从-1置回0
        for (auto i = 1; i < dp.size(); i++)
        {
            for (auto j = 1; j < dp[0].size(); j++)
            {
                if (i - coins[j - 1] >= 0) // j-1刚好对应coins下标
                {
                    if (dp[i][j - 1] == -1 && dp[i - coins[j - 1]][j] == -1) // 即若左边和减少对应面值两种情况都无法凑出目标金额
                    {
                        dp[i][j] = -1;
                    }
                    else if (dp[i][j - 1] == -1 && dp[i - coins[j - 1]][j] != -1)
                    {
                        // 如3 5 7凑3时
                        dp[i][j] = dp[i - coins[j - 1]][j] + 1;
                    }
                    else if (dp[i][j - 1] != -1 && dp[i - coins[j - 1]][j] == -1)
                    {
                        // 如3 5 7凑6时，2个3可以，5减少对应面值是-1，但可以从3过来
                        dp[i][j] = dp[i][j - 1];
                    }
                    else
                        dp[i][j] = min(dp[i - coins[j - 1]][j] + 1, dp[i][j - 1]);
                }
                else
                {
                    // 当前金额小于硬币面值，因为金额是从小尝试到大的
                    // 会传递的，不用直接赋值-1，例如硬币最小面值是5，自然金额1~4都应是-1，
                    // 1这行从dp[1][0]得到-1，dp[1][1]从dp[1][0],排序了嘛，j从1是最小面值5都超大了，j=2的面值起码是6，dp[1][2]从dp[1][1]
                    // 2这行同理，从dp[2][0]传递
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
        return dp[amount].back();
    }
};
// @lc code=end
