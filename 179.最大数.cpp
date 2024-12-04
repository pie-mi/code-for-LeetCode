/*
 * @lc app=leetcode.cn id=179 lang=cpp
 *
 * [179] 最大数
 */
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
// @lc code=start

// 前缀相同，长的那个数多出来的第一个数字和前缀第一个数字比较 3451_345<3453451
// 前缀相同，第一个不同的就正常string比较 3451 3452
/*
bool cmp(string a, string b)
{
    // int difflength = abs(a.length() - b.length());
    if (a.length() < b.length() && a == b.substr(0, a.length()))
    {
        return a[0] < b[a.length()];
    }
    else if (a.length() > b.length() && a.substr(0, b.length()) == b)
    {
        return a[b.length()] > a[0];
    }

    else
        return a > b;
}
*/

  /*432,43243   my:43243243   true:43243432*/ 
//看到这个例子，仔细看了很久，发现是将前缀相同之处忽略，直接用前缀比较长出来那一部分，即432与43243的43比
//而432与43比，相当于递归样式，又是前缀相同嘛，拿凸出来的2与首位4对比

//发现挺蒙的，用计算器减一下，忽然想到，直接这么减一下不就行了吗，让计算机像我一样操作
//就是将string拼在一起，相减(直接string比较即可)/(当然用stringstream转回int也行，更直观)，看大小即可
bool cmp2(string a,string b)
{
    string ab = a + b;
    string ba = b + a;
    return ab > ba;
}


class Solution
{
public:
    string largestNumber(vector<int> &nums)
    {
        // 可以用stringstream kuci; kuci << nums[i] 转换为字符串
        // 也可用to_string(n)
        string result;
        vector<string> string_nums;
        for (int i = 0; i < nums.size(); i++)
        {
            string_nums.emplace_back(to_string(nums[i]));
        }
        // sort(string_nums.begin(), string_nums.end(), greater<string>());
        sort(string_nums.begin(), string_nums.end(), cmp2);
        for (auto it = string_nums.begin(); it != string_nums.end(); it++)
        {
            result = result + *it;
        }
        //处理[0,0]这种情况，避免输出"00"
        stringstream bozi;
        int kuci;
        bozi << result;
        bozi >> kuci;
        if (kuci==0)
        {
            result = "0";
        }
        
        return result;
    }
};
// @lc code=end
