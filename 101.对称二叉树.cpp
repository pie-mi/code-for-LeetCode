/*
 * @lc app=leetcode.cn id=101 lang=cpp
 *
 * [101] 对称二叉树
 */

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

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

class Solution {
public:
    //注意结点值不一样的不对称[1,2,2,3,4,4,3,null,null,5,null,null,7,null,null]
    bool matchSymmetric(TreeNode *leftroot,TreeNode *rightroot)
    {
        bool SymmeLeft = true;
        bool SymmeRight = true;
        if (leftroot && rightroot)
        {
            if (leftroot->val == rightroot->val)
            {
                if (leftroot->left && rightroot->right)
                {
                    SymmeLeft = SymmeLeft & matchSymmetric(leftroot->left, rightroot->right);
                }
                else if (leftroot->left == rightroot->right) //都到叶子结点了
                {
                    SymmeLeft = true; // return true; //Symme = true会使本来已经不对称的false又变回true
                }
                else
                    return false; //有一个false不对称即全棵树不对称
                if (leftroot->right && rightroot->left)
                    SymmeRight = SymmeRight & matchSymmetric(leftroot->right, rightroot->left);
                else if (leftroot->right == rightroot->left) //都到叶子结点了
                {
                    SymmeRight = true; // return true;
                }
                else
                    return false;
            }
            else
                return false; // Symme = false;
        }

        return (SymmeLeft & SymmeRight);
    }

    bool isSymmetric(TreeNode* root) {
        bool result = true;
        TreeNode *rootleft, *rootright;
        if(!root) //空树
            return true;
        rootleft = root->left;
        rootright = root->right;
        if (rootleft==rootright) //只有根节点
        {
            return true;
        }
        
        if (rootleft && rootright)
        {
            /*if (root->right)
            {
                if (root->val == root->val)
                {
                    
                }
                
            }*/
            result = matchSymmetric(rootleft, rootright);
        }
        else
            result = false;
        return result;
    }
};
// @lc code=end

