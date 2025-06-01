/*
 * @lc app=leetcode id=781 lang=cpp
 *
 * [781] Rabbits in Forest
 */
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
/*
Wrong Answer
34 / 56 testcases passed
[0,0,1,1,1] 应该要6
[0,0,2,2,2,2,2] 应该是8

Daily Coding Challenge Completed!
Accepted
0ms Beats100.00%
11.91MB Beats96.43%
*/
// @lc code=start
class Solution
{
public:
    int numRabbits(vector<int> &answers)
    {
        //[1,0,1,0,0]应当是5，0要特殊处理
        sort(answers.begin(), answers.end());
        auto non_zero = answers.begin();
        while (*non_zero == 0)
        {
            non_zero++;
        }
        for (auto it = non_zero; it < answers.end(); it++)
        {
            //这里需要把相邻的相等的处理，例如连续2,2,2，就是第一个2加上自己2之间的统一为一种颜色
            //不要删除元素，怕end之类的迭代器失效，其余置为-1即可，用第一个代表全部
            //10,10,10这种应该11个10之内都置零，虽然不满4个
            auto i = 1;
            for (; i <= *it && it + i != answers.end(); i++)
            {
                if (*(it + i) == *it)
                {
                    *(it + i) = -1;
                }
                else
                    break; //不够4个3，下一个已经不相等了
            }
            //*it = 0;
            if (it + i < answers.end()) //10,10,10会越界
                it += i - 1;
            else
                break;

            //if (*(it+*it) == *it)
            //{
            //    while (it != (it+*it))
            //    {
            //        *it = 0;
            //        it++;
            //    }
            //    *it = 0;
            //}
            
        }
               
        //auto last = unique(non_zero, answers.end());
        // answers.erase(last, answers.end());
        auto result = 0;
        for (auto it = answers.begin(); it != answers.end(); it++)
        {
            if (*it != -1)
            {
                result += *it;
                result++;
            }
        }
        return result; // + answers.size();
    }
};
// @lc code=end

int main()
{
    vector<int> ans2{10, 10, 10};
    Solution test;
    int rabbit2 = test.numRabbits(ans2);
    cout << rabbit2 << endl;
    return 0;
}