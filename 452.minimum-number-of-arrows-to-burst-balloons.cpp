/*
 * @lc app=leetcode id=452 lang=cpp
 *
 * [452] Minimum Number of Arrows to Burst Balloons
 */
#include <vector>
#include <algorithm>
#include <iostream>

using std::vector, std::sort;

/*
28/50 cases passed (N/A)
目前重叠3 6，后序6 8、7 12、9 10，最佳是6 8并入，后两者合并，只需2箭，但逻辑写了6 8先和7 12合并成7 8
40/50 testcases passed，这个用例5000个区间，expected是63，但output了66
问AI后才知道思路是按结束点排序​​：将区间按结束点从小到大排序，确保每次射箭在最小的右端点。
​​维护当前交集的右端点​​：遍历时，若当前区间起始点超过当前右端点，则需新增箭，并更新右端点为该区间的结束点。
AI的Accepted，自己的思路就是排序之后合并重叠区间，让AI改写，很简短，不用i++跳过
32ms Beats98.16%
93.90MB Beats49.63%
AI按照自己思路改写的Accepted
54ms Beats39.53%
96.12MB Beats22.61%
*/

// @lc code=start
class Solution
{
public:
    int findMinArrowShots(vector<vector<int>> &points)
    {
        // sort一下，关键是如何合并区间，动态规划？
        std::sort(points.begin(), points.end(), [](const vector<int> &a, const vector<int> &b)
                  {if (a[0] == b[0])
                    {
                        return a[1] < b[1];
                    }
                    return a[0] < b[0]; }); // 其实sort默认就可以对二维数组排序，不用lambda表达式也可
        /*
        // 似乎如何划分合并区间影响不是很大，有断点不会影响总数，只是断开位置不同
        // 把相邻两个区间的重叠统计出来
        vector<vector<int>> mergeOverlap; //{points[0]};
        int minArrow = 1;
        int endpoint;                            // 记录目前mergeOverlap的最右端点，如果与当前左端点相等，先合并，例如目前为3 6，后序6 8、7 12、9 10
        for (auto i = 0; i < points.size(); i++) // 本来size()-1来避免下面i+1越界，但balloon4这个例子会达不到最后一个元素
        {
            if (!mergeOverlap.empty())
            {
                endpoint = mergeOverlap.back()[1];
                if (points[i][0] == endpoint)
                {
                    mergeOverlap.pop_back();
                    mergeOverlap.push_back({endpoint, endpoint});
                    // 应该不用push下一个，因为这里已经缩成一个点了，即使下一个也是这个点也OK
                    continue;
                }
            }
            if (i != points.size() - 1 && points[i][1] >= points[i + 1][0])
            {
                if (points[i][1] > points[i + 1][1]) // 如1 100、2 3，100比后区间右边界都大，应该以小的区间
                {
                    continue;
                }
                vector<int> temp{points[i + 1][0], points[i][1]};
                if (!mergeOverlap.empty() && mergeOverlap.back()[1] >= temp[0])
                {
                    //mergeOverlap[4 9] temp = [6 7]，这样完全包裹的取小的，不然就扩大了
                    if (mergeOverlap.back()[1] >= temp[1])
                    {
                        mergeOverlap.pop_back();
                        mergeOverlap.push_back(temp);
                    }
                    else
                    {
                        temp[1] = mergeOverlap.back()[1];
                        mergeOverlap.pop_back();
                        mergeOverlap.push_back(temp);
                    }
                }
                else
                {
                    mergeOverlap.push_back(temp);
                }
                i++; // 否则三者中两两有重叠又不能合成会错误合并，如2 3、3 4、4 5，一个个下去则前两者合成3 3，后两者又合成4 4
            }
            else if (!mergeOverlap.empty() && points[i][0] <= mergeOverlap.back()[1]) // 与后者不重叠但与之前已合并的重叠
            {
                //这里也会有被完全包裹的情况，balloon9就是，不仅当前左端点小于已合并的右端点，当前的右端点也小于已合并的右端点
                //靠AI用python画图对比debug出来的，数字太大了
                if (points[i][1] <= mergeOverlap.back()[1])
                {
                    mergeOverlap.pop_back();
                    mergeOverlap.push_back(points[i]);
                }
                else
                {
                    vector<int> temp{points[i][0], mergeOverlap.back()[1]};
                    mergeOverlap.pop_back();
                    mergeOverlap.push_back(temp);
                    // 这里不用i++
                }
            }
            else
            {
                mergeOverlap.push_back(points[i]);
            }
        }
        minArrow = std::max((int)mergeOverlap.size(), 1); // 只有一个气球时
        return minArrow;
        */
        
        //让AI帮我改写，一个个处理就好，一开始压一个进去，每次和merge最后的比
        vector<vector<int>> merged;
        merged.push_back(points[0]);
        for (int i = 1; i < points.size(); ++i)
        {
            auto &last = merged.back(); // 检查当前区间是否与合并后的最后一个区间重叠
            if (points[i][0] <= last[1])
            {
                // 合并，取右端点的较小值
                last[1] = std::min(last[1], points[i][1]);
            }
            else
            {
                merged.push_back(points[i]);
            }
        }
        return merged.size();
    }
};
// @lc code=end

// 根据AI给的思路写一下
// 按右端点排序，若当前左端点不超过目前记录右端点则不用管，超过则需要另一支箭，以这个右端点新开
int Solution::findMinArrowShots(vector<vector<int>> &points)
{
    std::sort(points.begin(), points.end(), [](const vector<int> &a, const vector<int> &b)
              { return a[1] < b[1]; });
    int minArrow = 1;
    auto endpoint = points[0][1];
    for (auto &&i : points)
    {
        if (i[0] > endpoint)
        {
            minArrow++;
            endpoint = i[1];
        }
    }
    return std::max(minArrow, 1);
}

int main()
{
    vector<vector<int>> balloon{{10, 16}, {2, 8}, {1, 6}, {7, 12}};                                                                                // 2
    vector<vector<int>> balloon2{{1, 2}, {2, 3}, {3, 4}, {4, 5}};                                                                                  // 2
    vector<vector<int>> balloon3{{1, 2}, {1, 2}, {1, 2}, {1, 2}};                                                                                  // 1
    vector<vector<int>> balloon4{{2, 7}, {3, 9}, {11, 17}, {8, 10}, {15, 70}, {100, 101}};                                                         // 4
    vector<vector<int>> balloon5{{2, 7}, {3, 9}, {11, 17}, {8, 10}, {15, 70}, {100, 101}, {102, 111}, {110, 111}, {110, 130}, {66, 99}, {1, 100}}; // 6 但运行得2
    vector<vector<int>> balloon6{{2, 7}, {3, 9}, {11, 17}, {8, 10}, {1, 100}}; // 3 但运行得1
    vector<vector<int>> balloon7{{7, 12}, {3, 9}, {3, 8}, {6, 8}, {9, 10}, {2, 9}, {0, 9}, {3, 9}, {0, 6}, {2, 8}}; // 2 但得出3
    vector<vector<int>> balloon8{{9, 12}, {1, 10}, {4, 11}, {8, 12}, {3, 9}, {6, 9}, {6, 7}}; // 2 得出1
    vector<vector<int>> balloon9{{77171087, 133597895}, {45117276, 135064454}, {80695788, 90089372}, {91705403, 110208054}, {52392754, 127005153}, {53999932, 118094992}, {11549676, 55543044}, {43947739, 128157751}, {55636226, 105334812}, {69348094, 125645633}}; //3 但得2
    //不OK了，第40个用例都显示不完T_T
    Solution test;
    auto arrow = test.findMinArrowShots(balloon);
    auto arrow2 = test.findMinArrowShots(balloon2);
    auto arrow3 = test.findMinArrowShots(balloon3);
    auto arrow4 = test.findMinArrowShots(balloon4);
    auto arrow5 = test.findMinArrowShots(balloon5);
    auto arrow6 = test.findMinArrowShots(balloon6);
    auto arrow7 = test.findMinArrowShots(balloon7);
    auto arrow8 = test.findMinArrowShots(balloon8);
    auto arrow9 = test.findMinArrowShots(balloon9);
    std::cout << arrow << std::endl;
    std::cout << arrow2 << "\n"
              << arrow3 << std::endl
              << arrow4 << "\n"
              << arrow5 << std::endl
              << arrow6 << "\n"
              << arrow7 << std::endl
              << arrow8 << "\n"
              << arrow9;
    return 0;
}