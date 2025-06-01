/*
 * @lc app=leetcode id=994 lang=cpp
 *
 * [994] Rotting Oranges
 */
#include <vector>
using namespace std;

/*
Accepted
307/307 cases passed (0 ms)
Your runtime beats 100 % of cpp submissions
Your memory usage beats 99.5 % of cpp submissions (16.5 MB)
*/

// @lc code=start
class Solution
{
public:
    int orangesRotting(vector<vector<int>> &grid)
    {
        // 如果只是判断是否能全部感染rotten，那就是看是否连通图
        // 但需要知道最短分钟，那就要一步步模拟了，新感染rotten的标记为3、4、5...
        // 避免这分钟感染的就传给下一个了
        int count = 0;
        int m = grid.size();
        int n = grid[0].size();
        const int base = 3;
        while (infect(grid, base + count))
        {
            count++;
        }

        // 完成所有感染后看是否有好橘子
        for (auto i = 0; i < m; i++)
        {
            for (auto j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    count = -1;
                    break;
                }
            }
        }
        return count;
    }

private:
    // 感染此分钟附近的，并返回是否还有新感染，即有没有下一分钟
    // 优化或许用哈希表记录，就不用每次遍历一遍矩阵
    bool infect(vector<vector<int>> &grid, int vary)
    {
        bool haveNewInfection = false;
        int m = grid.size();
        int n = grid[0].size();
        for (auto i = 0; i < m; i++)
        {
            for (auto j = 0; j < n; j++)
            {
                if (grid[i][j] == vary - 1) // 上一分钟变rotten的标记数值
                {
                    // 只infect为1的橘子
                    if (i >= 1 && j >= 1 && i < m - 1 && j < n - 1)
                    {
                        // 四个方向
                        if (grid[i - 1][j] == 1)
                        {
                            grid[i - 1][j] = vary;
                            haveNewInfection = true;
                        }
                        if (grid[i + 1][j] == 1)
                        {
                            grid[i + 1][j] = vary;
                            haveNewInfection = true;
                        }
                        if (grid[i][j - 1] == 1)
                        {
                            grid[i][j - 1] = vary;
                            haveNewInfection = true;
                        }
                        if (grid[i][j + 1] == 1)
                        {
                            grid[i][j + 1] = vary;
                            haveNewInfection = true;
                        }
                    }
                    else if (i == 0 && j + 1 < n && j >= 1)
                    {
                        if (grid[i][j + 1] == 1)
                        {
                            grid[i][j + 1] = vary;
                            haveNewInfection = true;
                        }
                        if (grid[i][j - 1] == 1)
                        {
                            grid[i][j - 1] = vary;
                            haveNewInfection = true;
                        }
                        if (i + 1 < m && grid[i + 1][j] == 1) // 预防越界
                        {
                            grid[i + 1][j] = vary;
                            haveNewInfection = true;
                        }
                    }
                    else if (i == m - 1 && j + 1 < n && j < n - 1)
                    { //[[1,2]]变成[[2/3,0]]后会越界，加上判断才行
                        if (i - 1 >= 0 && grid[i - 1][j] == 1)
                        {
                            grid[i - 1][j] = vary;
                            haveNewInfection = true;
                        }
                        if (j - 1 >= 0 && grid[i][j - 1] == 1)
                        {
                            grid[i][j - 1] = vary;
                            haveNewInfection = true;
                        }
                        if (grid[i][j + 1] == 1)
                        {
                            grid[i][j + 1] = vary;
                            haveNewInfection = true;
                        }
                    }
                    else if (j == 0 && i >= 1 && i < m - 1)
                    {
                        if (grid[i - 1][j] == 1)
                        {
                            grid[i - 1][j] = vary;
                            haveNewInfection = true;
                        }
                        if (grid[i + 1][j] == 1)
                        {
                            grid[i + 1][j] = vary;
                            haveNewInfection = true;
                        }
                        if (j + 1 < n && grid[i][j + 1] == 1) // 预防越界
                        {
                            grid[i][j + 1] = vary;
                            haveNewInfection = true;
                        }
                    }
                    else if (j == n - 1 && i >= 1 && i < m - 1)
                    {
                        if (grid[i - 1][j] == 1)
                        {
                            grid[i - 1][j] = vary;
                            haveNewInfection = true;
                        }
                        if (grid[i + 1][j] == 1)
                        {
                            grid[i + 1][j] = vary;
                            haveNewInfection = true;
                        }
                        if (j >= 1 && grid[i][j - 1] == 1)
                        {
                            grid[i][j - 1] = vary;
                            haveNewInfection = true;
                        }
                    }
                    else if (i == 0 && j == 0)
                    {
                        // [[2]]避免越界
                        if (i + 1 <= m - 1 && grid[i + 1][j] == 1)
                        {
                            grid[i + 1][j] = vary;
                            haveNewInfection = true;
                        }

                        if (j + 1 <= n - 1 && grid[i][j + 1] == 1)
                        {
                            grid[i][j + 1] = vary;
                            haveNewInfection = true;
                        }
                    }
                    else if (i == m - 1 && j == 0)
                    {
                        if (i - 1 >= 0 && grid[i - 1][j] == 1)
                        {
                            grid[i - 1][j] = vary;
                            haveNewInfection = true;
                        }

                        if (j + 1 <= n - 1 && grid[i][j + 1] == 1) //[[0],[2]]
                        {
                            grid[i][j + 1] = vary;
                            haveNewInfection = true;
                        }
                    }
                    else if (i == 0 && j == n - 1)
                    {

                        if (i + 1 <= m - 1 && grid[i + 1][j] == 1) //[[0,2]]
                        {
                            grid[i + 1][j] = vary;
                            haveNewInfection = true;
                        }
                        if (j - 1 >= 0 && grid[i][j - 1] == 1)
                        {
                            grid[i][j - 1] = vary;
                            haveNewInfection = true;
                        }
                    }
                    else if (i == m - 1 && j == n - 1)
                    {
                        if (i - 1 >= 0 && grid[i - 1][j] == 1)
                        {
                            grid[i - 1][j] = vary;
                            haveNewInfection = true;
                        }

                        if (j - 1 >= 0 && grid[i][j - 1] == 1)
                        {
                            grid[i][j - 1] = vary;
                            haveNewInfection = true;
                        }
                    }

                    grid[i][j] = 0; // 此分钟的rotten再后边就设为0，化作春泥，免得每次都重复四方向寻找
                }
            }
        }
        return haveNewInfection;
    }
};
// @lc code=end
