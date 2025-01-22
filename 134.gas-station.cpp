/*
 * @lc app=leetcode id=134 lang=cpp
 *
 * [134] Gas Station
 */
#include <vector>
#include <numeric>
#include <unordered_map>
using namespace std;
// @lc code=start
class Solution
{
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        /*
        int gasSum, costSum;
        gasSum = accumulate(gas.begin(), gas.end(), 0);
        costSum=accumulate(cost.begin(),cost.end(),0);
        if (gasSum<costSum)
        {
            return -1;
        }
        else
        {
            //就是保证 gas一直大于等于0
            vector<int> gap;
            int min = gas[0] - cost[0];
            int min_index = 0;
            for (int i = 0; i < gas.size(); i++)
            {
                gap.emplace_back(gas[i] - cost[i]);
                if (gap[i]<=min)
                {
                    min_index = i;
                }

            }
            //考虑中间一个耗油量巨大的站，但是如果从其后面一个开始可以顺利走完
            //找到最后一个最大的耗油大于储油的，从后一个正数的开始
            return (min_index + 1) % (gas.size() - 1);
        }
        */
        vector<int> gap;
        int sum = 0;
        int min = gas[0] - cost[0];
        int max = min;
        int min_index = 0;
        int max_index = 0;
        int flag = 1, first_nonnegative_index = 0;
        for (int i = 0; i < gas.size(); i++)
        {
            gap.emplace_back(gas[i] - cost[i]);
            sum += gap[i];
            if (flag && gap[i] >= 0)
            {
                flag = 0;
                first_nonnegative_index = i;
            }          
            min = gap[i] < min ? gap[i] : min;
            max = gap[i] > max ? gap[i] : max;
            min_index = gap[i] <= min ? i : min_index;
            max_index = gap[i] > max ? i : max_index;
        }
        if (sum < 0)
            return -1;
        //bool ishavefuel;
        //将相邻的正数/负数合并
        /*
        vector<int> combine;
        vector<int> positive_start_index;
        bool isTheFirstPostive = true;
        for (auto i = 0; i < gap.size(); i++)
        {
            if (gap[i]>0 && isTheFirstPostive)
            {
                positive_start_index.emplace_back(i);
                isTheFirstPostive = false;
            }
            else if (gap[i]<0)
            {
                isTheFirstPostive = true;
            }
            
        }
        
        int beside_sum = gap[0];
        bool former_sign = gap[0] >= 0 ? true : false;
        for (int i = 1; i < gap.size(); i++)
        {
            if (gap[i]>=0 && former_sign)
            {
                beside_sum += gap[i];
                continue;
            }
            else if (gap[i]<0 && former_sign)
            {
                combine.emplace_back(beside_sum);
                beside_sum=0;
                continue;
            }
            else if (gap[i]>=0 && !former_sign)
            {
                combine.emplace_back(beside_sum);
                beside_sum=0;
                continue;
            }
            else
            {
                beside_sum += gap[i];
            }
        }
        */
        /*
        if ((*combine.begin()>=0 && combine.back()>=0) || (*combine.begin()<0 && combine.back()<0))
        {
            *combine.begin() += combine.back();
            combine.pop_back();
        }
        */
        //因为保证是唯一的，所以可以用负数的吞并正数，应该会剩下的唯一正数

        //直接按顺序加起来就行了，到哪一个为正数，到末尾都是负数则返回-1
        int gapsum = 0;
        int result=-1;
        /*
        for (int count = 0; count < gas.size(); count++)
        {
            static int i = first_nonnegative_index;
            /*if(gap[i] <= 0)
            {
                i++;
                continue;
            }
            //result = i;
            gapsum += gap[i];
            if (gapsum >= 0)
            {
                //result = i;
                continue;
            }
            else
            {
                result = -1;
                gapsum = 0;
            }
            
        }
        return result;
        */
        //看了标签的贪心算法，应该找最大，往左边加入使油量增大的

        //从一个正数gap开始加，要是中途变负，则找下一个正数从头开始
        int i = first_nonnegative_index, j = i;
       
        for (; i < gas.size() && j < gas.size(); j++)
        {
            gapsum += gap[j];
            if (gapsum >= 0)
            {
                result = i;
                continue;
            }
            else
            {
                result = -1;
                gapsum = 0;
                i = j + 1;
            }
            
        }
        return result;
    }
};
// @lc code=end
