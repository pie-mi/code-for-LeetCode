#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;
// 标签里有动态规划

/*124
16 103 132 23 211 75 155 82 32 48 79 183 13 91 51 172 109 102 189 121 12 120 116 133 79 120 116 208 47 110 65 187 69 143 140 173 203 35 184 49 245 50 179 63 204 34 218 11 205 100 90 19 145 203 203 215 72 108 58 198 95 116 125 235 156 133 220 236 125 29 235 170 130 165 155 54 127 128 204 62 59 226 233 245 46 3 14 108 37 94 52 97 159 190 143 67 24 204 39 222 245 233 11 80 166 39 224 12 38 13 85 21 47 25 180 219 140 201 11 42 110 209 77 136*/

int main()
{
    vector<int> high;
    int n;
    cin >> n;
    int a;
    while (cin >> a)
    {
        high.push_back(a);
    }
    // 计算每一个的逆序数，然后划分?

    // 直接看解法，“最长递增子序列”的变体，从左/右两边分别统计
    vector<int> increase_left(n, 1);
    vector<int> decrease_right(n, 1);
    increase_left[0] = 1;
    decrease_right[n - 1] = 1;
    int maxi = 1;
    for (auto i = 0; i < n; i++)
    {
        for (auto j = 0; j < i; j++)
        {
            if (high[j] < high[i])
            {
                // increase_left[i]++;
                increase_left[i] = max(increase_left[j] + 1, increase_left[i]); //不是与max比
            }
        }
    }
    maxi = 1;
    for (auto i = n - 1; i >= 0; i--)
    {
        for (auto j = n-1; j > i; j--)
        {
            if (high[j] < high[i])
            {
                // decrease_right[i]++;
                decrease_right[i] = max(decrease_right[j] + 1, decrease_right[i]);
            }
        }
    }
    vector<int> together;
    for (int i = 0; i < n; i++)
    {
        together.push_back(increase_left[i] + decrease_right[i]);
    }
    maxi = together[0];
    for (auto it = together.begin(); it != together.end(); it++)
    {
        maxi = max(*it, maxi);
    }
    if (n == 1) // 只有一个输入
    {
        maxi = 1;
    }

    cout << n-(maxi - 1); // 统计了最高佬两次 (max-1)是最终合唱队的人数，出列人数就总人数减一下
    return 0;
}

