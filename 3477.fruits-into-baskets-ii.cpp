#include <vector>
#include <algorithm>
using namespace std;

/*
Wrong Answer
333 / 904 testcases passed
[7,5] [8,5] 应该是0，但得到1

Accepted
904 / 904 testcases passed
4ms Beats35.09%
48.88MB Beats74.93%
*/

class Solution
{
public:
    int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets);
    /*{
        sort(fruits.begin(), fruits.end());
        auto kind = fruits.size();
        for (auto i = 0; i < fruits.size(); i++)
        {
            for (auto j = 0; j < fruits.size(); j++)
            {
                if (fruits[i] > baskets[j])
                {
                    continue;
                }
                else
                {
                    baskets[j] = -1; // 标记已装入
                    kind--;
                    break;
                }
            }
        }
        return kind;
    }*/
};

int Solution::numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets)
{
    auto kind = fruits.size();
    for (auto i = 0; i < fruits.size(); i++)
    {
        for (auto j = 0; j < baskets.size(); j++)
        {
            if (fruits[i] > baskets[j])
            {
                continue;
            }
            else
            {
                baskets[j] = -1; // 标记已装入
                kind--;
                break;
            }
        }
    }
    return kind;
}