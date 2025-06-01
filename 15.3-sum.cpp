/*
 * @lc app=leetcode id=15 lang=cpp
 *
 * [15] 3Sum
 */
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
using namespace std;

/*
Time Limit Exceeded
310/314 cases passed (N/A)
Accepted
314 / 314 testcases passed
170ms Beats20.38%
44.64MB Beats17.19%
*/

// @lc code=start
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> result;
        // sort(nums.begin(), nums.end());
        //  给我来了几千个0，即使用哈希一个个比都超时，出现超过三次的去重掉
        nums = sortAndDeduplicate(nums);

        // 保证不重复，标准库没有对vector的hash，需要自己手动重载运算符实现
        // unordered_set<vector<int>> exist;
        // 用set吧，每个vector都要自己先排序，不然会视为不同的vector
        set<vector<int>> exist;
        for (auto i = 0; i < nums.size() - 2; i++)
        {
            if (nums[i] > 0)
            {
                // 已经排序了，如果最左边的i都为正数，右边肯定都是正数，加起来不会小于0
                break;
            }

            for (auto j = i + 1; j < nums.size() - 1; j++)
            {
                if (nums[i] + nums[j] >= 0 && nums[j] > 0)
                {
                    break;
                }

                for (auto k = j + 1; k < nums.size(); k++)
                {
                    if (nums[i] + nums[j] + nums[k] == 0)
                    {
                        vector<int> current{nums[i], nums[j], nums[k]};
                        sort(current.begin(), current.end());
                        if (exist.count(current) == 0)
                        {
                            result.emplace_back(current);
                            exist.emplace(current);
                        }
                        // 已经排序了，后面加起来肯定只会更大，即使一致也是重复
                        break;
                    }
                    else if (nums[i] + nums[j] + nums[k] > 0)
                    {
                        break;
                    }
                }
            }
        }

        // nums[i]+nums[j] = -nums[k]，用哈希找是否存在这个nums[k]
        unordered_multimap<int, int> complement;
        for (int i = 0; i < nums.size(); i++)
        {
            complement.insert({nums[i], i}); // nums已排序
            // 或者complement.emplace(make_pair(nums[i],i)) emplace是用参数构造，直接大括号报错
        }
        for (int i = 0; i < nums.size() - 2; i++)
        {
            if (nums[i] > 0)
            {
                break;
            }
            for (auto j = i + 1; j < nums.size() - 1; j++)
            {
                if (nums[i] + nums[j] > 0) // sorted，前两者之和都已经大于0，后面只会更大
                    break;
                auto target = -nums[i] - nums[j];
                auto k_range = complement.equal_range(target);
                for (auto it = k_range.first; it != k_range.second; it++)
                {
                    // 避免重复i=k=j，如-1、-1、2，这两个-1不能是同一个，甚至于3个0
                    // 其实nums已经排序了，i、j是在前的，k是三者最大的了，所以找的k是正数或0，
                    // 因为若是nums[k]仍为负，则不可能加起来得0
                    // nums[i]肯定≤0，nums[j]可正可负，但若前两者之和大于0，则nums[k]必为正，无可能加起来等于0
                    if (it->second != i && it->second != j)
                    {
                        vector<int> temp{nums[i], nums[j], it->first}; // 感觉写target更清晰
                        sort(temp.begin(), temp.end());
                        if (exist.count(temp) == 0)
                        {
                            result.emplace_back(temp);
                            exist.emplace(temp);
                        }
                        break;
                    }
                }
            }
        }

        return result;
    }

private:
    // Deepseek 超过三次去重
    vector<int> sortAndDeduplicate(vector<int> &nums)
    {
        // 1. 排序
        sort(nums.begin(), nums.end());

        vector<int> result;
        auto it = nums.begin();

        // 2. 遍历统计并保留元素
        while (it != nums.end())
        {
            int current = *it;
            int count = 0;

            // 统计当前元素的连续出现次数
            while (it != nums.end() && *it == current)
            {
                ++count;
                ++it;
            }

            // 保留最多3个元素
            int add = min(count, 3);
            result.insert(result.end(), add, current);
        }

        return result;
    }

    // 豆包，参数加个引用
    std::vector<int> sortAndDeduplicate_doubao(std::vector<int> &vec)
    {
        // 先对vector进行排序
        std::sort(vec.begin(), vec.end());
        std::unordered_map<int, int> countMap;
        std::vector<int> result;

        // 统计每个元素的出现次数
        for (int num : vec)
        {
            countMap[num]++;
        }

        // 根据统计结果添加元素到结果向量
        for (int num : vec)
        {
            if (countMap[num] <= 3)
            {
                result.push_back(num);
            }
            else if (countMap[num] > 3)
            {
                if (std::count(result.begin(), result.end(), num) < 3)
                {
                    result.push_back(num);
                }
            }
        }

        return result;
    }
};
// @lc code=end
