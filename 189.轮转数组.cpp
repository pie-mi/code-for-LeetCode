/*
 * @lc app=leetcode.cn id=189 lang=cpp
 *
 * [189] 轮转数组
 */
#include <algorithm>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
public:
    void rotate(vector<int> &nums, int k); /*
    {
        /*
        注意：数组只有2个元素，但轮转100次
        */
                                           /*方法一
                                                if (nums.size() == k)
                                                    ; // 什么也不用做
                                                else if (nums.size() > k)
                                                {
                                                    vector<int> hapii(nums.begin() + (nums.size() - k), nums.end());
                                                    nums.erase(nums.begin() + (nums.size() - k), nums.end());
                                                    //利用vector1.insert( vector1.end(), vector2.begin(), vector2.end() )
                                                    hapii.insert(hapii.end(), nums.begin(), nums.end());
                                                    /*
                                                    不知道这样拼接是复制过去，还是直接连接原来
                                                    (是复制过去的，符合vector连续存放的特点)
                                                    */
                                           /*
                                         nums.clear();
                                         nums = hapii;
                                     }
                                     else
                                     {
                                         k = k % nums.size();
                                         if (k == 0)
                                             ;
                                         else
                                         {
                                             vector<int> hapii(nums.begin() + (nums.size() - k), nums.end());
                                             nums.erase(nums.begin() + (nums.size() - k), nums.end());
                                             hapii.insert(hapii.end(), nums.begin(), nums.end());
                                             nums.clear();
                                             nums = hapii;
                                         }
                                     }
                                 }*/
};
// 尝试方法二：看了提示，应该可以原地O(1)，自己想到过1秒，但觉得单次翻转不行，顺序是反的
void Solution::rotate(vector<int> &nums, int k)
{
    k = k % nums.size();
    if (k == 0)
        goto END;
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k); // 左闭右开，因此右边不用 k-1
    reverse(nums.begin() + k, nums.end());
END:;
}
// @lc code=end
