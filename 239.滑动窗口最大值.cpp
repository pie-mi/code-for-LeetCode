/*
 * @lc app=leetcode.cn id=239 lang=cpp
 *
 * [239] 滑动窗口最大值
 */
#include <deque>
#include <queue>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
protected:
    pair<int, int> max_in_window(deque<int> &window)
    {
        deque<int> contain = window;
        int max = contain.front();
        int i = -1;
        while (!contain.empty())
        {
            if (max <= contain.front())
            {
                max = contain.front();
                i++;
            }
            contain.pop_front();
        }
        return make_pair(max, i);
    }

public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k);
    /*
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        vector<int> maxinslidewindow;
        deque<int> window; // 提示用deque，标签还有堆heap
        //<algorithm>里的make_heap() push_heap() pop_heap() sort_heap()对vector来使用
        // STL的<queue>提供了priority_queue
        priority_queue<pair<int, int>> heap_window;
        pair<int, int> howlongbecomethebiggest;
        howlongbecomethebiggest.first = nums[0];
        howlongbecomethebiggest.second = 0;
        for (int i = 0; i < k; i++)
        {
            window.push_back(nums[i]);
            // 会先根据first来排序，相等的再根据second来排序
            heap_window.push(make_pair(nums[i],i));
            if (nums[i] >= howlongbecomethebiggest.first) // 同为最大值，后面出现的效果持久一些
            {
                howlongbecomethebiggest.first = nums[i];
                howlongbecomethebiggest.second = i; // 剩余有效期，小于0则表示已经移出窗口，失效
            }
        }
        maxinslidewindow.push_back(howlongbecomethebiggest.first);

        for (auto it = nums.begin() + k; it != nums.end(); it++)
        {
            if (*it < howlongbecomethebiggest.first && howlongbecomethebiggest.second > 0)
            {
                window.pop_front();
                window.push_back(*it);
                // maxinslidewindow.push_back(howlongbecomethebiggest.first);
                howlongbecomethebiggest.second--;
                // continue;
            }
            else if (*it > howlongbecomethebiggest.first)
            {
                window.pop_front();
                window.push_back(*it);
                howlongbecomethebiggest.first = *it;
                howlongbecomethebiggest.second = k - 1;
            }
            else
            {
                window.pop_front();
                window.push_back(*it);
                howlongbecomethebiggest = max_in_window(window);
            }
            maxinslidewindow.push_back(howlongbecomethebiggest.first);
        }
        return maxinslidewindow;
    }*/
};

vector<int> Solution::maxSlidingWindow(vector<int> &nums, int k)
{
    vector<int> result_maxinslidewindow;
    // deque<int> window; // 提示用deque，标签还有堆heap
    //<algorithm>里的make_heap() push_heap() pop_heap() sort_heap()对vector来使用
    //  STL的<queue>提供了priority_queue
    priority_queue<pair<int, int>> heap_window;
    pair<int, int> howlongbecomethebiggest;
    howlongbecomethebiggest.first = nums[0];
    howlongbecomethebiggest.second = 0;
    for (int i = 0; i < k; i++)
    {
        // window.push_back(nums[i]);
        //  会先根据first来排序，相等的再根据second来排序
        heap_window.push(make_pair(nums[i], i));
        if (nums[i] >= howlongbecomethebiggest.first) // 同为最大值，后面出现的效果持久一些
        {
            howlongbecomethebiggest.first = nums[i];
            howlongbecomethebiggest.second = i; // 剩余有效期，小于0则表示已经移出窗口，失效
        }
    }
    result_maxinslidewindow.push_back(heap_window.top().first);
    //heap_window.pop(); 堆顶这个可能还会在有效期内呢
    for (int i = k; i < nums.size(); i++) // auto it = nums.begin() + k; it != nums.end(); it++
    {
        // 前k个处理好后，只要遇见比堆顶大的，直接清空堆，肯定是大佬
        // 小的就加入堆，难点在于如何更新确保有效期内，靠堆大小判断好像不可行，除了堆顶又不能每次取出来更新再放回，不然就没有提升效率
        // 不用太复杂，只需要配对压入是第几个(即下标-1)，从堆中取出时，判断第i个减去窗口长度k，看是否大于，是则在窗口内，有效
        heap_window.push(make_pair(nums[i], i));
        if (i - k < heap_window.top().second)
        {
            result_maxinslidewindow.push_back(heap_window.top().first);
            //heap_window.pop(); 堆顶这个可能还会在有效期内呢
        }
        else
        {
            while (i - k >= heap_window.top().second)
            {
                heap_window.pop();
            }
            result_maxinslidewindow.push_back(heap_window.top().first);
            //heap_window.pop();
        }
    }
    return result_maxinslidewindow;
}
// @lc code=end
