/*
 * @lc app=leetcode id=73 lang=cpp
 *
 * [73] Set Matrix Zeroes
 */
#include <vector>
#include <optional>
#include <climits>
using std::vector;
// @lc code=start
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        /*
        O(m+n)是第一反应，记录哪些行和列有0
        要求原地，想到位运算，与上下左右做与运算,不OK，emample2就是例子
        或者一行行来，整行整列与运算，只记录此行和此列？
        看了提示，也想过，用首行和首列以及特殊marker来记录，
        似乎optional要定义的，传进来的matrix不是这个，又要原地
        遍历行再遍历列，首行变更了只会影响首列，只要提前将matrix[0][0]处理好即可
        一直被自己困了，以为每个格子都要做一次所在行/列
        */
        
        // N/A  [[1,2,3,4],[5,0,7,8],[0,10,11,12],[13,14,15,0]]  myAnswer [[0,0,3,4],[0,0,0,0],[0,0,0,0],[0,0,15,0]]

        /*
        Accepted
        202/202 cases passed (0 ms)
        Your runtime beats 100 % of cpp submissions 其实根本不用与运算，是0就改首行/列，不是就下一个
        Your memory usage beats 94.52 % of cpp submissions (18.5 MB)
        */

        //这几个变量甚至还不影响matrix[0][0],也O(1)
        int marker00row = matrix[0][0], marker00col = marker00row, marker00;
        for (int i = 1; i < matrix[0].size(); i++)
            marker00row = marker00row && matrix[0][i];  //一开始都用了按位与"&"，感觉也没有问题但还是改为逻辑与
        
        for (int i = 1; i < matrix.size(); i++)
            marker00col = marker00col && matrix[i][0];
        marker00 = marker00row && marker00col;

        //遍历行
        int rowMarker;
        for (int i = 1; i < matrix.size(); i++)
        {
            rowMarker = matrix[i][0];
            for (int j = 0; j < matrix[0].size(); j++)
            {
                if (rowMarker && matrix[i][j] != 0)
                    rowMarker = rowMarker && matrix[i][j];
                else //为0则证明这一行有0，最终整行包括自己也要置为零
                {
                    matrix[i][0] = 0;
                    break;
                }              
            }
            if(!rowMarker)
                matrix[i][0] = 0;
        }
        
        //遍历列
        int colMarker;
        for (int i = 1; i < matrix[0].size(); i++)
        {
            colMarker = matrix[0][i];
            for (int j = 0; j < matrix.size(); j++)
            {
                if (colMarker && matrix[j][i] != 0)
                    colMarker = colMarker && matrix[j][i];
                else
                {
                    matrix[0][i] = 0;
                    break;
                }    
            }
            /*if(!colMarker) //最右下角是0，没有更新，上面的N/A，不过加上 && matrix[j][i] != 0也OK
                matrix[0][i] = 0;*/
        }

        //将matrix[0][0]也填好
        if(!marker00)
            matrix[0][0] = 0;
        
        //更新矩阵
        for (int i = 1; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[0].size(); j++)
            {
                if (!matrix[i][0])
                {
                    matrix[i][j] = 0;
                }
                else
                    break;
            }  
        }
        for (int i = 1; i < matrix[0].size(); i++)
        {
            for (int j = 0; j < matrix.size(); j++)
            {
                if (!matrix[0][i])
                {
                    matrix[j][i] = 0;
                }
                else
                    break;
            }  
        }

        /*本来以为这就OK了，没想到example2就不通过
        上边为了避免覆盖从1开始，导致首行和首列存在0的情况没有更新
        不过marker00row和marker00col已经记录了
        */
        if (!marker00row)
        {
            for (int i = 0; i < matrix[0].size(); i++)
            {
                matrix[0][i] = 0;
            }  
        }
        if (!marker00col)
        {
            for (int i = 0; i < matrix.size(); i++)
            {
                matrix[i][0] = 0;
            }  
        }
    }
};
// @lc code=end

