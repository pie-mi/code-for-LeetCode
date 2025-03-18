/*
 * @lc app=leetcode.cn id=123 lang=cpp
 *
 * [123] 买卖股票的最佳时机 III
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start

// 2025.3.15 在美国站上运行不通过，才发现应该没AC，重新思考修改
/*
看人家解法复刻了
Accepted
214/214 cases passed (0 ms)
Your runtime beats 100 % of cpp submissions
Your memory usage beats 67.85 % of cpp submissions (85.4 MB)
*/
class Solution
{
private:
    // from买卖股票I
    int singleSideMaxProfit(vector<int> &part)
    {
        int i = 0, j = i + 1;
        int profit = 0;
        while (j < part.size())
        {
            if (part[i] < part[j])
            {
                profit = part[j] - part[i] > profit ? part[j] - part[i] : profit;
                // i++; don't move i, just move j
                j++;
            }
            else
            {
                i = j;
                j++;
            }
        }
        return profit;
    }

public:
    int maxProfit(vector<int> &prices); /*
     {
         // 先算单笔的最大利润，再清除数组这一段，并且分割两段，分别再来一次最大利润
         // 错误，如0 0 3 4 2 6
         //  3 5 0 4 7 8 2 10是0-8、2-10最大，不是3-5、0-10
         // 所以应该每一次出现下降就分段
         // 重复情况3 5 4 7 3 5 4 7这个是3-7 3-7最大，不是每次下降就获利直接重新看后一段
         // 改一个更小的2可能更清楚3 5 2 7 3 5 4 7，2-7 3-7最大，后面有小于等于i指针自己就获利看后一段，因为后面如果升肯定赚得不比i自己少
         // 单只有3 5 4 7就是3-5 4-7最大，而不是3-7
         // 即每一轮循环都要不断扫下去，不管中间有没有下降，更新从i到j的最大获利，但是如果遇到比i更小的，就可以直接获利，i移到更小处继续循环
         // 0 0 3 1 4 3 3 7 和 3 3 7 0 0 3 1 4居然不一样，前者0-3 1-7，后者3-7 0-4
         // 递归，找分割点，两边调用maxProfit求最大，递归那有可能是动态规划哦，状态转换嘛，一开始也想过，没想出来，看了label确实有动态规划

         int currentMin = part[0];
         int currentProfit = 0;
         vector<int> profit;
         // profit.push_back(0);
         int result = 0;
         int i = 0, j = i + 1;
         while(j < part.size())
         {
             // currentMin = part[i] < currentMin ? part[i] : currentMin;
             // currentMin = part[i];
             if (j < part.size() && part[j] <= part[i])
             {
                 //currentMin = part[i + 1];
                 profit.push_back(currentProfit);
                 i = j;
                 j++;
                 currentProfit = 0;
                 continue;
             }
             currentProfit = part[j] - part[i] > currentProfit ? part[j] - part[i] : currentProfit;
             j++;
             /*
             if (part[i] - currentMin > currentProfit)
             {
                 // profit[j] = part[i] - currentMin;
                 profit.push_back(part[i] - currentMin);
             }
             */
                                    /*
            }
            sort(profit.begin(), profit.end());
            if (!profit.empty())
            {
                result = *profit.rbegin();
                profit.pop_back();
            }
            if (!profit.empty())
                result += *profit.rbegin();
            return result;
            }*/
};
/*
int Solution::maxProfit(vector<int> &prices)
{   // 超时！ time exceeded
    int segPoint = 1;
    int result = 0;
    //先调用一次singleSide的，表示分割点在数组前/后，即整个数组只买卖一次
    result = singleSideMaxProfit(prices);
    while (segPoint < prices.size())
    {
        vector<int> former(prices.begin(), prices.begin() + segPoint); //左闭右开
        vector<int> latter(prices.begin() + segPoint, prices.end());
        auto temp = singleSideMaxProfit(former) + singleSideMaxProfit(latter);
        result = temp > result ? temp : result;
    }
    return result;
}
*/

// 看了leetcode美国站上的印度小哥的worst to best
// 里面第二方法就是加"break point"，但人家两个方向且加了记忆化搜索，有点像239题官方第三种解法
// 左到右：记住目前最小，也用数组记住每个i最大，看当前获利能否比之前大，就是以i为分割点，到目前能最大的获利
// 右往左：记住目前最大，看j到结尾最大获利
// 然后两个数组相加，即对应的下标作为分割点两边能够最大获利相加，再找出最大的即可
int Solution::maxProfit(vector<int> &prices)
{
    //int segPoint = 1;
    vector order(prices.size(), 0);
    vector backorder(prices.size(), 0);
    int currentMin = prices[0];
    int currentMax = *prices.rbegin();
    int result = 0;
    for (int i = 1; i < prices.size(); i++)
    {
        currentMin = prices[i] < currentMin ? prices[i] : currentMin;
        order[i] = prices[i] - currentMin > order[i - 1] ? prices[i] - currentMin : order[i - 1];
    }
    for (int j = prices.size() - 2; j >= 0; j--)
    {
        currentMax = prices[j] > currentMax ? prices[j] : currentMax;
        backorder[j] = currentMax - prices[j] > backorder[j + 1] ? currentMax - prices[j] : backorder[j + 1];
    }
    for (int k = 0; k < prices.size(); k++)
    {
        result = order[k] + backorder[k] > result ? order[k] + backorder[k] : result;
    }

    return result;
}
// @lc code=end
