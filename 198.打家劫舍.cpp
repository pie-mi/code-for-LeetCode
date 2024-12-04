/*
 * @lc app=leetcode.cn id=198 lang=cpp
 *
 * [198] 打家劫舍
 */
#include <vector>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int rob(vector<int>& nums) {
        /*
        注意 1 1 3 1 1 1 1 1 256 257这种，放弃中间连续两个1，可能会更大
        */
        int result = 0;
        if (nums.size() == 1)
        {
            return nums[0];
        }
        if (nums.size() == 2)
        {
            return max(nums[1], nums[0]);
        }
        /*
        //尝试先排序，每选择一个数，则意味着放弃相邻两个数
        vector<int> tosort = nums;
        //或者尝试用数组记录每一位相邻两位的和
        vector<int> sum_of_neighbour;
        sum_of_neighbour.push_back(nums[1]);
        for (int i = 1; i < nums.size()-1; i++)
        {
            sum_of_neighbour.push_back(nums[i - 1] + nums[i + 1]);
        }
        sum_of_neighbour.push_back(nums[nums.size() - 2]);
        while (sum_of_neighbour.size() > 0)
        {
            auto current_maxValue = *max_element(sum_of_neighbour.begin(), sum_of_neighbour.end());
            auto current_max_index = max_element(sum_of_neighbour.begin(), sum_of_neighbour.end());
            result += current_maxValue;
            if(sum_of_neighbour.size() == 1)
                break;
            if ((current_max_index != sum_of_neighbour.begin()) && (current_max_index != (sum_of_neighbour.end()-1)))
            {
                sum_of_neighbour.erase(current_max_index - 1, current_max_index + 2); //[first,last)
            }
            else if (current_max_index == sum_of_neighbour.begin())
            {
                sum_of_neighbour.erase(current_max_index, current_max_index + 2);
            }
            else if (current_max_index == (sum_of_neighbour.end()-1))
            {
                sum_of_neighbour.erase(current_max_index - 1, current_max_index + 1);
            }
            
        }
        */
        
        //看答案后写，其实自己想到只有一二间房子，但想不到如何推出3间房子
        //第k间有两种选择：1.偷--则前k-2间总最大值加第k间  2.不偷--则前k-1间总最大值
        int forward_1, forward_2;
        forward_1 = nums[0];
        forward_2 = 0;
        for (int i = 1; i < nums.size(); i++)
        {
            //forward_1 = nums[i - 1];
            //forward_2 = nums[i - 2];
            result = max(forward_2 + nums[i], forward_1);
            forward_2 = forward_1;
            forward_1 = result;
        }
        
        return result;
    }
};
// @lc code=end

