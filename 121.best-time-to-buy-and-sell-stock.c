
/*
Runtime
0ms
Beats 100.00%
*/

// 做123题买卖股票时感觉想用到这个，直接写一遍

int maxProfit(int* prices, int pricesSize) {
    int i = 0, j = i + 1;
    int profit = 0;
    while(j < pricesSize)
    {
        if(prices[i] < prices[j])
        {
            profit = prices[j] - prices[i] > profit ? prices[j] - prices[i] : profit;
            // i++; don't move i, just move j
            j++;
            // continue;
        }
        else
        {
            i = j;
            j++;
        }
    }
    return profit;
}