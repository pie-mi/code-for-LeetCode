#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;
/*
通过全部用例
运行时间5ms
占用内存440KB
*/

// 遗忘了不确定减出来是int吗，问AI了
int convertCharToInt(char c)
{
    return c - 'A'; // 不用+1，矩阵A刚好存在matrix[0]
}

int main()
{
    /*其实题目是只统计乘法运输次数，没有算加法，所以一开始看不懂计算方式，问了AI分别给出乘和加的运算次数才看懂*/
    int n;
    vector<pair<int, int>> matrix;
    string formula;
    stack<char> reorder;
    // vector<int> order;
    int calulation = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int a, b;
        cin >> a >> b;
        matrix.emplace_back(make_pair(a, b));
    }
    cin >> formula;

    for (auto i : formula)
    {
        if (i == ')' && !reorder.empty())
        {
            if (reorder.top() != '(' && reorder.size() >= 2) //原本写的是while，作用等于if 哈
            {
                char latter = reorder.top();
                reorder.pop();
                char former = reorder.top();
                reorder.pop();
                // order.emplace_back(convertCharToInt(former));
                // order.emplace_back(convertCharToInt(latter));
                // 新矩阵规模是前者的行乘后者的列，每个元素前者的列或后者的行个元素对应相乘再相加
                calulation = calulation + matrix[convertCharToInt(former)].first *
                                          matrix[convertCharToInt(latter)].second *
                                          matrix[convertCharToInt(former)].second;
                
                reorder.pop(); //弹走'('
                //做了一次矩阵乘法，将新矩阵塞回去，将刚刚的两个矩阵改为一样新的行列数
                reorder.push(former);
                matrix[convertCharToInt(former)].second = matrix[convertCharToInt(latter)].second;
                matrix[convertCharToInt(latter)].first = matrix[convertCharToInt(former)].first;
            }
            
            continue;
        }
        else
        {
            reorder.push(i);
        }
    }
    cout << calulation;
    return 0;
}