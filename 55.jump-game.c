/*
 * @lc app=leetcode id=55 lang=c
 *
 * [55] Jump Game
 */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*
Wrong Answer 注释掉的
171/174 cases passed (N/A) [2,0,1,0,1]

Accepted
174/174 cases passed (3 ms)
Your runtime beats 22.83 % of c submissions
Your memory usage beats 33.03 % of c submissions (10.7 MB)
*/

// @lc code=start
bool canJump(int *nums, int numsSize)
{
    // 例子提示想到将元素和下标相加，前一个3与后一个2都只能到同一个位置，
    // 相加的结果表示能达到的最远下标
    // 贪心，在窗口内能到达更远的下标就选，如果窗口内没有更大就无法到达
    if (numsSize == 1)
        return true;
    int i = 0, j = 1;
    bool result = false;
    int weighted[numsSize]; // C99之后支持变量定义数组长度
    for (int i = 0; i < numsSize; i++)
        weighted[i] = i + nums[i];

    while (i < numsSize)
    {
        j = nums[i];
        int temp = 1;
        while (temp <= j)
        {
            if (i + temp >= numsSize - 1)
            {
                result = true;
                goto END;
            }
            else if (i + temp < numsSize - 1 && weighted[i] < weighted[i + temp])
            {
                i += temp;
                break;
            }
            temp++;
        }
        if (temp > j)
        {
            // 是循环到窗口末尾都没有一个能前进的，就是完成不了
            // 如果上面是break出来的则以新起点继续
            result = false;
            break;
        }

        /*
        if (temp > j)
        {
            // 是循环到窗口末尾都没有一个能前进的，就是完成不了
            // 如果上面是break出来的则以新起点继续
            result = false;
            break;
        }
        else if (i + temp >= numsSize - 1) // break出来的，但i已经加了temp，这边再加，超出了
        {
            // 是因为已经到数组末尾了而退出循环，即已到终点
            result = true;
            break;
        }
        // else //是if里break出来的，即窗口内找到了能到更远的
        */
    }
END:
    return result;
}
// @lc code=end

int main()
{
    int nums[] = {2, 5, 3, 1, 1, 1, 1, 1, 2, 4, 0, 1};
    bool can = canJump(nums, 12);
    if (can)
        printf("%s", "True");
    else
        printf("%s", "False");
    return 0;
}
