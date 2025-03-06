/*
 * @lc app=leetcode id=343 lang=c
 *
 * [343] Integer Break
 */
#include <math.h>
#include <stdlib.h>
// @lc code=start
/*
Accepted
50/50 cases passed (0 ms)
Your runtime beats 100 % of c submissions
Your memory usage beats 30.2 % of c submissions (8 MB)
*/
/*
看hello-algo的贪心后而来。

一开始自己分析，想到了和凑硬币有点像，都能一个个分解为1，但没能推出动态规划；
也想到中学的栅栏围成矩形，维持边长相等(即正方形)面积最大；
但最后用6做例子，以为从中间分开就是最大，汗~题目提示就用7和10

1. 算术-几何平均数不等式(AM-GM不等式)可以证明拆分成尽可能多的某个特定的正整数，则这些正整数的乘积最大;
2. 可以用f(x)=x^(n/x)换成底数e可以证明分为e时乘积最大，靠近的整数则是3
3. 0、1、2、3这几个直接写，再分情况：若除3之后余0，那就正好；
                                余1，因为2*2>1*3，要退回一个3，和1凑回2*2；
                                若余2，就剩下这个2即可

另外评论区看到动态规划亦可，也很巧妙，问DeepSeek看过程才看懂，效率不够贪心好
*/

int integerBreak(int n)
{
    int count3, yushu;
    if (n <= 3)
    {
        return n - 1;
    }
    count3 = n / 3;
    yushu = n % 3;
    switch (yushu)
    {
    /*case 0:
        return (int)pow(3, count3);
        break;*/
    case 1:
        return (int)pow(3, count3 - 1) * 2 * 2;
        break;
    case 2:
        return (int)pow(3, count3) * 2;
        break;
    }
    /*
    integerBreak 函数被声明为返回一个 int 类型的值，不过在 switch 语句之后没有返回语句，
    这就可能导致控制流在不返回任何值的情况下结束函数，从而引发编译错误。
    专门留一个case在这里return
    */
    return (int)pow(3, count3);

    /*动态规划
    当 i≥2 时，假设对正整数 i 拆分出的第一个正整数是 j（1≤j<i），则有以下两种方案：
    将 i 拆分成 j 和 i−j 的和，且 i−j 不再拆分成多个正整数，此时的乘积是 j×(i−j)；
    将 i 拆分成 j 和 i−j 的和，且 i−j 继续拆分成多个正整数，此时的乘积是 j×dp[i−j]。

    int dp[n + 1];
    dp[0] = dp[1] = 0;
    dp[2] = 1;
    for (int i = 2; i <= n; i++) // 不用到n+2
    {
        int temp = 0;
        for (int j = 1; j <= i / 2; j++) // 是i/2不是n/2
        {
            temp = fmax(temp, fmax(j * dp[i - j], j * (i - j))); // 写错成了temp = fmax(temp, dp[j] * (i - j)) T_T
        }
        dp[i] = temp;
    }
    return dp[n];
    */
}
// @lc code=end
