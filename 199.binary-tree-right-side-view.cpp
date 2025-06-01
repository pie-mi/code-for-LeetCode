/*
 * @lc app=leetcode id=199 lang=cpp
 *
 * [199] Binary Tree Right Side View
 */
#include <vector>
#include <queue>
using namespace std;

/*
Accepted
217 / 217 testcases passed
0ms Beats100.00%
15.13MB Beats24.69%
*/

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
public:
    vector<int> rightSideView(TreeNode *root)
    {
        // 本来想知道左右最深，超出右子树的深度才有可能被看到，
        // 但右子树中的左子树可能最深，各子树没能直接对比，
        // 看了其他解法其实也是对的，右子树优先，记录首个达到深度的就是了，用递归或者栈
        // 又想到可能转为广度优先，一层层遍历，每一层的最右边就是了

        vector<int> result;
        queue<TreeNode *> que;
        if (root == nullptr)
            return result;
        que.push(root);
        auto count = que.size();
        while (!que.empty())
        {
            if (count-- > 0)
            {

                if (count == 0) // 上边自减了，即本次是此层最后一个
                {
                    result.emplace_back(que.front()->val);
                }
                if (que.front()->left != nullptr)
                    que.push(que.front()->left);
                if (que.front()->right != nullptr)
                    que.push(que.front()->right);
                que.pop();
            }
            else
                count = que.size();
        }
        return result;
    }
};
// @lc code=end
