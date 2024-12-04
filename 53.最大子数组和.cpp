/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子数组和
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        // 想了最基础的两个for，每一个元素都从头扫到自己，看哪个开头使结果最大
        // 想动态规划，但没有想出来递推关系，前面最大可能并不与自己连续相连
        // 想了从后面开始，看自己后面的总和是否大于零

        if (nums.size() == 1)
        {
            return nums[0];
        }
        bool all_negative = nums[nums.size() - 1] < 0; // 看看是不是全负数
        vector<int> tailsum(nums.size(), 0);
        vector<int> frontsum(nums.size(), 0);
        int addtail = 0;
        for (int i = nums.size() - 2; i >= 0; i--)
        {
            addtail += nums[i + 1];
            tailsum[i] = addtail;
            if (all_negative && nums[i] < 0)
            {
                ;
            }
            else
                all_negative = false;
        }
        if (all_negative)
        {
            int Max = nums[0];
            for (int n : nums)
            {
                Max = Max < n ? n : Max;
            }
            return Max;
        }
        int addfront = 0;
        for (int i = 1; i < frontsum.size(); i++)
        {
            addfront += nums[i - 1];
            frontsum[i] = addfront;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            tailsum[i] = tailsum[i] + nums[i]; // 求出每个数，包括自己到结尾的总和
        }
        for (int i = 0; i < nums.size(); i++)
        {
            frontsum[i] = frontsum[i] + nums[i]; // 求出每个数，从开头至包括自己的总和
        }

        int MAX_tail = tailsum[0];
        int MAX_tail_index = 0;
        int MAX_front = frontsum[0];
        int MAX_front_index = 0;
        for (int i = 0; i < tailsum.size(); i++)
        {
            if (tailsum[i] > MAX_tail)
            {
                MAX_tail = tailsum[i];
                MAX_tail_index = i;
            }
            // 找出最大值的下标，注意，只是到结尾最大，不到结尾可能更大，例1就是如此，用excel算算看
        }
        for (int i = 0; i < frontsum.size(); i++)
        {
            if (frontsum[i] >= MAX_front) // 这里加"="，多个相同的，找的是最后一个最大值
            {
                MAX_front = frontsum[i];
                MAX_front_index = i;
            }
        }
        /*我不知道是否能保证 MAX_tail_index<MAX_front_index 或两者有交集*/
        //[0,-3,1,1]就是反例，不能保证的！！！
        int biggestsum = 0;
        for (int i = MAX_tail_index; i <= MAX_front_index; i++)
        {
            biggestsum += nums[i];
        }

        // 关键：如果这个下标之后tailsum紧跟着还有>=0的，
        // 那说明它们都能让本来后面是 负的 变为 正的或0，把它们纳入麾下，再后面那些是负的，不够力，截去
        int tail_result = nums[MAX_tail_index];
        for (int j = MAX_tail_index + 1; j < tailsum.size(); j++)
        {
            if (tailsum[j] >= 0)
            {
                tail_result += nums[j];
            }
            else
                break; // 只要找到一个负的，就要断开了，就算后面还有大于零，但已经不连续的
            // 另外，如果最大都是负的，错误X那就自己就是，后面更“拖累”,是一致的
        }
        int front_result = nums[MAX_front_index];
        for (int j = 0; j < MAX_front_index; j++)
        {
            if (frontsum[j]>=0)
            {
                front_result += nums[j];
            }
            else
                break;
        }

        int result = max(tail_result, front_result);
        if (MAX_tail_index > MAX_front_index)
        {
            return result;
        }
        else
            return biggestsum;
    }
};
// @lc code=end

int Solution::maxSubArray(vector<int> &nums)
{
    //看了标签，想明了如何用动态规划
    //第一个元素最大和就是自己，第二个元素加入后最大和就是max(2nd元素自己或自己加前面最大和)，3rd也是如此
//PS 如果哦是子序列，那就将所有正数加起来就行，哈哈，子序列不要求连续嘛
    //[-2,1,-3,1]
    vector<int> dp_maxArraySum;
    dp_maxArraySum.emplace_back(nums[0]);
    int maxsum = nums[0];
    for (int i = 1; i < nums.size(); i++)
    {
        dp_maxArraySum.emplace_back(max(nums[i], nums[i] + dp_maxArraySum[i - 1]));
        maxsum = max(maxsum, dp_maxArraySum.back());
    }
    return maxsum;
}