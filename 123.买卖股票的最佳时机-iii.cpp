/*
 * @lc app=leetcode.cn id=123 lang=cpp
 *
 * [123] 买卖股票的最佳时机 III
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //先算单笔的最大利润，再清除数组这一段，并且分割两段，分别再来一次最大利润
        //错误，如0 0 3 4 2 6
        // 3 5 0 4 7 8 2 10是0-8、2-10最大，不是3-5、0-10
        //所以应该每一次出现下降就分段
        int currentMin;
        int currentProfit;
        vector<int> profit;
        //profit.push_back(0);
        int result;
        int j = 0;
        for (int i = 0; i < prices.size(); i++)
        {
            //currentMin = prices[i] < currentMin ? prices[i] : currentMin;
            currentMin = prices[i];
            if (i+1<prices.size() && prices[i+1]<prices[i])
            {
                currentMin = prices[i + 1];
                j++;
                continue;
            }
            if (prices[i]-currentMin>currentProfit)
            {
                //profit[j] = prices[i] - currentMin;
                profit.push_back(prices[i] - currentMin);
            }
            
        }
        sort(profit.begin(), profit.end());
        result = *profit.rbegin();
        profit.pop_back();
        result += *profit.rbegin();
        return result;
    }
};
// @lc code=end

