/*
 * @lc app=leetcode.cn id=79 lang=cpp
 *
 * [79] 单词搜索
 */
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

#define up 1
#define right 2
#define down 3
#define left 4
#define finish 5
// @lc code=start
class Solution
{
protected:
    /*enum checkorder
    {
        up,
        right,
        down,
        left,
        finish
    };*/
    void checkandpush(stack<pair<int, int>> &searchcontant, int flag)
    {
        int m = searchcontant.top().first;
        int n = searchcontant.top().second;
        if (flag == up && n >= 1)
        {
            n--;
            /*if (board[m][n]==the1stcharacter)
                {
                    the1stchar.push(make_pair(m, n));
                }*/
        }
    }

public:
    bool exist(vector<vector<char>> &board, string word)
    {
        bool result = false;
        queue<pair<int, int>> thecharorder;
        queue<pair<int, int>> the1stchar;
        stack<pair<int, int>> searchcontant;
        deque<pair<int, int>> contain;

        // stack<tuple<int, int, int>> scissor;
        // 用make_tuple，访问用get<下标> scissor

        auto the1stcharacter = word[0];
        for (int m = 0; m < board.size(); m++)
        {
            for (int n = 0; n < board[0].size(); n++)
            {
                if (board[m][n] == the1stcharacter)
                {
                    the1stchar.push(make_pair(m, n));
                }
            }
        }

        while (!the1stchar.empty())
        {
            if (result)
            {
                goto END;
            }
            
            int flag = up;
            stack<tuple<int, int, int>> scissor;
            scissor.push(make_tuple(the1stchar.front().first, the1stchar.front().second, flag));

            for (int i = 1; i < word.length(); i++)
            {
                auto thechartocompare = word[i];
                // int flag = up;
                while (get<2>(scissor.top()) != finish)
                {
                    if (get<2>(scissor.top()) == up)
                    {
                        if (get<1>(scissor.top()) >= 1) //有无头上一格
                        {
                            if (board[get<0>(scissor.top())][get<1>(scissor.top()) - 1] == thechartocompare)
                            {
                                // searchcontant.push(make_pair(the1stchar.front().first, the1stchar.front().second - 1));
                                get<2>(scissor.top())++; //已检查up方向，修改为下一个要检查方向
                                scissor.push(make_tuple(get<0>(scissor.top()), get<1>(scissor.top()) - 1, up));
                                //continue;
                                goto NextCharRoop;
                            }
                        }
                    }
                    else if (get<2>(scissor.top()) == right)
                    {
                        if (get<0>(scissor.top()) < (board[0].size() - 1)) //有无右边一格
                        {
                            if (board[get<0>(scissor.top()) + 1][get<1>(scissor.top())] == thechartocompare)
                            {
                                // searchcontant.push(make_pair(the1stchar.front().first, the1stchar.front().second - 1));
                                //flag++;
                                get<2>(scissor.top())++;
                                scissor.push(make_tuple(get<0>(scissor.top()) +1, get<1>(scissor.top()), up));
                                //continue;
                                goto NextCharRoop;
                            }
                        }
                    }
                    else if (get<2>(scissor.top()) == down)
                    {
                        if (get<1>(scissor.top()) < (board.size() -1)) //有无下边一格
                        {
                            if (board[get<0>(scissor.top())][get<1>(scissor.top()) + 1] == thechartocompare)
                            {
                                // searchcontant.push(make_pair(the1stchar.front().first, the1stchar.front().second - 1));
                                //flag++;
                                get<2>(scissor.top())++;
                                scissor.push(make_tuple(get<0>(scissor.top()), get<1>(scissor.top()) + 1, up));
                                //continue;
                                goto NextCharRoop;
                            }
                        }
                    }
                    else if (get<2>(scissor.top()) == left)
                    {
                        if (get<0>(scissor.top()) >= 1) //有无左边一格
                        {
                            if (board[get<0>(scissor.top()) - 1][get<1>(scissor.top())] == thechartocompare)
                            {
                                // searchcontant.push(make_pair(the1stchar.front().first, the1stchar.front().second - 1));
                                //flag++;
                                get<2>(scissor.top())++;
                                scissor.push(make_tuple(get<0>(scissor.top()) -1, get<1>(scissor.top()), up));
                                //continue;
                                goto NextCharRoop;
                            }
                            else //left是最后检查的，不对就pop出了
                            {
                                scissor.pop();
                                i--; //pop了，对比的字符也应该是前一个
                            }
                        }
                        else //没有左边，证明这条路找不到的,因为左边是最后检查的
                        {
                            scissor.pop();
                            i--;
                        }
                    }
                    //flag++;
                }
                if (i == word.length()-1)
                {
                    result = true;
                }
                //flag = right;
                

                
                    //the1stchar.pop();
NextCharRoop:   //直接为空，执行下一轮外层循环
            }
            /*
            for (int m = 0; m < board.size(); m++)
            {
                for (int n = 0; n < board[0].size(); n++)
                {
                    if (board[m][n] == thechartocompare)
                    {
                        thecharorder.push(make_pair(m, n));
                        searchcontant.push(make_pair(m, n));
                        break;
                    }
                }
                break;
            }
            */

            the1stchar.pop();
        }
    END:
        return result;
    }
};
// @lc code=end
