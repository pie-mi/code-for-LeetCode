/*
 * @lc app=leetcode.cn id=122 lang=c
 *
 * [122] 买卖股票的最佳时机 II
 */

// @lc code=start

/*本来还是大一时的三指针思路，但处理越界很复杂
忽然想起好似看到过类似的题，船过三峡，
只要算出所有相邻两天的差值即可*/
int maxProfit(int* prices, int pricesSize){
    int *p, *q;
    int profit = 0;
    p = prices;
    if(pricesSize==1)
        return profit;
    q = p+1;//不要p++，p自己也变了
    int dailyGap[pricesSize - 1];
    for (int i = 0; i < pricesSize-1; i++)
    {
        dailyGap[i] = *q - *p;
        p++;
        q++;
    }
    for (int i = 0; i < pricesSize-1; i++)
    {
        if (dailyGap[i]>0)
        {
            profit += dailyGap[i];
        }
        
    }
    return profit;
}
// @lc code=end

