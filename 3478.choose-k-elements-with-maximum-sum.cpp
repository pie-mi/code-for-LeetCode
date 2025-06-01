#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

/*
Time Limit Exceeded
624 / 635 testcases passed
看了提示思路完全一样，优化就是想到不要每次重新建堆，用一个变量sum记录上一个即可
还不够k个元素就直接加起来，就是上一个sum加一个；
超过k且当前元素大于小根堆的堆顶，就sum减堆顶，再加上当前元素，再插入堆中
后面处理连续相等的情况混乱了两天，主要分清有更大的始终更新sum，以便未来能用堆来获取前方最大k个之和，
但相等的本身是等于前一个，因为小于其的下标没有变化，无任何元素加入
Accepted
635 / 635 testcases passed
61ms Beats97.11%
178.95MB Beats50.35%
*/

class Solution
{
public:
    vector<long long> findMaxSum(vector<int> &nums1, vector<int> &nums2, int k)
    {
        vector<long long> result(nums1.size(), 0);
        // vector<pair<int, int>> bond;
        // for (auto i = 0; i < nums1.size(); i++)
        //     bond.emplace_back(nums1[i], nums2[i]);

        // 要按顺序输出，不太能将bond直接排序，排完损失了下标信息，改为绑定下标
        vector<pair<int, int>> nums1_with_index;
        for (auto i = 0; i < nums1.size(); i++)
        {
            nums1_with_index.emplace_back(nums1[i], i);
        }
        sort(nums1_with_index.begin(), nums1_with_index.end());

        // 最小的元素排第一，不会有其它更小的，对应的和就是0，从下标1开始
        for (auto i = 1; i < nums1_with_index.size(); i++)
        {
            // 小根堆，插入，已经有k个就比较堆顶，堆顶比较小就pop走堆顶，再插入
            priority_queue<int, vector<int>, greater<int>> heap;
            for (auto j = 0; j < i && nums1_with_index[j].first < nums1_with_index[i].first; j++) // case2 全是2相等
            {
                // AI 且不是<=，否则已经够k个了还push一个
                if (heap.size() < k)
                {
                    heap.push(nums2[nums1_with_index[j].second]);
                }
                else if (nums2[nums1_with_index[j].second] > heap.top())
                {
                    heap.pop();
                    heap.push(nums2[nums1_with_index[j].second]);
                }
            }
            // 将堆求和
            long long sum = 0;
            while (!heap.empty())
            {
                sum += heap.top();
                heap.pop();
            }
            result[nums1_with_index[i].second] = sum;
        }
        return result;
    }
    vector<long long> findMaxSum_Optimize(vector<int> &nums1, vector<int> &nums2, int k);
};

vector<long long> Solution::findMaxSum_Optimize(vector<int> &nums1, vector<int> &nums2, int k)
{
    vector<long long> result(nums1.size(), 0);
    // vector<pair<int, int>> bond;
    // for (auto i = 0; i < nums1.size(); i++)
    //     bond.emplace_back(nums1[i], nums2[i]);

    // 要按顺序输出，不太能将bond直接排序，排完损失了下标信息，改为绑定下标
    vector<pair<int, int>> nums1_with_index;
    for (auto i = 0; i < nums1.size(); i++)
    {
        nums1_with_index.emplace_back(nums1[i], i);
    }
    sort(nums1_with_index.begin(), nums1_with_index.end());

    // 小根堆，插入，已经有k个就比较堆顶，堆顶比较小就pop走堆顶，再插入
    priority_queue<int, vector<int>, greater<int>> heap;
    // heap.push(nums2[nums1_with_index[0].second]); //第一个最小，肯定进堆
    long long sum = 0; // heap.top();

    // 最小的元素排第一，不会有其它更小的，对应的和就是0，从下标1开始
    for (auto i = 1; i < nums1_with_index.size(); i++)
    {
        // 不要每次重新建堆，超时
        // priority_queue<int, vector<int>, greater<int>> heap;
        if (heap.size() < k) // 压入这一个够k个了，堆就满了刚好
        {
            if (nums1_with_index[i - 1].first < nums1_with_index[i].first) // case2 全是2相等
            {
                heap.push(nums2[nums1_with_index[i - 1].second]);
                sum += nums2[nums1_with_index[i - 1].second]; // 不是heap.top()，不一定刚压进去的就是最小的
                result[nums1_with_index[i].second] = sum;
                continue;
            }
            else
            {
                // 还是要压入堆的，因为前面全是2，后面跟一个3，那3应该取前面2对应的前k个值之和
                heap.push(nums2[nums1_with_index[i - 1].second]);
                sum += nums2[nums1_with_index[i - 1].second];
                result[nums1_with_index[i].second] = result[nums1_with_index[i - 1].second];
                continue;
            }
        }
        // else
        if (heap.empty())
            break; // 只要有不相等的都不会为空，全相等（包括只有一个元素）就返回全0result即可
        auto j = i - 1;
        if (nums1_with_index[i - 1].first < nums1_with_index[i].first)
        {
            if (nums2[nums1_with_index[j].second] > heap.top())
            {
                // 新进的更大，舍弃之前k个中最小的，新的加入最大的k个之一
                sum -= heap.top();
                heap.pop();
                heap.push(nums2[nums1_with_index[j].second]);
                sum += nums2[nums1_with_index[j].second];
                result[nums1_with_index[i].second] = sum;
            }
            else
            {
                // 新进的小，不是前k个，直接等于之前的即可
                result[nums1_with_index[i].second] = sum;
            }
        }
        else if (nums1_with_index[i - 1].first == nums1_with_index[i].first)
        {
            if (nums2[nums1_with_index[j].second] > heap.top())
            {
                // 不满足前一个条件，即这几个是相等的，如连续的2，那小于2的下标都一样，和前者一样即可
                result[nums1_with_index[i].second] = result[nums1_with_index[i - 1].second];
                // 但满足第二个条件，这里也要更新sum！虽然都是2，但对应下标的nums2不一定一样，这个2对应的是更大的
                sum -= heap.top();
                heap.pop();
                heap.push(nums2[nums1_with_index[j].second]);
                sum += nums2[nums1_with_index[j].second];
            }
            else
                // 连续的2，和前者一样即可，且堆已经满k个了，这个2对应下标的nums2更小，sum不用变
                result[nums1_with_index[i].second] = result[nums1_with_index[i - 1].second];
        }
    }
    return result;
}

int main()
{
    vector<int> nums1{4, 2, 1, 5, 3};
    vector<int> nums2{10, 20, 30, 40, 50};
    Solution test;
    auto result1 = test.findMaxSum_Optimize(nums1, nums2, 2);
    for (auto &&i : result1)
    {
        cout << i << ' ';
    }
    cout << endl;
    vector<int> nums3{2, 2, 2, 2};
    vector<int> nums4{3, 1, 2, 3};
    auto result2 = test.findMaxSum_Optimize(nums3, nums4, 1);
    for (auto &&i : result2)
    {
        cout << i << ' ';
    }
    vector<int> nums5{2, 2, 3};
    vector<int> nums6{3, 1, 7};
    auto result3 = test.findMaxSum_Optimize(nums5, nums6, 1);
    for (auto &&i : result3)
    {
        cout << i << ' ';
    }
    return 0;
}