#include <string>
#include <vector>
#include <stack>
using namespace std;

/*
下方非内联的才是正确的，看了栈的提示才想到
Accepted
919 / 919 testcases passed
52ms Beats81.43%
65.23MB Beats10.13%
*/

class Solution {
public:
    string resultingString(string s) {
        //z与a需要特殊处理，其余只需+/-1
        //题目说至少两个字符才处理
        if(s.length() <2)
            return s;

        bool flag = true;
        do
        {
            flag = dealWithConsecutive(s);
        } while (flag && !s.empty());

        return s;
    }

private:
    //看的英文和翻译，没注意到是每次最左边的“一对”，这里写的逻辑是只要相邻就消
    bool dealWithConsecutive(string& s)
    {
        int left = 0, right = 1;
        //记录s是否有更新，没有更新就是已经没有相邻的了，上面的do-while就退出了
        bool flag = false; 
        //新想法，直接用数组记录相邻相减情况
        vector<int> isConsecutive; //size比s.length少1
        while (right < s.length())
        {
            isConsecutive.emplace_back(s[right] - s[left]);
            left++;
            right++;
        }
        string s_dele;
        for (auto i = 0; i < isConsecutive.size(); i++)
        {
            if (isConsecutive[i] == 1 || isConsecutive[i]==-1||isConsecutive[i]==25 || isConsecutive[i]==-25)
            {
                i++; //跳过两个相邻的，for自带一个++
                continue;
                flag = true;//有更新，可能删了之后拉近带来新的相邻
            }
            else
            {
                s_dele.push_back(s[i]);
            }    
        }
        s_dele.push_back(*s.rbegin());
        s = s_dele;
        return flag;
    }
};

string Solution::resultingString(string s)
{
    // 未结束前没有hint看，结束后看了hint，提到了stack
    // 不然还在想将删除的标记为空格？双指针？还是直接每次耗时的erase

    if (s.length() < 2)
        return s;
    vector<char> react;
    for (auto &c : s)
    {
        //包括一开始栈是空的，也有可能是如aabbc这样前方4个ab消除了的空栈
        if (!react.empty())
        {
            int gap = c - react.back();
            if (gap == 1 || gap == -1 || gap == 25 || gap == -25)
            {
                react.pop_back();
                continue;
            }
            else
                react.push_back(c);
        }
        else
            react.push_back(c);
    }
    string result;
    for (auto &&i : react)
    {
        result.push_back(i);
    }
    return result;
}