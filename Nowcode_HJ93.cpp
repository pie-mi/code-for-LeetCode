#include <cmath>
#include <iostream>
#include <numeric>
#include <stack>
#include <vector>
using namespace std;

// 用accumulate函数的前两个参数指定累加的范围，第三个参数为累加的初值，第四个参数为进行的操作，默认为累加

// 看答案，是全排列，不看如何分组，看能否凑出这个gap即可
bool fun(int i, int newgap, int gap, vector<int> &contain)
{
    if (i == contain.size())
    {
        return gap == abs(newgap);
    }
    else
    {
        return fun(i + 1, newgap + contain[i], gap, contain) || fun(i + 1, newgap - contain[i], gap, contain);
    }
}

int main()
{
    int n, a;
    vector<int> contain;
    bool result;
    cin >> n;
    vector<int> hold5;
    vector<int> hold3;
    while (cin >> a)
    {
        if (a % 5 == 0)
            hold5.push_back(a);
        else if (a % 3 == 0)
            hold3.push_back(a);
        else
            contain.push_back(a);
    }

    /*这种写法错误，因为erase之后本来就指向下一个，但又i++，漏过了这一个
    for (auto i = contain.begin(); i != contain.end(); i++)
    {
        if (*i % 5 == 0)
        {
            hold5.push_back(*i);
            contain.erase(i);
        }

        else if (*i % 3 == 0) // 刚好利用if与else if只执行一个
        {
            hold3.push_back(*i);
            contain.erase(i);
        }
    }
    */
    int gap = accumulate(hold5.begin(), hold5.end(), 0) - accumulate(hold3.begin(), hold3.end(), 0);
    gap = abs(gap);
    /*if (gap == 0 && contain.empty())
    {
        result = true;
        cout << result;
    }
//想不通如何选择哪几个，如何分，想用剪枝回溯
    /*
    for (int i = 0; i < contain.size()/2; i++)
    {
        vector<int> remain = contain;
        for (int j = 0; j < i; j++)
        {

        }

    }
    */
    if (fun(0, 0, gap, contain))
    {
        cout << "true";
    }
    else
        cout << "false";
    return 0;
}