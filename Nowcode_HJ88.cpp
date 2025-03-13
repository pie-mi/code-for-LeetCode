#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
enum type
{
    gezi,
    duizi,
    sange,
    bomb,
    shunzi,
    jokers
};

unordered_map<string, int> map{
    {"3", 3},
    {"4", 4},
    {"5", 5},
    {"6", 6},
    {"7", 7},
    {"8", 8},
    {"9", 9},
    {"10", 10},
    {"J", 11},
    {"Q", 12},
    {"K", 13},
    {"A", 14},
    {"2", 15},
    {"joker", 16},
    {"JOKER", 17}};

void stringToint(string poker, vector<int> &card)
{
    // AI，改编
    istringstream iss(poker);
    string token;
    while (iss >> token) // 使用 >> 从流中提取字符串，自动按空格分割
    {
        int num = map[token];
        card.push_back(num);
    }
}

type whatType(const vector<int> poker)
{
    if (poker[0] == map["joker"] && poker[1] == map["JOKER"])
    {
        return jokers;
    }
    // vector<int> card;

    /* 才想到牌里没有1，是A，所以不用怕读到字符'1'时1与10混淆
    for (auto i : poker)
    {
        auto space = poker.find(' ');
    }
    */

    switch (poker.size())
    {
    case 1:
        return gezi;
        break;
    case 2: // 对王已经一开始处理了
        return duizi;
        break;
    case 3:
        return sange;
        break;
    case 4:
        return bomb;
        break;
    default:
        return shunzi;
        break;
    }
}

int main()
{
    string poker, poker1, poker2;
    /*
    char c;
    while (cin >> c)
    {
        if (c != ' ')
        {
            if (c != '-')
            {
                poker1.push_back(c);
                poker1.push_back(' ');
            }
            else
                break;

        }
    }
    while (cin >> c)
    {
        if (c != ' ')
        {
            poker2.push_back(c);
            poker2.push_back(' ');
        }
    }
    */
    getline(cin, poker);
    // AI
    auto split = poker.find('-');
    poker1 = poker.substr(0, split);
    poker2 = poker.substr(split + 1);
    vector<int> poker1_int, poker2_int;
    stringToint(poker1, poker1_int);
    stringToint(poker2, poker2_int);
    auto poker1_type = whatType(poker1_int);
    auto poker2_type = whatType(poker2_int);
    string result = "ERROR";
    if (poker1_type == jokers || poker2_type == jokers)
        result = poker1_type == jokers ? poker1 : poker2;
    else
    {
        if (poker1_type == bomb && poker2_type != bomb)
            result = poker1;
        if (poker1_type != bomb && poker2_type == bomb)
            result = poker2;
        if (poker1_type == poker2_type)
        {
            // 比较最小的牌
            if (poker1_int[0] < poker2_int[0])
                result = poker2;
            else
                result = poker1;
        }
        // else
        // cout << "ERROR" << endl;
    }
    cout << result << endl;
    return 0;
}