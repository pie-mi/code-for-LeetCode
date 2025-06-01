/*
 * @lc app=leetcode id=236 lang=cpp
 *
 * [236] Lowest Common Ancestor of a Binary Tree
 */
// #include <stdlib.h>
#include <vector>
#include <deque>
#include <unordered_set>

using namespace std;

/*
Accepted
18ms Beats 11.65%
20.43MB Beats 5.04%
*/

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// @lc code=start

class Solution
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        // 层次遍历树转为数组，下标从1开始，除以2向下取整就是父节点，但是很难处理单边树
        std::vector<TreeNode *> treeOrder;
        treeOrder.push_back(root); // 用root占个位treeOrder[0]
        // 用最大值标记空节点 TreeNode(__INT_MAX__);
        // 层次遍历就是广度优先
        deque<TreeNode *> queue;
        queue.push_back(root);
        int p_index, q_index;
        int result_index = 0;                   // 根节点一定是共同祖先
        /*
        while (!queue.empty() && queue.front()) // 叶子节点会push null进队列，实际已空了
        {
            // 用指针也要把null也push进去，要占位的
            treeOrder.push_back(queue.front());
            if (queue.front()) // 非null，不然null->left越界
            {
                if (queue.front()->val == p->val)
                {
                    p_index = treeOrder.size();
                }
                if (queue.front()->val == q->val)
                {
                    q_index = treeOrder.size();
                }
                queue.push_back(queue.front()->left); // 如果数组存treenode类型，就用*(queue.front().left)取节点
                queue.push_back(queue.front()->right);
            }
            queue.pop_front();
        }
        */
        // 记录所有祖先
        /*
        vector<int> p_ancestor{p_index};
        vector<int> q_ancestor{q_index};
        for (int i = p_index; i >= 1;)
        {
            i /= 2;
            p_ancestor.push_back(i);
        }
        for (int i = q_index; i >= 1;)
        {
            i /= 2;
            q_ancestor.push_back(i);
        }
        */
        // 发现单边树不好处理，转为深度优先，用栈记录找到p、q之前的路径/祖先
        vector<TreeNode *> p_route, q_route;
        unordered_set<TreeNode *> visited{root};
        p_route.push_back(root);
        q_route.push_back(root);
        auto temp = root;
        /*
        while (!p_route.empty())
        {
            if (temp)
            {
                p_route.push_back(temp->val);
                if (temp->val == p->val)
                {
                    // p_route.pop_back(); 不pop，自己也是自己的祖先
                    break;
                }
            }
            else
            {
                p_route.pop_back();
            }

            temp = p_route.back();
        }
        */

        /* 根节点开始一直左子树，经过的全部压栈记录，找不到再弹走，压入最下方的右子树，一层层返回
        do
        {
            if (p_route.back()->val == p->val)
            {
                break;
            }
            else if (temp->left && visited.count(temp) == 0) //否则左子树尽头又会尝试进入左子树
            {
                temp = temp->left;
                p_route.push_back(temp);
                visited.emplace(temp);
            }
            else
            {
                if (temp->right)
                {
                    temp = temp->right;
                    p_route.push_back(temp);
                    visited.emplace(temp);
                }
                else
                {
                    p_route.pop_back();
                    temp = p_route.back();
                }                              
            }
            
        } while (!p_route.empty());
        while (!q_route.empty())
        {
            if (q_route.back()->val == q->val)
            {
                break;
            }
            else if (temp->left && visited.count(temp) == 0) //否则左子树尽头又会尝试进入左子树
            {
                temp = temp->left;
                q_route.push_back(temp);
                visited.emplace(temp);
            }
            else
            {
                if (temp->right)
                {
                    temp = temp->right;
                    q_route.push_back(temp);
                    visited.emplace(temp);
                }
                else
                {
                    q_route.pop_back();
                    temp = q_route.back();
                }                              
            }
        }
        */
        
        
        // AI
        vector<TreeNode *> p_path, q_path;
        p_path = findPathToTarget(root, p->val);
        q_path = findPathToTarget(root, q->val);
        /*
        unordered_set<int>
            find_commom(p_path.begin(), p_path.end());
        for (auto i : q_path)
        {
            if (find_commom.count(i))
            {
                result_index = i;
            }
        }
        return treeOrder[result_index];
        */

        TreeNode *result = root;
        //要找最近公共祖先，要深度最深，要倒序
        unordered_set<TreeNode *> find_commom_path(p_path.begin(), p_path.end());
        for (auto i = q_path.rbegin(); i != q_path.rend(); i++)
        {
            if (find_commom_path.count(*i))
            {
                result = *i;
                break;
            } 
        }
        return result;
    }

private:
    // AI
    bool findPath(TreeNode *node, int target, vector<TreeNode *> &path)
    {
        if (!node)
        {
            return false;
        }
        path.push_back(node);
        if (node->val == target) { //自己也压进去了的，自己也是自己祖先
            return true;
        }
        //左子树
        if (findPath(node->left, target, path))
        {
            return true;
        }
        //右子树
        if (findPath(node->right, target, path))
        {
            return true;
        }
        //未找到，回溯
        path.pop_back();
        return false;
    }

    vector<TreeNode *> findPathToTarget(TreeNode *node, int target)
    {
        vector<TreeNode *> path;
        findPath(node, target, path);
        return path;
    }
};
// @lc code=end

int main()
{
    Solution debug;
    // [3,5,null,6,2,0,8,null,null,7,4,null,null,77,null] p=77 q=8 output=8 expected=6
    TreeNode root(3), no2(5);
    // 发现如果是单边树，应该要用很多null填空位要凑齐2^n -1，有点难度，特别是单右边树

    // case 2:[3,5,1,6,2,0,8,null,null,7,4] p=5 q=4 output=3 expected=5
}