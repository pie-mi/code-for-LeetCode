#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
通过全部用例 中心拓展法
运行时间3ms
占用内存616KB
通过全部用例 动态规划
运行时间16ms
占用内存22936KB
*/

//知道是最长回文子串，也看到了动态规划的label，但是没有思路
//问AI答案，暴力、中间往两边扩展、动态规划和Manacher算法
//自己想时以为dp[i]表示前方最长回文子串，但没办法想明白
//原来dp[i,j]表示i到j是否为回文，当i=j时，就取决于dp[i+1,j-1]是否为回文，若i与j相差2，即中间夹一个，那必然回文

int dynamicProgm(string passwd)
{
    vector<vector<int>> dp(passwd.size(), vector<int>(passwd.length(), 0));
    for (int i = 0; i < dp.size(); i++)
    {
        dp[i][i] = 1; //对角线表示单个字符自己是回文串        
    }
    
    int result = 1;
    if (passwd.size() < 2)
    {
        return 1;
    }
    // 自己写得不OK，copy AI
    for (int gap = 2; gap <= passwd.size(); gap++)
    {
        for (int i = 0; i <= passwd.size() - gap; i++)
        {
            int j = i + gap - 1;
            if (passwd[i] == passwd[j])
            {
                if (gap == 2 || dp[i+1][j-1])
                {
                    dp[i][j] = 1;
                    //result = j - i > result ? j - i : result;
                    if(gap > result)
                        result = gap;
                        //这里还能记录目前最长回文子串起始位置
                }                
            }
            
        }
        
    }
    return result;
}

//also from AI
int expandBothSide(const string &passwd, int left, int right)
{    
    while (left >= 0 && right < passwd.size() && passwd[left] == passwd[right])
    {
        left--;
        right++;
    }
    return right - left - 1; // 实际回文长度 = (right - left + 1) - 2
}
//奇数中间与偶数两个中间
int max_expandBothSide(string &passwd)
{
    int result = 1;
    for (int i = 0; i < passwd.size(); i++)
    {
        // 处理奇数长度回文（中心为i）
        int len1 = expandBothSide(passwd, i, i);
        // 处理偶数长度回文（中心为i和i+1）
        int len2 = expandBothSide(passwd, i, i + 1);
        int current_max = max(len1, len2);

        // 更新最长回文起始位置和长度
        if (current_max > result) {
            result = current_max;
            //这里还能记录目前最长回文子串起始位置
        }
    }
    return result;
}

int main()
{
    string passwd;
    cin >> passwd;
    int result = 1; //输入至少一个字符，单字符自己一定回文
    result = max_expandBothSide(passwd);
    cout << result << endl;
    return 0;
}