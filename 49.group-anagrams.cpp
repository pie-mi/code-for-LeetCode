/*
 * @lc app=leetcode id=49 lang=cpp
 *
 * [49] Group Anagrams
 */
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

/*
Accepted
126/126 cases passed (558 ms)
Your runtime beats 5 % of cpp submissions
Your memory usage beats 5.52 % of cpp submissions (42.2 MB)
*/

// @lc code=start
class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        // 哈希看是否一致，unordered map有相等==操作
        // 空字符串自成一派
        vector<vector<string>> result;
        vector<pair<unordered_map<char, int>, vector<string>>> hashGroup; // 同哈希的放进同一个vector
        // unordered_map再哈希unordered_map，需要有哈希与相等操作，有相等，需要自己写哈希函数
        for (auto &&s : strs)
        {
            // hash
            unordered_map<char, int> hashString;
            for (auto &&c : s)
                hashString[c]++; // unordered_map的int会默认初始化为0，并自增

            // hashGroup一开始为空，下面遍历是不会进去，没办法加入的
            if (hashGroup.empty())
            {
                hashGroup.emplace_back(hashString, vector<string>{s});
                continue;
            }
            // 似乎空字符串会对应空hashString哈希表，也会压进去，不用特殊处理
            bool found = false; // 记录是否有相同组成的已经出现过
            for (auto &&i : hashGroup)
            {
                if (hashString == i.first)
                {
                    i.second.push_back(s);
                    found = true;
                    break;
                }
                // else
                //{ //AI说不要一边遍历一边加入，vector扩容迭代器失效
                //     hashGroup.push_back(make_pair(hashString, vector<string>{s}));
                // }
            }
            if (!found)
            {
                hashGroup.push_back(make_pair(hashString, vector<string>{s}));
            }
        }

        // 分好组的string整理到result
        for (auto &&p : hashGroup)
        {
            result.emplace_back(p.second);
        }
        return result;
    }
};
// @lc code=end
