#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
using namespace std;
/*
void sortScore( bool mode, vector<int> &score)
{
    if (mode)
    {
        stable_sort(score.begin(), score.end());
    }
    else
        stable_sort(score.begin(), score.end(), greater<int>());
}
*/
/*
multimap<int,string> biggerOrder()
{
    multimap<int, string> hashtable;
    string a;
    int b;
    while (cin >> a >> b)
        hashtable.insert(make_pair(b,a));   
    return hashtable; //叫“移动构造函数”
}

multimap<int,string,greater<int>> smallerOrder()
{
    multimap<int, string, greater<int>> hashtable;
    string a;
    int b;
    while (cin >> a >> b)
        hashtable.insert(make_pair(b,a));   
    return hashtable;
}
*/

void biggerOrder()
{
    multimap<int, string> hashtable;
    string a;
    int b;
    while (cin >> a >> b)
        hashtable.insert(make_pair(b,a));
    multimap<int, string>::iterator it;
    for ( it = hashtable.begin(); it != hashtable.end(); it++)
        cout << it->second << " " << it->first << endl;
    
}

void smallerOrder()
{
    multimap<int, string, greater<int>> hashtable;
    string a;
    int b;
    while (cin >> a >> b)
        hashtable.insert(make_pair(b,a));
    multimap<int, string>::iterator it;
    for ( it = hashtable.begin(); it != hashtable.end(); it++)
        cout << it->second << " " << it->first << endl;
    
}

int main()
{
    //vector<int> score;
    int n;
    cin >> n;
    bool mode;
    cin >> mode;
    //关键是如何对应名字与成绩
    //unordered_map<int, string> hashtable;
    /*作用域只在里面 extern也不行
    if (mode)
    {
        multimap<int, string> hashtable;
    }
    else
        extern multimap<int, string, greater<int>> hashtable;
    */
    
    /*
    https://www.cnblogs.com/lca1826/p/6847404.html
    multimap中，同一个键关联的元素必然相邻存放。3种办法输出同一key对应的多个value
    1.使用find和count函数  2.使用lower_bound(key)和upper_bound(key) 3.使用equat_range(key)
    */
    /*
    string a;
    int b;
    while (cin >> a >> b)
    {
        //score.push_back(b);
        hashtable.insert(make_pair(b,a));
        
    }
    */
    if(mode)
        biggerOrder();
    else
        smallerOrder();
    return 0;
}