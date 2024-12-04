/*
 * @lc app=leetcode.cn id=56 lang=cpp
 *
 * [56] 合并区间
 */
#include <algorithm>
#include <vector>
using namespace std;
// @lc code=start
//!!!就是华为OD技术一面的手撕代码题！！！
class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        vector<vector<int>> result;
        mysort(intervals);
        //auto it = intervals.begin();
        //auto jt = it + 1;
        for (auto it = intervals.begin(); it != intervals.end();)
        {
            int currMAX = (*it)[1];
            auto jt = it + 1;
            /*
            if (jt == intervals.end())
            {
                result.emplace_back(*it);
            }
            */
            for (; jt != intervals.end(); jt++)
            {
                currMAX = max(currMAX, (*it)[1]);
                if (currMAX >= (*jt)[0]) //(*it)[1]>=(*jt)[0]
                {
                    if (currMAX >= (*jt)[1]) //(*it)[1]>=(*jt)[1]
                    {
                        if ((jt+1)!=intervals.end())
                        {
                            continue;
                        }
                        else
                        {
                            vector<int> temp;
                            temp.emplace_back((*it)[0]);
                            temp.emplace_back(currMAX);
                            result.emplace_back(temp);
                            it = jt + 1;
                            break;
                        }
                    }
                    else // 但是可能紧接下一个也连着[1,3][3,5][5,6][8,9]  [1,6][3,5][6,7]
                    {
                        currMAX = (*jt)[1];
                        if ((jt + 1) != intervals.end() && currMAX >= (*(jt + 1))[0])
                            continue;
                        else
                        {
                            vector<int> temp;
                            temp.emplace_back((*it)[0]);
                            temp.emplace_back(currMAX);
                            result.emplace_back(temp);
                            it = jt + 1; //currMAX >= (*jt)[0]意味着jt所指这个区间已经纳入范围
                            break;
                        }
                    }
                }
                else
                {
                    vector<int> temp;
                    temp.emplace_back((*it)[0]);
                    temp.emplace_back(currMAX);
                    result.emplace_back(temp);
                    it = jt; //意味着it与jt所指没有重叠之处，断开的，jt所指还未处理
                    break;
                }
            }

            //it = jt + 1; // X错误！应分开为以上两种情况设定it，即下一次开始之处
            if (it==intervals.end()-1 && jt==intervals.end())
            {
                result.emplace_back(*it);
                break;
            }
            
        }
        /*
        if (it == intervals.end() && jt != intervals.end())
        {
            result.emplace_back(*(it - 1));
        }
        
        if (it == intervals.end())
        {
            result.emplace_back(*jt);
        }
        */
        return result;
    }

private:
    void mysort(vector<vector<int>> &intervals)
    {
        vector<pair<int, int>> shift2pair;
        for (auto it = intervals.begin(); it != intervals.end(); it++)
        {
            shift2pair.emplace_back(make_pair((*it)[0], (*it)[1]));
        }
        sort(shift2pair.begin(), shift2pair.end());
        intervals.clear();
        for (pair<int, int> i : shift2pair)
        {
            vector<int> a;
            a.emplace_back(i.first);
            a.emplace_back(i.second);
            intervals.emplace_back(a);
        }
    }
};
// @lc code=end
