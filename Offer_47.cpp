#include <vector>
#include <stack>
using namespace std;

#define down true
#define right false

int calcuValue(vector<vector<int> >& grid , vector<bool> &oredr)
{
    vector<bool>::iterator guci;
    int value = grid[0][0];
    int m_down = 0;
    int n_right = 0;
    for ( guci = oredr.begin(); guci != oredr.end(); guci++)
    {
        if (*guci)
        {
            m_down++;
        }
        else
        {
            n_right++;
        }
        value += grid[m_down][n_right];
    }
    return value;
}

int maxValue(vector<vector<int> >& grid) {
    //贪心不行，题目标签是动态规划，也不是剪枝回溯。因为贪心可能把某一列最大的值忽略了，选了眼前最大的
    /*递归版  超时
    int result = 0;
        int rightResult = 0;
        int downResult = 0;
        //result += grid[0][0];
        if (grid.size() >= 1 || grid[0].size() >= 1) {
            if (grid[0].size() > 1) {
                vector<vector<int>> rightgrid = grid;
                for (int i = 0; i < rightgrid.size(); i++) {
                    rightgrid[i].erase(rightgrid[i].begin());
                }
                rightResult = maxValue(rightgrid);
            }
            if (grid.size() > 1) {
                vector<vector<int>> downgrid = grid;
                downgrid.erase(downgrid.begin());
                downResult = maxValue(downgrid);

            }
            result = grid[0][0] + max(rightResult, downResult);
        }
        return result;
    */
    
    //变为迭代，每次需要的缩小矩阵也要存储，麻烦哦
    //或许理解为m个向下和n个向右的排列组合
    /*
    bool flag = false;
    //stack<bool> order;
    vector<bool> order;
    int m = grid.size();
    int n = grid[0].size();
    int result;
    for (int i = 0; i < m; i++)
    {
        order.push_back(down);
    }
    for (int i = 0; i < n; i++)
    {
        order.push_back(right);
    }
    result = calcuValue(grid, order);
    while (!order.empty())
    {
        result = max(result, calcuValue(grid, order));
        int m_pop = 0; //pop出来多少个down，待会塞回去
        int n_pop = 0;
//应该一直pop到另一个！pop出来两个都是down，交换再塞回去没有意义，一样的路径
        order.pop_back();
    }
    */
    
    //看答案了，才明白这题的动态规划
    //到达d[i,j]只有d[i-1,j]和d[i,j-1]两种方法，取其较大者加上d[i,j]
    //可以额外用同样大小的矩阵记录每个格子最大值，也可原地更新
    //注意两条边边只有一种方法可到达
    int m_down = grid.size();
    int n_right = grid[0].size();
    vector<vector<int>>::iterator it;
    for ( it = grid.begin(); it != grid.end(); it++) //处理竖边
    {
        vector<vector<int>>::iterator kuci = it + 1;
        if (kuci==grid.end())
        {
            break;
        }
        
        *(kuci->begin()) = *(kuci->begin()) + (*it)[0];
    }
    for (int i = 0; i < n_right-1; i++) //处理横边
    {
        grid[0][i + 1] = grid[0][i + 1] + grid[0][i];
    }
    for (int m = 1; m < m_down; m++)
    {
        for (int n = 1; n < n_right; n++)
        {
            grid[m][n] = grid[m][n] + max(grid[m][n - 1], grid[m - 1][n]);
        }
        
    }
    return grid[m_down-1][n_right-1];
}