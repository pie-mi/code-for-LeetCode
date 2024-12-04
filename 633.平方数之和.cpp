/*
 * @lc app=leetcode.cn id=633 lang=cpp
 *
 * [633] 平方数之和
 */
#include <cmath>
// @lc code=start
class Solution {
public:

    bool is_int(double num){
        return num - (int)num == 0 ? true : false;
    }
/*
之前一直想两个for，平方根前一个个试探
忽然想移项，看a^2=c-b^2，之前第一次尝试好像也看到过答案XD
*/
    bool judgeSquareSum(int c) {
        int sqroot = sqrt(c);
        double a;
        bool result = false;
        for (int i = 0; i <= sqroot; i++)
        {

            a = sqrt(c - i * i);
            //return is_int(a) ? true : false;
            //result = is_int(a) ? true : false;
            if (is_int(a))
            {
                result = true;
                break;//得到就退出啦，忘了，就一直到平方根，而且将result更新为错误的
            }
            
        }
        return result;
    }
};
// @lc code=end

