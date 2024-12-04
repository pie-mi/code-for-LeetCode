#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool is_Prime(int n)
{
    for (int i = 2; i < (int)sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int n, a;
    cin >> n;
    vector<int> nums;
    while (cin>>a)
    {
        nums.emplace_back(a);
    }
    //标签里有 排序
    //大于3的质数恒可表示为6k-1或6t+1，大于3的孪生素数对恒可表示为6b±1的形式
    //随着自然数n的增大，尽管n内的素数总量在增大，正比趋于n/ln (n);但n内的素数的平均分布区间越来越大，分布密度越来越小
    //感觉是越大的数，越可能是合数，质因子可能性越大
}