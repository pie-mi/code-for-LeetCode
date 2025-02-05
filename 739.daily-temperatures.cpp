/*
 * @lc app=leetcode id=739 lang=cpp
 *
 * [739] Daily Temperatures
 */
#include <stack>
#include <utility>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
public:
    vector<int> dailyTemperatures(vector<int> &temperatures)
    {
        // 看了栈这个标签进来的
        // 当前最高入栈于栈顶，有更高的就弹走
        // 若中间有低的，小于栈顶就入栈，又有高于栈顶的就不断弹走与新栈顶比较

        stack<pair<int, int>> higerTemperatures;               // first是温度，second是下标
        vector<int> result(temperatures.size(), 0);            // AI补全，clever，中间的最高温要到末尾才知道没有更高的，初始化先给个0，不用后面再如何找回对应下标填0
        higerTemperatures.push(make_pair(temperatures[0], 0)); // 题目说至少有一个，非空
        for (auto i = 1; i < temperatures.size(); i++)
        {

            while (!higerTemperatures.empty() && temperatures[i] > higerTemperatures.top().first)
            {
                int index = higerTemperatures.top().second;
                result[index] = i - index; // AI 下标差就是天数
                higerTemperatures.pop();
            }

            higerTemperatures.push(make_pair(temperatures[i], i)); // AI 入栈，先比较再决定是否入栈，自己也入栈
        }
        return result;
    }
};
// @lc code=end
