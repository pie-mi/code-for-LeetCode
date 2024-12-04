/*
 * @lc app=leetcode.cn id=172 lang=cpp
 *
 * [172] 阶乘后的零
 */

// @lc code=start
class Solution
{
public:
    // 今天光大银行笔试刚好有 计算200! 末尾几个0
    /*实际就是统计几多个5*/
    int trailingZeroes(int n)
    {
        int result = 0;
        //int tailnum; // 只需要关注尾数，最后位
        for (int i = 5; i <= n; i = i + 5)
        {
            /*if (i % 10000 == 0)
            {
                result += 4;
                continue;
            }
            else if (i % 1000 == 0)
            {
                result += 3;
                continue;
            }
            else if (i % 100 == 0)
            {
                result += 2;
                continue;
            }
            else if (i % 10 == 0)
            {
                result++;
                continue;
            }*/
            if (i % 3125 == 0)
            {
                result += 5;
            }
            else if (i % 625 == 0)
            {
                result += 4;
            }
            else if (i % 125 == 0)
            {
                result += 3;
            }
            else if (i % 25 == 0)
            {
                result += 2;
            }
            else if (i % 5 == 0)
            {
                result++;
            }

            //tailnum = (tailnum * i) % 10;
        }
        return result;
    }
};
// @lc code=end
