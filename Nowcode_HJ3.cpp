#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
private:
    /* data */
public:
    Solution(/* args */);
    ~Solution();
    //去重加排序  可以用sort和unique  亦可用 map来去重再sort  或者set
    void DeduplicateAndSort(vector<int> &randnums)
    {
        sort(randnums.begin(), randnums.end());
        auto last = unique(randnums.begin(), randnums.end());
        randnums.erase(last, randnums.end());
    }
};

Solution::Solution(/* args */)
{
}

Solution::~Solution()
{
}

int main()
{
    vector<int> randnums;
    int numsize; //第一个输入是个数
    cin >> numsize;
    int a;
    while (cin >> a)
    {
        randnums.push_back(a);
    }
    Solution jimmy;
    jimmy.DeduplicateAndSort(randnums);
    vector<int>::iterator bozi;
    for ( bozi = randnums.begin(); bozi != randnums.end(); bozi++)
    {
        cout << *(bozi) << endl;
    }
    return 0;
}