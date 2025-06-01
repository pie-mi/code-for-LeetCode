/*
 * @lc app=leetcode id=105 lang=cpp
 *
 * [105] Construct Binary Tree from Preorder and Inorder Traversal
 */
#include <vector>
using std::vector;

/*
Accepted
203 / 203 testcases passed
23ms Beats 10.79%
74.48MB Beats 9.01%
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
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        // 前序与中序还原二叉树，思路是OK的，前序遍历第一个是根节点
        // 根节点对应中序里就划分了左右子树，
        // 实现就是递归，树都递归，得到左子树，其中前序遍历第二个就是左子树的根，又找中序再划分左右
        // 主要是前序遍历如何按照左右子树划分，才能作为参数传去子树的前序遍历
        // 根据中序得到的左/右子树的size按顺序划分同样size作为子树的前序遍历即可
        // 原因在于前序遍历(视为一团)，左子树最后一个(右下方)也会比右子树第一个(根)更早遍历到，不会混合的
        if (preorder.size() == 0)
        {
            // 例如前序和中序都是同一个开头，即左子树为空
            return nullptr;
        }
        if (preorder.size() == 1)
        {
            return new TreeNode(preorder[0]);
        }

        TreeNode *root = new TreeNode(preorder[0]);
        auto i = 0;
        while (inorder[i] != preorder[0] && i < preorder.size())
            i++;
        
        // 问AI才想起这种用迭代器加偏移的方式初始化，不然一个个for很机械，都是左闭右开区间
        vector<int> leftInorder(inorder.begin(), inorder.begin() + i);            // 根自己不要纳入
        vector<int> leftPreorder(preorder.begin() + 1, preorder.begin() + 1 + i); // 举例子也可，但是另一方法就是前序与中序size要一致
        vector<int> rightInorder(inorder.begin() + i + 1, inorder.end());
        vector<int> rightPreorder(preorder.begin() + i + 1, preorder.end());
        root->left = buildTree(leftPreorder, leftInorder);
        root->right = buildTree(rightPreorder, rightInorder);
        return root;
    }
};
// @lc code=end
