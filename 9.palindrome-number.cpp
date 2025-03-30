/*
 * @lc app=leetcode id=9 lang=cpp
 *
 * [9] Palindrome Number
 */
#include <string>
using namespace std;

// 说复试临时机试第一个人是回文数，second就蚁群算法、信息素了

/*
Accepted
11511/11511 cases passed (7 ms)
Your runtime beats 16.24 % of cpp submissions
Your memory usage beats 15.86 % of cpp submissions (10.9 MB)
*/

// @lc code=start
class Solution
{
public:
    bool isPalindrome(int x)
    {
        if (x < 0)
            return false;
        string s = to_string(x);
        int i = 0;
        int j = s.size() - 1;
        while (i < s.size() / 2)
        {
            if (s[i] == s[j])
            {
                i++;
                j--;
                continue;
            }
            else
                return false;
        }
        return true;
    }
};
// @lc code=end
