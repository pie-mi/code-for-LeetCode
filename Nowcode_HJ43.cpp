#include <iostream>
#include <queue>
#include <stack>
#include <tuple>
#include <vector>
using namespace std;

// 看了答案，大概写一写
void bfs(vector<vector<int>> &matrix, int i, int j, vector<pair<int, int>> &route, queue<pair<int, int>> &contain)
{
    // queue<pair<int, int>> contain;
    // contain.push(make_pair(0, 0));
    i=contain.front().first;
    j = contain.front().second;
    contain.pop();
    if (i - 1 < 0 || matrix[i-1][j]==1)
    {
        ;
    }
    else
        contain.push(make_pair(i - 1, j));
    if (i+1>=matrix.size()|| matrix[i+1][j]==1)
    {
        ;
    }
    else
        contain.push(make_pair(i + 1, j));
    if (j-1<0|| matrix[i][j-1]==1)
    {
        ;
    }
    else
        contain.push(make_pair(i, j - 1));
    if (j+1>=matrix[0].size()|| matrix[i][j+1]==1)
    {
        ;
    }
    else
        contain.push(make_pair(i, j + 1));
    
    if (contain.back().first!=matrix.size()-1 || contain.back().second!=matrix[0].size()-1)
    {
        bfs(matrix, contain.back().first, contain.back().second, route, contain);
    }
    else
    {
        route.push_back(contain.back()); //应该是逆序放入的，cout时用逆向迭代器rbegin
    } 
}

int main()
{
    enum direction
    {
        up,
        rightt,
        down,
        leftt,
        done
    };
    vector<tuple<int, int, direction, direction>> route; // 行,列, where are you from, next direction to explore
    int m, n;
    cin >> m >> n;
    vector<int> row;
    vector<vector<int>> matrix;
    int a;
    int k = 0;
    while (k < (m * n))
    {
        cin >> a;
        row.push_back(a);
        k++;
        if (row.size() == n)
        {
            matrix.push_back(row);
            row.clear();
        }
    }
    route.push_back(make_tuple(0, 0, done, rightt));

    direction where_are_you_from = leftt;
    stack<direction> steps;
    // int i, j;
    // i = j = 0;
    direction d = up;
    /*
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {

        }

    }*/
    while (get<0>(route[route.size() - 1]) != (m - 1) || get<1>(route[route.size() - 1]) != (n - 1)) //(i<m-1 && j<n-1)
    {
        d = get<3>(route[route.size() - 1]);
        where_are_you_from = get<2>(route[route.size() - 1]);
        if (d == up)
        {
            if ((get<0>(route[route.size() - 1]) - 1 < 0) || (matrix[get<0>(route[route.size() - 1]) - 1][get<1>(route[route.size() - 1])] == 1) || where_are_you_from == up)
            {
                d = rightt;
                continue;
            }
            else
            {
                where_are_you_from = down;
                route.push_back(make_tuple(get<0>(route[route.size() - 1]) - 1, get<1>(route[route.size() - 1]), down, up));
            }
        }
        else if (d == rightt)
        {
            if ((get<1>(route[route.size() - 1]) + 1 >= n) || (matrix[get<0>(route[route.size() - 1])][get<1>(route[route.size() - 1]) + 1] == 1) || where_are_you_from == rightt)
            {
                d = down;
                continue;
            }
            else
            {
                where_are_you_from = leftt;
                route.push_back(make_tuple(get<0>(route[route.size() - 1]), get<1>(route[route.size() - 1]) + 1, leftt, up));
            }
        }
        else if (d == down)
        { /* 但是检查先右边的，多余的担心了
             if (i==m-1) //去到最下边那一行，只有往右走，往左走是走不到右下角的
             {
                 d = rightt;
                 continue;
                }*/
            if ((get<0>(route[route.size() - 1]) + 1 >= m) || (matrix[get<0>(route[route.size() - 1]) + 1][get<1>(route[route.size() - 1])] == 1) || where_are_you_from == down)
            {
                d = leftt;
                continue;
            }
            else
            {
                where_are_you_from = up;
                route.push_back(make_tuple(get<0>(route[route.size() - 1]) + 1, get<1>(route[route.size() - 1]), up, up));
            }
        }
        else if (d == leftt)
        {
            if ((get<1>(route[route.size() - 1]) - 1 < 0) || (matrix[get<0>(route[route.size() - 1])][get<1>(route[route.size() - 1]) - 1] == 1) || where_are_you_from == leftt)
            {
                d = done;
                continue;
            }
            else
            {
                where_are_you_from = rightt;
                route.push_back(make_tuple(get<0>(route[route.size() - 1]), get<1>(route[route.size() - 1]) - 1, rightt, up));
            }
        }
        else if (d == done)
        {
            route.pop_back();
        }
    }
    route.push_back(make_tuple(m, n, where_are_you_from, up)); // 右下角，随意
    for (auto it = route.begin(); it != route.end(); it++)
    {
        cout << '(' << get<0>(*it) << ',' << get<1>(*it) << ')' << endl;
    }
    return 0;
}