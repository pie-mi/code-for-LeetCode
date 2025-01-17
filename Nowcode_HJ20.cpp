#include <iostream>
#include <type_traits>
#include <unordered_map>
#include <vector>
using namespace std;

bool threeKind(string s)
{
    vector<int> flag(4, 0);
    for (auto i = s.begin(); i != s.end(); ++i)
    {
        if (*i >= '0' && *i <= '9')
        {
            flag[0] = 1;
            continue;
        }
        if (*i >= 'A' && *i <= 'Z')
        {
            flag[1] = 1;
            continue;
        }
        if (*i >= 'a' && *i <= 'z')
        {
            flag[2] = 1;
            continue;
        }
        if (*i >= '!' && *i <= '/')
        {
            flag[3] = 1;
            continue;
        }
        if ((*i >= ':' && *i <= '@') || (*i >= '[' && *i <= '`') || (*i >= '{' && *i <= '~'))
        {
            flag[3] = 1;
            continue;
        }
    }
    int a = 0;
    for (auto ii : flag)
    {
        a += ii;
    }
    return a >= 3 ? true : false;
}

/*woc，在想什么，两个一样的字符串的最长公共子串肯定等于全长啊！
bool LCS(string s)
{
    // 最长公共子串长度大于2则NG
    vector<vector<int>> dp(s.size() + 1, vector<int>(s.size() + 1, 0));
    int LCSlength = 0;
    for (int i = 1; i <= s.size(); ++i)
    {
        for (int j = 1; j <= s.size(); j++)
        {
            if (s[i-1] == s[j-1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                LCSlength = LCSlength < dp[i][j] ? dp[i][j] : LCSlength;
            }
            /*多余，本来整个矩阵就是全部初始化为0
            else
            {
                dp[i][j] = 0;
            }

        }
    }
    return LCSlength > 2 ? true : false;
}
*/

// Nope...刚好看到非的python每日一题，用到了滑动窗口，此处也可设定大小为3的滑动窗口配合哈希
bool slideWindow(string s)
{
    unordered_map<string, bool> exist;
    for (auto i = 0; i + 2 != s.length(); i += 3) // i++不对，如ababa其实是合格的
    {
        string window;
        window.push_back(s[i]);
        window.push_back(s[i + 1]);
        window.push_back(s[i + 2]);
        auto it = exist.find(window);
        if (it == exist.end())
            exist.insert(make_pair(window, true));
        else
            return false;
    }
    return true;
}

bool findduplicate(string s) // 从i+3往后找
{
    for (int i = 0; i + 3 < s.length(); i++)
    {
        string window;
        window.push_back(s[i]);
        window.push_back(s[i + 1]);
        window.push_back(s[i + 2]);
        auto j = s.find(window, i + 3);
        if(j != s.npos)
            return true;
    }
    return false;
}

int main()
{
    vector<string> psw;
    string p;
    vector<string> answer;
    const string NG("NG");
    const string OK("OK");
    while (cin >> p)
    { // 注意 while 处理多个 case
        psw.push_back(p);
    }
    for (auto i = psw.begin(); i != psw.end(); i++)
    {
        if ((*i).length() < 8 || !threeKind(*i) || findduplicate(*i))
        {
            answer.push_back(NG);
            continue;
        }
        else
            answer.push_back(OK);
    }
    for (auto i : answer)
    {
        cout << i << endl;
    }

    return 0;
}
// 64 位输出请用 printf("%lld")