/*
 * @lc app=leetcode id=133 lang=cpp
 *
 * [133] Clone Graph
 */
#include <vector>
#include <deque>
#include <unordered_map>
using namespace std;

/*
非内联的
Accepted
22 / 22 testcases passed
3ms Beats 69.40%
11.90MB Beats 89.35%
*/

class Node
{
public:
    int val;
    vector<Node *> neighbors;
    Node()
    {
        val = 0;
        neighbors = vector<Node *>();
    }
    Node(int _val)
    {
        val = _val;
        neighbors = vector<Node *>();
    }
    Node(int _val, vector<Node *> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};
// @lc code=start

class Solution
{
public:
    Node *cloneGraph(Node *node)
    {
        if (node == nullptr)
            return nullptr;

        // 因为题目自带的返回类型是Node *，不能返回unique_ptr<Node>，
        // 要么普通的new，力扣自己delete，要么或者试一下shared ptr
        // unique_ptr<Node> first = make_unique<Node>(node->val, node->neighbors);
        // auto first = make_shared<Node>(node->val, node->neighbors);
        Node *first = new Node(node->val);
        // 因为题目中说节点编号和值是对应的，因此不用unordered_map来记录是否已经有这个节点，用vector就OK
        vector<Node *> newcopy(101, nullptr); // 最多100个节点
        newcopy[1] = first;
        // 问题主要是如何通过这个节点遍历整个连通图，也是深度优先和广度优先，
        // 实际上通过neighbor的node指针一个个遍历，这里用广度优先，队列
        // 如果已经节点存在，就不进入队列，不然每次都会有节点入队，因为连通，即使已存在，不知道何时遍历完，结束不了
        // 核心是一开始复制的都是原图节点的指针，不OK，直接根据val在newcopy里取，
        // 就算是nullptr也先直接取，到时候遍历到有它就会new并更新newcopy里的指针
        deque<Node *> que; // 存的是原图节点
        que.push_back(node);
        vector<bool> visited(101, false); // 记录原图节点是否遍历过

        while (!que.empty())
        {
            auto curr = que.front();
            if (newcopy[curr->val] == nullptr)
            {
                // 这里注意，不能直接new时调用两个参数的那个构造函数，
                // 否则复制的都是原图的节点指针，要替换为新创的节点指针
                newcopy[curr->val] = new Node(curr->val);
            }
            for (auto &&i : curr->neighbors)
            {
                // 按照原图val来插入neighbors，新图指针哦，就算时未遍历到也有nullptr
                // 这里有问题！！想法是让邻接表中存储的是对newcopy数组元素的引用，
                // 这样当后续节点被创建时，引用会自动指向正确的节点。这种思路在理论上是可行的，但在 C++ 中实现会遇到几个问题
                // C++ 中的引用一旦初始化就不能重新绑定；vector 存储引用是不合法的；即使使用指针，也需要确保所有节点在被引用前已创建
                newcopy[curr->val]->neighbors.push_back(newcopy[i->val]);
                if (!visited[i->val])
                {
                    que.push_back(i);
                    visited[i->val] = true; //case 1的3会在2与4重复压入
                }    
            }
            visited[curr->val] = true;
            que.pop_front();
        }
        return first;
    }

private:
    // Node firstOfCopy;
    //  已有对象move转移所有权给unique ptr，不推荐，堆上可以，栈上似乎不太OK
};
// @lc code=end

Node *Solution::cloneGraph(Node *node)
{
    if (node == nullptr)
            return nullptr;
    // 接受AI建议，入队时确保节点创建，用unordered map<Node *,Node *>也顺便节省visited
    unordered_map<Node *, Node *> oldToNew;
    deque<Node *> que;
    que.push_back(node);
    while (!que.empty())
    {
        auto curr = que.front();
        if (oldToNew.find(curr) == oldToNew.end()) //节点本身
        {
            oldToNew[curr] = new Node(curr->val);
        }
        for (auto &&i : curr->neighbors) //邻接关系
        {
            if (oldToNew.find(i) == oldToNew.end())
            {
                oldToNew[i] = new Node(i->val);
                que.push_back(i); //在这里压入，不是外面，未探索过的才压入，不然就无穷循环了
            }
            oldToNew[curr]->neighbors.push_back(oldToNew[i]); //节点的所有邻居都要复制，邻接关系不变
            // not here
        }
        que.pop_front();
    }
    return oldToNew[node];
}