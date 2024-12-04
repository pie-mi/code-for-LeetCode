#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;

int countCharacter(string &str)
{
    int count = 0;
    unordered_map<char, int> ifexist;
    for (int i = 0; i < str.size(); i++)
    {
        auto got = ifexist.find(str[i]); //未找到返回end
        if (got == ifexist.end())
        {
            ifexist.emplace(str[i], 1);
            count++;
        }
        
    }
    return count;
}

int main()
{
    string input;
    cin >> input;
    int result;
    result = countCharacter(input);
    cout << result;
    return 0;
}