/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] 有效的括号
 */
#include <stack>
#include <string>
using std::string, std::stack;
// @lc code=start
class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> st;
        bool result = true;
        for (auto it = s.begin(); it != s.end(); it++)
        {
            if (result == false)
            {
                break;
            }

            if (*it == '(' || *it == '[' || *it == '{')
            {
                st.push(*it);
            }
            else
            {
                switch (*it)
                {
                case ')':
                    if (!st.empty() && st.top() == '(') // 注意栈为空时，这样调用top是越界
                    //当然，要将判空放前面，因为top放前面，空栈时直接越界先了
                    {
                        st.pop();
                    }
                    else
                    {
                        result = false;
                    }

                    break;
                case ']':
                    if (!st.empty() && st.top() == '[')
                    {
                        st.pop();
                    }
                    else
                        result = false;
                    break;
                case '}':
                    if (!st.empty() && st.top() == '{')
                    {
                        st.pop();
                    }
                    else
                        result = false;
                    break;
                }
            }
        }
        if (!st.empty())
        {
            result = false;
        }

        return result;
    }
};
// @lc code=end
