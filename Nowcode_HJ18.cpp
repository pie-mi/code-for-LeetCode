#include <bitset>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define ignore 'g'

using namespace std;

/*
42.53.252.112~255.0.0.0
166.237.7.68~255.0.0.0
136.3.73.64~255.255.0.0
204.29.136.133~255.255.0.245 X
195.30.208.94~255.255.0.213 X
154.253.86.183~255.200.255.0 X
94.164.187.131~255.255.0.0
167.79.164.186~255.0.0.0
194.172.2.64~255.255.0.0
210.212.79.137~255.255.255.42 X
143.151.137.40~255.255.255.255 X
184.145.79.157~255.0.0.0
100.214.131.51~255.255.255.255 X
233.10.182.98~255.0.0.125 X
99.184.165.228~255.0.0.82 X
92.20.159.86~255.0.0.0
198.198.174.83~255.0.0.0
17.158.122.89~255.255.75.255 X
149.253.103.237~255.0.26.0 X
91.243.182.7~255.0.0.0
36.76.55.4~255.255.255.255 X
126.54.86.143~255.0.0.0
预期 5 4 2 0 0 11 0
实际 7 5 2 0 0 8 0
*/

/*简书写法*/
vector<string> split(const string &str, const string &pattern)
{
    vector<string> res;
    if (str == "")
        return res;
    // 在字符串末尾也加入分隔符，方便截取最后一段
    string strs = str + pattern;
    size_t pos = strs.find(pattern);

    while (pos != strs.npos)
    {
        if (pos >= 1)
        {
            string temp = strs.substr(0, pos); // 忽略 -1是不要这个pattern
            res.push_back(temp);
        }

        // 去掉已分割的字符串,在剩下的字符串中进行分割
        strs = strs.substr(pos + 1, strs.size());
        pos = strs.find(pattern);
    }

    return res;
}

// stackoverflow上也有split的一个写法 https://stackoverflow.com/questions/26328793/how-to-split-string-with-delimiter-using-c

int string2int(string kuci)
{
    stringstream stream;
    int n;
    stream << kuci;
    stream >> n;
    return n;
}

bool is_mask_legal(string mask)
{
    string pattern = ".";
    vector<string> con = split(mask, pattern);
    vector<int> int_con;
    if (con.size() != 4) // 题目示例提醒了255..255.127不合法
    {
        return false;
    }
    /*本来想很麻烦地一节节判断，若第一个不是255，后面不是0，那肯定不合法*/
    for (int i = 0; i < con.size(); i++)
    {
        int_con.push_back(string2int(con[i]));
    }
    // int->binary->string
    bitset<8> one(int_con[0]); // int->binary
    bitset<8> two(int_con[1]);
    bitset<8> three(int_con[2]);
    bitset<8> four(int_con[3]);
    string oo = one.to_string(); // binary->string
    string tt = two.to_string();
    string hh = three.to_string();
    string ff = four.to_string();
    // string concat = con[0] + con[1] + con[2] + con[3];
    string cat = oo + tt + hh + ff;
    // unsigned int int_con = (unsigned int)string2int(concat);
    string _1 = "1";
    string _0 = "0";
    if (int_con[0] == 0 && int_con[1] == 0 && int_con[2] == 0 && int_con[3] == 0) // 全0 非法 不要使用连等号
        return false;
    if (int_con[0] == 255 && int_con[1] == 255 && int_con[2] == 255 && int_con[3] == 255) // 全1 非法 不要使用连等号
        return false;
    if (cat.find_first_of(_0) > cat.find_last_of(_1)) // 全1 全0都是非法子网掩码
    {
        return true;
    }
    else
        return false;
}

bool is_private_ip(vector<int> &int_con)
{
    if (int_con[0] == 10)
    {
        return true;
    }
    if (int_con[0] == 172 && (16 <= int_con[1] && int_con[1] <= 31))
    {
        return true;
    }
    if (int_con[0] == 192 && int_con[1] == 168)
    {
        return true;
    }
    return false;
}

char is_ip_legal(string ip) // I-不合法 ABCDE分别代表自己 ingore-不统计 XYZ分别为属于ABC私有地址
{
    string pattern = ".";
    vector<string> con = split(ip, pattern);
    vector<int> int_con;
    // int flag;
    char ju;
    if (con.size() != 4) // 题目示例提醒了255..255.127不合法
    {
        ju= 'I';
        goto LA;
    }
    for (int i = 0; i < con.size(); i++)
    {
        int_con.push_back(string2int(con[i]));
    }
    if (int_con[0] == 0 || int_con[0] == 127)
    {
        ju = ignore; //return ignore;
        goto LA;
    }
    if ((1 <= int_con[0] && int_con[0] <= 255) && (0 <= int_con[1] && int_con[1] <= 255) && (0 <= int_con[2] && int_con[2] <= 255) && (0 <= int_con[3] && int_con[3] <= 255))
    {
        if (1 <= int_con[0] && int_con[0] <= 126)
        {
            if (is_private_ip(int_con))
            {
                ju = 'X'; //return 'X';
            }
            else
                ju = 'A'; //return 'A';
        }
        else if (128 <= int_con[0] && int_con[0] <= 191)
        {
            if (is_private_ip(int_con))
                ju = 'Y'; //return 'Y';
            else
                ju = 'B'; //return 'B';
        }
        else if (192 <= int_con[0] && int_con[0] <= 223)
        {
            if (is_private_ip(int_con))
                ju = 'Z'; // 'Z';
            else
                ju = 'C'; //return 'C';
        }
        else if (224 <= int_con[0] && int_con[0] <= 239)
            ju = 'D'; //return 'D';
        else if (240 <= int_con[0] && int_con[0] <= 255)
            ju = 'E'; // return 'E';
    }
    else
        ju= 'I';
LA:    return ju;
}

int main()
{
    vector<int> result;
    int A, B, C, D, E, illegal, personal_private;A = B = C = D = E = illegal = personal_private = 0;
    string ip;
    while (cin >> ip)
    {
        
        string mask;
        auto pos = ip.find('~');
        mask = ip.substr(pos + 1, ip.size());
        ip = ip.substr(0, pos);
        char classify = is_ip_legal(ip);
        if (classify == ignore)
        {
            continue;
        }
        if (classify == 'I' || !is_mask_legal(mask))
        {
            illegal++;
            continue;
        }
        else
        {
            switch (classify)
            {
            /*case ignore:
                continue;
                break;*/
            case 'X':
                A++;
                personal_private++;
                break;
            case 'Y':
                B++;
                personal_private++;
                break;
            case 'Z':
                C++;
                personal_private++;
                break;
            case 'A':
                A++;
                break;
            case 'B':
                B++;
                break;
            case 'C':
                C++;
                break;
            case 'D':
                D++;
                break;
            case 'E':
                E++;
                break;
            default:
                break;
            }
        }
    }
    cout << A << " " << B << " " << C << " " << D << " " << E << " " << illegal << " " << personal_private;
    return 0;
}