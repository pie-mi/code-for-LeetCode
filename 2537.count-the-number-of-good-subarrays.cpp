/*
 * @lc app=leetcode id=2537 lang=cpp
 *
 * [2537] Count the Number of Good Subarrays
 */
#include <vector>
#include <unordered_map>
#include <cmath>
#include <iostream>
using namespace std;

/*
Time Limit Exceeded
32 / 41 testcases passed

Accepted
41 / 41 testcases passed
86ms Beats26.48%
81.58MB Beats7.85%
*/

// @lc code=start
class Solution
{
public:
    long long countGood(vector<int> &nums, int k);
    long long countGood_timeLimit(vector<int> &nums, int k)
    {
        // 滑动窗口并结合哈希，方便判断是否存在以及删除/添加窗口外的元素
        // 例子1说明子数组长度L至少是C(L,2)>=k，展开解方程取整
        // 例子2说明每个长度的子数组都可能满足，要遍历
        // 就是要求子数组内至少有k对相等元素，找出符合的子数组个数
        long long good = 0;
        int minLength = ceil((1 + sqrt(1 + 8 * k)) / 2);
        auto windowLength = minLength; // 加个&取别名?
        if (minLength > nums.size())
            return 0; // 整个数组都找不够k对元素，如找size为1的数组不可能找出1对元素

        // 应该可以优化，每种长度窗口每次开始都要初始化塞windowsLength进去，O(minLength+(minLength+1)+...+nums.size)
        // 其实就是比上一个窗口大小增加1，记录一下第一个，加一个就初始化好了下一个，O(minLength+1+1+...+1)
        // 进一步，滑到第二个窗口也是比小1的第二个窗口多一个，要不要记录所有窗口呢，NO
        // 代码已经写了，就是从第一个右移一个就得到了，O(1)
        // 连vector<pair<int, int>> recordFirst;都不用，一个变量就够了，记录上一个
        long long record = 0; // 记录窗口内相等的对数，int应该不够，题目nums最大10^5，即使k是1，
                              // 结果是L=2的子数组有十万-1个，L=3的十万-2个，十万个的等差数列：(十万-1)+(十万-2)+...+2+1
                              // 最多的窗口内相等的对数就是L=十万，C(十万,2)=4,999,950,000
                              // 总体子数组就4,999,950,000个了，超过int的范围

        unordered_map<int, int> recordFirst; // 最多十万个，全相等int也够了
        for (auto i = 0; i < windowLength; i++)
        {
            recordFirst[nums[i]]++;
            // 不能在这里一起计算有多少对相等，因为计算是用组合数，每加一个都变化很大，不到末尾不知道有多少个
        }
        for (auto &&elem : recordFirst)
        {
            if (elem.second >= 2)
            {
                // 是C(n,2) 如三个相等的数，则3对
                record += elem.second * (elem.second - 1) / 2;
            }
        }
        if (record >= k)
            good++;

        while (windowLength <= nums.size()) // 内部还要用到windowinLength，先不++
        {
            if (windowLength - minLength) // 首个窗口除外，不用加入下一个
            {
                recordFirst[nums[windowLength - 1]]++; // 其实就是比上一个窗口大小增加1，因为第一round自增了，第二round应该加入的就是-1
                if (recordFirst[nums[windowLength - 1]] >= 2)
                {
                    record += recordFirst[nums[windowLength - 1]] - 1; // C(n+1,2)-C(n,2)=n
                }
                //完成了新长度窗口的初始化，也要判断是否“好数组”
                if (record >= k)
                    good++;
            }
            unordered_map<int, int> elem_in_win(recordFirst);
            auto countEqual = record;
            // 首个窗口已塞好，从窗口后一个下标开始
            auto i = 0;
            auto j = windowLength;
            while (j < nums.size())
            {
                // 最前面的i滑出窗口，新的j滑入窗口
                //  i滑出了，减少1个，C(n,2)-C((n-1),2)=n-1
                countEqual = countEqual - (elem_in_win[nums[i]] - 1);
                elem_in_win[nums[i]]--;
                elem_in_win[nums[j]]++;

                if (elem_in_win[nums[j]] >= 2)
                {
                    // 如三个相等的数，则原来是两个，只有1对，现在变为3对，增加2对，这个是增加的C(n+1,2)-C(n,2)=n
                    countEqual += elem_in_win[nums[j]] - 1; // elem_in_win[nums[j]] * (elem_in_win[nums[j]] - 1) / 2;
                }
                if (countEqual >= k)
                    good++;
                i++;
                j++;
            }
            windowLength++;
        }

        return good;
    }

private:
    int find_until(vector<int> &nums, unordered_map<int,int> &elem_in_win, int k, int index, int currLength, int &count)
    {
        auto i = index + currLength;
        while (count < k)
        {
            elem_in_win[i]++;
        }
        
    }
};
// @lc code=end

long long Solution::countGood(vector<int> &nums, int k)
{
    //超时需要再次优化，当下标i这里开始winLength已经满足“好”，那后面加长肯定只会更好，直到nums.end
    //用哈希表记录每个下标需要的最小窗口长度
    //之前是每个窗口长度去滑各个元素，现在反过来想每个元素滑出自己最小窗口长度，其实case2就是这个思路
    //超时的用例是5万个元素，前面的应该唯一，最后一段一万个同一元素
    //k=1，第一个元素滑到窗口为4才满足，第二个元素窗口至少从3开始，第三个元素 0 0 1 1 1
    //有没有可能后缀->后缀树?
    long long good = 0;
    int minLength = ceil((1 + sqrt(1 + 8LL * k)) / 2); // 题目的k到10^9，int表示不了，来个了runtime error，
                                                    // 若minLength改为long long后边的max又没有int与long long的重载，问AI后，平方根用long long，用static_cast或者后面加LL
    if (minLength > nums.size()) //整个nums都不可能凑出这么多对元素
        return 0;
   
    vector<int> each_window(nums.size(), 0); // 记录每个下标对应的满足“好”的最小窗口长度 //给个最小值避免下面首次调用back越界
    unordered_map<int, int> elem_in_win; // 最多十万个，全相等int也够了
    auto count = 0;
    for (auto i = 0; i < minLength && i < nums.size(); i++) //case 39，nums只有一个元素63，k是93，最小窗口长度15，不能认为最小窗口一定比nums小
    {
        elem_in_win[nums[i]]++;
        // 不能在这里一起计算有多少对相等，因为计算是用组合数，每加一个都变化很大，不到末尾不知道有多少个
    }
    for (auto &&elem : elem_in_win)
    {
        if (elem.second >= 2)
        {
            // 是C(n,2) 如三个相等的数，则3对
            count += elem.second * (elem.second - 1) / 2;
        }
    }
    if (count >= k)
        each_window[0] = minLength;
    else
    {
        auto i = minLength;
        for (; count < k && i < nums.size(); i++) //找到第一个窗口的“好”最小窗口长度
        {
            elem_in_win[nums[i]]++;
            if (elem_in_win[nums[i]] >= 2)
            {
                // 如三个相等的数，则原来是两个，只有1对，现在变为3对，增加2对，这个是增加的C(n+1,2)-C(n,2)=n
                count += elem_in_win[nums[i]] - 1; // elem_in_win[nums[j]] * (elem_in_win[nums[j]] - 1) / 2;
            }
        }
        if(count >= k) //是满足了k对退出的循环
            each_window[0] = i; // 不用i+1，因为record满足了还会i++才比较才不循环
        else //到末尾而退出循环，即整个nums从头到尾找不到k对，没有“好”子数组
            return 0;
    }

    for (auto i = 1; i <= nums.size() - minLength; i++)
    {
        if (each_window[i - 1] == 0) //前一个会一直找到尽头，都找不到窗口来达到“好”，这里还比前一个少一个元素，往后不可能找得到
            break;
        auto currLength = max(each_window[i - 1] - 1, minLength);
        if (currLength == each_window[i - 1] - 1)
        {
            //  i-1滑出了，减少1个，C(n,2)-C((n-1),2)=n-1
            count = count - (elem_in_win[nums[i - 1]] - 1);
            elem_in_win[nums[i - 1]]--;
        }
        else
        {
            //前一个就是最小窗口，这个也要是，不仅弹走前一个，也要压入后一个
            count = count - (elem_in_win[nums[i - 1]] - 1);
            elem_in_win[nums[i - 1]]--;
            elem_in_win[nums[i + minLength - 1]]++;
            if (elem_in_win[nums[i + minLength - 1]] >= 2)
                count += elem_in_win[nums[i + minLength - 1]] - 1;
        }       

        if (count >= k)
        {
            each_window[i] = currLength; // each_window.emplace_back(currLength);
            continue;
        }
        else
        {
            // auto thisLength=find_until
            // if (i + currLength - 1 >= nums.size())

            while (count < k && i - 1 + currLength < nums.size()) //例如全是自然数按顺序的，根本没有重复数字，currlength加到无穷都不退出，越界就退出了
            {
                currLength++;
                auto index = i - 1 + currLength;
                if (index < nums.size()) //因为进入while时窗口刚好到最后元素了，不够对数就先扩大窗口，可能已经越界了，如case2
                {
                    elem_in_win[nums[index]]++;
                    if (elem_in_win[nums[index]] >= 2)
                    {
                        // 如三个相等的数，则原来是两个，只有1对，现在变为3对，增加2对，这个是增加的C(n+1,2)-C(n,2)=n
                        count += elem_in_win[nums[index]] - 1;
                    }
                }
                else
                {
                    //进入时就是窗口到最后了，扩大窗口已越界
                    break;
                }
                
            }
            if(count >= k) //免得越界退出的也写入
                each_window[i] = currLength;
        }
    }
    
    //根据每个下标的最小窗口长度统计子数组数量
    for (auto i = 0; i < each_window.size(); i++)
    {
        if(each_window[i] >= 2) //因为成对的，长度至少为2，初始化为0没变的就是没找到最小窗口
            good += nums.size() - i - each_window[i] + 1; // (i,length-1),...,size-1 是length-1到size-1，即(size-1) - (i+length-1) +1
    }
    return good;
}

// 未优化版
/*经过了修改，应该能通过更多，但效率肯定比不上优化的，优化的都超时
Wrong Answer
2 / 41 testcases passed
*/
long long countGood_unOptimize(vector<int> &nums, int k)
{
    auto minLength = ceil((1 + sqrt(1 + 8 * k)) / 2);
    auto windowLength = minLength; // 加个&取别名?
    long long good = 0;
    if (minLength > nums.size())
        return 0; // 整个数组都找不够k对元素，如找size为1的数组不可能找出1对元素

    // 应该可以优化，每种长度窗口每次开始都要初始化塞windowsLength进去，O(minLength+(minLength+1)+...+nums.size)
    // 其实就是比上一个窗口大小增加1，记录一下第一个，加一个就初始化好了下一个，O(minLength+1+1+...+1)
    // 进一步，滑到第二个窗口也是比小1的第二个窗口多一个，要不要记录所有窗口呢，NO
    // 代码已经写了，就是从第一个右移一个就得到了，O(1)
    // 连vector<pair<int, int>> recordFirst;都不用，一个变量就够了，记录上一个

    while (windowLength <= nums.size()) // 内部还要用到windowinLength，先不++
    {
        unordered_map<int, int> elem_in_win; // 最多十万个，全相等int也够了
        long long countEqual = 0;            // 记录窗口内相等的对数，int应该不够，题目nums最大10^5，即使k是1，
        // 结果是L=2的子数组有十万-1个，L=3的十万-2个，十万个的等差数列：(十万-1)+(十万-2)+...+2+1
        // 最多的窗口内相等的对数就是L=十万，C(十万,2)=4,999,950,000
        // 总体子数组就4,999,950,000个了，超过int的范围
        for (auto i = 0; i < windowLength; i++)
        {
            elem_in_win[nums[i]]++;
            // 不能在这里一起计算有多少对相等，因为计算是用组合数，每加一个都变化很大，不到末尾不知道有多少个
        }
        for (auto &&elem : elem_in_win)
        {
            if (elem.second >= 2)
            {
                // 是C(n,2) 如三个相等的数，则3对
                countEqual += elem.second * (elem.second - 1) / 2;
            }
        }
        if (countEqual >= k)
            good++;
        // 首个窗口已塞好，从窗口后一个下标开始
        auto i = 0;
        auto j = windowLength;
        while (j < nums.size())
        {
            // 最前面的i滑出窗口，新的j滑入窗口
            //  i滑出了，减少1个，C(n,2)-C((n-1),2)=n-1
            countEqual = countEqual - (elem_in_win[nums[i]] - 1);
            elem_in_win[nums[i]]--;
            elem_in_win[nums[j]]++;

            if (elem_in_win[nums[j]] >= 2)
            {
                // 是C(n,2) 如三个相等的数，则3对，这个是增加的C(n+1,2)-C(n,2)=n
                countEqual += elem_in_win[nums[j]] - 1; // elem_in_win[nums[j]] * (elem_in_win[nums[j]] - 1) / 2;
            }
            if (countEqual >= k)
                good++;
            i++;
            j++;
        }

        windowLength++;
    }

    return good;
}

int main()
{
    Solution test;
    vector<int> nums1{1, 1, 1, 1, 1};
    vector<int> nums2{3, 1, 4, 3, 2, 2, 4};
    vector<int> nums3{2, 3, 3, 3, 3, 1, 3, 1, 3, 2};
    auto good1 = test.countGood(nums1, 10); // 1
    auto good2 = test.countGood(nums2, 2);  // 4 但得2、5
    auto good3 = test.countGood(nums3, 19); // 0
    cout << good1 << endl
         << good2 << endl
         << good3 << endl;
}