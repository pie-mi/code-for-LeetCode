/*
 * @lc app=leetcode id=502 lang=cpp
 *
 * [502] IPO
 */
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>
using namespace std;

/*
Time Limit Exceeded
32/40 cases passed (N/A)

Accepted    AI analyse O((N+K)Logn) 
40/40 cases passed (366 ms)
Your runtime beats 5.09 % of cpp submissions
Your memory usage beats 5.19 % of cpp submissions (184.7 MB)
*/

// @lc code=start
class Solution
{
public:
    int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital)
    {
        // 有可能全都是0资本的利润最大
        // 按每个资本分开建堆，每个堆只保留k个，最大堆，堆顶是当前资本最大利润
        int currCap = w;
        int lastCap = 0; // 记录上一次已加入
        map<int, priority_queue<int>> maxProfitInDiffCap;
        priority_queue<int> heap;
        for (auto i = 0; i < capital.size(); i++)
        {
            maxProfitInDiffCap[capital[i]] = heap;
        }
        for (auto i = 0; i < capital.size(); i++)
        {
            maxProfitInDiffCap[capital[i]].emplace(profits[i]);
        }
        int count = 0; // 不超过k个项目
        // 感觉需要对capital排序，才能知道哪些项目当前可以操作,不用unordered了

        // AI，用struct定义compare对象，则下方heapOfheap后不用括号compare
        auto compare = [](const pair<int, map<int, priority_queue<int>>::iterator> &a,
                          const pair<int, map<int, priority_queue<int>>::iterator> &b)
        {
            return a.first < b.first;
        };
        // 每个堆的堆顶构成一个堆
        priority_queue<pair<int, map<int, priority_queue<int>>::iterator>, vector<pair<int, map<int, priority_queue<int>>::iterator>>, decltype(compare)>
            heapOfheap(compare);
        // auto init = maxProfitInDiffCap.upper_bound(w);
        auto alreadyInclude = maxProfitInDiffCap.begin();
        auto newInclude = maxProfitInDiffCap.upper_bound(currCap);

        while (count < k)
        {
            int maxProfit = 0;
            auto whichCap = newInclude;

            // 加入资本够的堆
            for (auto start = alreadyInclude; start != newInclude; start++)
            {
                if (!start->second.empty())
                    heapOfheap.push(make_pair(start->second.top(), start));
            }
            if (!heapOfheap.empty())
            {
                lastCap = currCap;
                currCap += heapOfheap.top().first;
                whichCap = heapOfheap.top().second;
                heapOfheap.pop();
                whichCap->second.pop();
                // 对比AI的才发现忘了将原堆的新堆顶补充回来
                if (!whichCap->second.empty())
                    heapOfheap.push({whichCap->second.top(), whichCap});
            }
            else
            {
                // 全部堆都为空
                break;
            }
            alreadyInclude = newInclude;
            newInclude = maxProfitInDiffCap.upper_bound(currCap);
            count++;
        }
        return currCap;
    }
};
// @lc code=end

int Solution::findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital)
{
    // 有可能全都是0资本的利润最大
    // 按每个资本分开建堆，每个堆只保留k个，最大堆，堆顶是当前资本最大利润
    int currCap = w;
    map<int, priority_queue<int>> maxProfitInDiffCap;
    priority_queue<int> heap;
    for (auto i = 0; i < capital.size(); i++)
    {
        maxProfitInDiffCap[capital[i]] = heap;
    }
    for (auto i = 0; i < capital.size(); i++)
    {
        maxProfitInDiffCap[capital[i]].emplace(profits[i]);
    }
    int count = 0; // 不超过k个项目
    // 感觉需要对capital排序，才能知道哪些项目当前可以操作,不用unordered了
    while (count < k)
    {
        auto it = maxProfitInDiffCap.upper_bound(currCap);
        int maxProfit = 0;
        auto whichCap = it;
        for (auto i = maxProfitInDiffCap.begin(); i != it; i++)
        {
            if (!i->second.empty() && maxProfit < i->second.top())
            {
                maxProfit = i->second.top();
                whichCap = i;
            }
        }
        currCap += maxProfit;
        if (whichCap != maxProfitInDiffCap.end()) // case 4 k=10 cap.size=3
            whichCap->second.pop();               // 已经做了这个项目
        count++;
    }
    return currCap;
}