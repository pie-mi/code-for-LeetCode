/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 */

#include <vector>
#include <stack>
#include <queue>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //std::stack<int> bozi;
        /*的确可以用单向栈完成*/
        //queue<int> kuci;
        int profit = 0;
        if (prices.size()==1)
        {
            return profit;
        }
        /*
        for (int i = 0; i < prices.size(); i++)
        {
            for (int j = i+1; j < prices.size(); j++)
            {
                if (prices[i]<prices[j])
                {
                    //profit = ((prices[j] - prices[i]) > profit) ? prices[j] - prices[i] : profit;
                    profit = max(prices[j] - prices[i], profit);
                }
                
            }
            
        }
        */
        
        /*用队列，好像不行*/
        
        /*只有后面有更小的，且再后边有令其差值更大的
        */
       /*
        int minier;
        int gaper;
        for (int i = 1; i < prices.size(); i++)
        {
            if (prices[i-1]>prices[i])
            {
                minier = prices[i];
                for (int j = i+1; j < prices.size(); j++)
                {
                    if ((prices[j]-prices[i])>profit)
                    {
                        profit = prices[j] - prices[i];
                    }
                    
                }
                
            }
            
        }
        */

        //看了Leetcode上的答案
        int present_mini = prices[0];
        for (int i = 0; i < prices.size(); i++)
        {
            if (present_mini>prices[i])
            {
                present_mini = prices[i];
                continue;
            }
            profit = max(profit, prices[i] - present_mini);
        }
        
        return profit;
    }
};
// @lc code=end

