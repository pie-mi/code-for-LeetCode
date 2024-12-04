/*
 * @lc app=leetcode.cn id=70 lang=cpp
 *
 * [70] 爬楼梯
 */
#include <stack>
// @lc code=start
class Solution {
public:
    int climbStairs(int n) {
        //递归或栈，本质一样，递归是OS栈嘛
        /*
        思路是：剩余3级台阶，走法跟2级的、1级的有关，
        即2级再走1下，1级再走2下；剩余4级台阶，走法跟3级、2级有关。
        即只与未来的两级有关联，反过来，递推“4=3+2”、“3=2+1”
        */
        if (n==1)
        {
            return 1;
        }
        if(n==2)
            return 2;
        int result;

        /*很简洁的递归，可惜超时A_A
        result = climbStairs(n - 1) + climbStairs(n - 2);
        */
        std::stack<int> bozi;
        int i = n;
        while (i>2)
        {
            bozi.push(result);
            i--; //又忘了n--之后n变了，下面n-2直接过了
        }
        bozi.push(2);
        bozi.push(1);
        //每次pop出前2个，相加，修改给top，top有可以修改的重载
        while (n-2>0)//!bozi.empty()
        {
            int former2 = bozi.top();
            bozi.pop();
            //result = former2;
            if (!bozi.empty())//这个if应该多余了
            {
                int former1 = bozi.top();
                bozi.pop();
                bozi.top() = former1 + former2;
                bozi.push(former1);
            }
            n--;
        }
        bozi.pop(); //因为修改后又会压回去一个，这个是n-1的答案
        result = bozi.top();
        return result;
    }
};
// @lc code=end

