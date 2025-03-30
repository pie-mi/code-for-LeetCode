#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/*
AC! 运行时间：2ms 占用内存：492KB

7/20 组用例通过
39.66.68.72
3868643487 是因为超出了int的表示范围
预期
658654280
230.150.208.159
实际
658654280
127.255.255.255
*/

int main()
{
    string ip;
    unsigned int decimal_ip;
    cin >> ip >> decimal_ip;
    // string result_ip;
    unsigned int result_decimal;
    vector<string> ip_split;

    //按.分割IP
    string token;
    istringstream i(ip);
    while (getline(i, token, '.'))
    {
        ip_split.push_back(token);
    }
    vector<int> ip_split_int;
    for (string it : ip_split)
    {
        ip_split_int.push_back(stoi(it));
    }

    result_decimal = ip_split_int[0] * pow(2, 24) + ip_split_int[1] * pow(2, 16) + ip_split_int[2] * pow(2, 8) + ip_split_int[3];

    // AI
    // result_ip = to_string(result_decimal / pow(2, 24)) + "." + to_string((result_decimal % (int)pow(2, 24)) / pow(2, 16)) + "." + to_string((result_decimal % (int)pow(2, 16)) / pow(2, 8)) + "." + to_string(result_decimal % (int)pow(2, 8));

    ip_split[3] = to_string(decimal_ip % (int)pow(2, 8));
    ip_split[2] = to_string(decimal_ip / (int)pow(2, 8) % (int)pow(2, 8));
    ip_split[1] = to_string(decimal_ip / (int)pow(2, 16) % (int)pow(2, 8));
    ip_split[0] = to_string(decimal_ip / (int)pow(2, 24));

    cout << result_decimal << endl;
    cout << ip_split[0] << '.' << ip_split[1] << '.' << ip_split[2] << '.' << ip_split[3] << endl;
    return 0;
}
// 64 位输出请用 printf("%lld")