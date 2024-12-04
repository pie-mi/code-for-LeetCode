#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

bool cmp(pair<int, string> s1, pair<int, string> s2) //这里不能用引用 &s1，不知道为什么
{
    return s1.first > s2.first;
}

/*
bool operator > (pair<int,string> &s1,pair<int,string> &s2)
{
    return s1.first > s2.first;
}
*/
int main()
{
    // 可以利用sort对pair排序，默认根据first，需要second则自己写函数作为sort第三个参数
    string con;
    // cin >> con;
    while (cin >> con)
    {
        vector<pair<int, string>> timesandcontant;
        //vector<int> times;
        //unordered_map<int, string> match;
        for (auto i = 0; i < con.size(); i++)
        {
            if ('0' <= con[i] && con[i] <= '9')
            {
                auto j = i;
                for (; j < con.size(); j++)
                {
                    if ('0' <= con[j] && con[j] <= '9')
                    {
                        continue;
                    }
                    else
                    {
                        // i = j;不可以这么快修改i
                        break;
                    }
                }
                string cut = con.substr(i, j - i); // j已自增为下一个，substr第二个参数就是截取长度，而i是需要的
                timesandcontant.push_back(make_pair(cut.size(), cut));
                //times.push_back(cut.size());
                //match.insert(cut.size(), cut); 不能插入相同的键值
                i = j; // 因为j不是数字才跳出循环的，接着i会在外层循环中自增，没关系
            }
        }
        //stable_sort(timesandcontant.begin(), timesandcontant.end(), greater<>());
        //stable_sort(times.begin(), times.end(), greater<>());
        stable_sort(timesandcontant.begin(), timesandcontant.end(), cmp);
        // stable_sort(timesandcontant.begin(), timesandcontant.end());
        int max = timesandcontant.begin()->first;
        auto it = timesandcontant.begin();
        while (it->first == max)
        {
            cout << it->second;
            it++;
        }
        cout << ',' << max << endl;
    }

    return 0;
}