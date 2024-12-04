/*
 * @lc app=leetcode.cn id=207 lang=cpp
 *
 * [207] 课程表
 */
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
using std::vector, std::stack, std::find, std::queue;
// @lc code=start
/*
class Vetex
{
private:
    int data;

public:
    Vetex();
    ~Vetex();
};

Vetex::Vetex()
{
}

Vetex::~Vetex()
{
}


class Graph
{
private:
    vector<Vetex> v;
    vector<vector<Vetex>> e;

public:
    Graph();
    ~Graph();
};

Graph::Graph():
{
}

Graph::~Graph()
{
    for (int i = 0; i < e.size(); i++)
    {
        for (int j = 0; j < v.size(); j++)
        {
            delete e[i][j];
        }

    }

}
*/
// 看了官方代码后发觉不用自己写graph类，自己构建个邻接矩阵就行
class Solution
{
private:
    vector<bool> vetex;
    vector<vector<bool>> edge;

public:
    void dfs(vector<vector<int>> &edge, int nth)
    {
    }
    // 看看是否都满足了这个课程的先修课程要求
    bool if_satisfy(int n, vector<vector<bool>> &edge, vector<bool> &if_finish_course)
    {
        bool res = true;
        for (int i = 0; i < edge.size(); i++)
        {
            if (edge[i][n])
            {
                res = res & if_finish_course[i];
            }
        }
        return res;
    }

    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<bool> if_finish_course(numCourses, false);
        bool result = false;
        // 看了标签和提示里的拓扑排序
        // 因为可能是形成很长环的循环依赖，例如1->2->3->...->9->1
        // 此题条件每个课程只会依赖另一课程 X错误！
        // prerequisites可以含有超级多词条对
        // 先遍历一次，将没有被依赖的课程先修了
        vector<bool> is_relyon = if_finish_course;
        vetex = if_finish_course;
        vector<vector<bool>> kuci(numCourses, vetex);
        edge = kuci;
        for (auto it = prerequisites.begin(); it != prerequisites.end(); it++)
        {
            // is_relyon[(*it)[1]] = true;
            edge[(*it)[1]][(*it)[0]] = true;
        }
        queue<int> independent;
        for (auto i = 0; i < numCourses; i++)
        {
            // int count_free = 0;
            // auto fi = edge[0].begin();
            auto fi = find(edge[i].begin(), edge[i].end(), true);
            if (fi != edge[i].end())
            {
                continue;
            }
            else
            {
                independent.push(i);
                if_finish_course[i] = true;
            }
        }
        stack<int> order;
        while (!independent.empty())
        {
            int temp = independent.front();
            independent.pop();
            order.push(temp);
            // if_finish_course[temp] = true;
            while (!order.empty())
            {
                int curr = order.top();
                for (int i = 0; i < edge[curr].size(); i++)
                {
                    if (edge[curr][i] == true)
                    {
                        if (if_satisfy(i, edge, if_finish_course))
                        {
                            if_finish_course[i] = true;
                            // independent.push(i);
                            order.push(i);
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                /*
                auto fi = find(edge[curr].begin(), edge[curr].end(), true);
                if (fi==edge[curr].end())
                {
                    ;
                }
                */
            }
        }
        auto fi = if_finish_course.begin();
        result = find(if_finish_course.begin(), if_finish_course.end(), false) == if_finish_course.end() ? true : false;
        return result;
    }
};
// @lc code=end

// 一直困惑在于只要搜到就标记为已学，好像不满足需要先修两门课的，但拓扑排序就是如此，可以的
bool Solution::canFinish(int numCourses, vector<vector<int>> &prerequisites)
{
    bool result;
    vector<bool> if_finish(numCourses, false);
    // queue<int> order;
    vector<int> indegree(numCourses, 0); // 入度表
    vetex.resize(numCourses, false);
    edge.resize(numCourses, vetex);
    for (auto it = prerequisites.begin(); it != prerequisites.end(); it++)
    {
        // is_relyon[(*it)[1]] = true;
        edge[(*it)[1]][(*it)[0]] = true;
        indegree[(*it)[0]]++;
    }
    queue<int> independent;
    for (auto i = 0; i < numCourses; i++)
    {
        // int count_free = 0;
        // auto fi = edge[0].begin();
        auto fi = find(edge[i].begin(), edge[i].end(), true);
        if (fi != edge[i].end())
        {
            continue;
        }
        else
        {
            independent.push(i);
            if_finish[i] = true;
        }
    }
    while (!independent.empty())
    {
        int temp = independent.front();
        independent.pop();
        for (int i = 0; i < numCourses; i++)
        {
            if (edge[temp][i])
            {
                indegree[i]--;
                if (indegree[i] == 0)
                {
                    independent.push(i);
                    if_finish[i] = true;
                }
            }
        }
    }
    auto fi = if_finish.begin();
    result = find(if_finish.begin(), if_finish.end(), false) == if_finish.end() ? true : false;
    return result;
}