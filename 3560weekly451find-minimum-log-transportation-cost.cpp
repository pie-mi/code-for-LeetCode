#include <vector>
#include <string>
using namespace std;

/*
Accepted
740 / 740 testcases passed
0ms Beats100.00%
8.80MB Beats59.66%
*/

class Solution {
public:
    long long minCuttingCost(int n, int m, int k) {
        long long cost = 0;
        int cutsOfN = n / k;
        int cutsOfM = m / k;

        while (cutsOfN--)
        {
            cost += (long long)k * (n - k); //运行时显示两个相乘超出了int表示范围，将其中一个强制转换为longlong，另一个也会用
            n -= k;
        }
        while (cutsOfM--)
        {
            cost += (long long)k * (m - k);
            m -= k;
        }
        return cost;
    }
};
