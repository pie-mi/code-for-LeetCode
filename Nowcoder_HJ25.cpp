#include <iostream>
#include <vector>
#include <string>
#include <set>
/*
通过全部用例
运行时间3ms
占用内存588KB
*/

using namespace std;
// 有想过用正则表达式匹配，用regex库，因为不是最长公共子串，不需要动态规划
// 当然KMP也是类似但没有库，但是问AI之后说用string的find就OK

int main()
{
    int n, m;
    cin >> n;
    vector<int> dataset(n);
    for (int i = 0; i < n; i++)
    {
        cin >> dataset[i];
    }
    cin >> m;
    set<int> ruleset;
    auto m_temp = m;
    while (m_temp-- > 0)
    {
        int temp;
        cin >> temp;
        ruleset.insert(temp);
    }
    vector<string> dataset_string;
    for (auto item : dataset)
    {
        dataset_string.push_back(to_string(item));
    }
    vector<string> ruleset_string;
    for (const auto &item : ruleset)
        ruleset_string.push_back(to_string(item));
    // AI，set转为vector方便随机访问
    vector<int> ruleset_vector(ruleset.begin(), ruleset.end());

    auto count = 0;
    vector<vector<int>> mark_matrix(ruleset.size() , vector<int>(n + 1, 0)); // uniq(m)*(n+1) 多一列记录这一行规则有多少匹配
    for (auto i = 0; i < ruleset_string.size(); i++)
    {
        for (auto j = 0; j < n; j++)
        {
            if (dataset_string[j].find(ruleset_string[i]) != string::npos) //这里越界了，ruleset_string的size去重后通常小于m，牛客的没开越界检测不会报错，本地会报段错误
            {
                // 不能在这里就打印输出，因为统计总数的要在开头，只能先存着了
                mark_matrix[i][j] = 1;
                mark_matrix[i][n]++;
                count += 2; // 下标和数本身，规则不能在这里加1，不然重复加了
            }
        }
    }

    for (auto i = 0; i < ruleset.size(); i++)
    {
        for (auto j = 0; j < n; j++)
        {
            if (mark_matrix[i][j] == 1)
            {
                count++; // 加上有匹配的规则数
                count++; //加上“符合规则的条数”这个数
                break;
            }
        }
    }

    cout << count << ' ';
    for (auto i = 0; i < ruleset.size(); i++)
    {
        if (mark_matrix[i][n]) //规则有匹配
        {
            cout << ruleset_vector[i] << ' ' << mark_matrix[i][n] << ' '; // set的iterator不能 *(ruleset.begin() + i)
            for (auto j = 0; j < n; j++)
            {
                if (mark_matrix[i][j] == 1)
                {
                    cout << j << ' ' << dataset[j] << ' ';
                }
            }
        }
    }
    return 0;
}