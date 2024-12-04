#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
第一个想法是：将小的砝码凑成大的砝码，最终要使得全部砝码(包括凑出来的/本来整个的)数量为“1”，
用两个for就可以。实际就是2个3g砝码视为6g砝码。但是也有只要1个3g的情况，因此繁琐
但想了下去，复杂，而且最后排列组合也不是两个for能完成的
*/

/*
想着，突然发现不需要看是哪几个凑出来，只需要出现过就是，因此可以逐个加进来，与之前就有的再组合，
就是很直观的3g砝码与之前的已经组合出现过的2、3、4再组合，得到2+3、3+3、4+3，
*/

int main()
{
    int n;
    vector<int> weight;
    cin >> n;
    int a;
    while (cin >> a)
    {
        weight.push_back(a);
    }
    vector<int> nums(weight.begin() + weight.size() / 2, weight.end());
    weight.erase(weight.begin() + ((weight.size() + 1) / 2), weight.end());
    vector<int> combinition(1, 0);           // 用于按顺序存储已有组合
    unordered_map<int, int> is_weight_exist; // 用于查看组合是否已存在
    is_weight_exist.insert({0, 1}); //注意：需要用大括号将要插入的key-value括起来，或者make_pair
    for (int i = 0; i < weight.size(); i++)
    {
        /* 这是插入自己，不需要额外，因为0已经在里面了，0+自己就是自己
        if (is_weight_exist.find(weight[i]) == is_weight_exist.end())
        {
            is_weight_exist.insert({weight[i], 1}); // 查了一下，好像用insert是不会覆盖，用下标会覆盖
            combinition.push_back(weight[i]);
        }
        */
        while (nums[i] > 0) //weigth[i]有nums[i]个
        {
            int times = is_weight_exist.size();
            for (int j = 0; j < times; j++) //这里不能直接写is_weight_exist.size()，因为可能会插入，数量就变多了
            {
                if (is_weight_exist.find(combinition[j] + weight[i]) == is_weight_exist.end())
                {
                    is_weight_exist.insert({combinition[j] + weight[i], 1});
                    combinition.push_back(combinition[j] + weight[i]);
                }
            }
            nums[i]--;
        }
    }
    cout << combinition.size();
    return 0;
}