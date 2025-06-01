/*
 * @lc app=leetcode id=112 lang=c
 *
 * [112] Path Sum
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*
Accepted
118/118 cases passed (0 ms)
Your runtime beats 100 % of c submissions
Your memory usage beats 97.33 % of c submissions (11.4 MB)
*/

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool hasPathSum(struct TreeNode *root, int targetSum)
{
    bool leftside, rightside;
    leftside = rightside = false;
    // 因为从根到叶子节点，根先加进去，前序遍历
    int addsum = 0;
    if (root == NULL)
    {
        return false;
    }
    // 不对哦，要是root真的就是target，但后面确实也是+1、-1交叉到叶子节点才是true
    // root->left == root->right == NULL表达不OK，这是先判断左右是否相等，得到1/0再与NULL比较
    if (targetSum == root->val && root->left == NULL && root->right == NULL)
    {
        return true;
    }

    //好笑，忘了写函数名，只写了括号和参数，居然是不报错合法的语句！
    //逗号运算符会依次执行括号内的表达式，并返回最后一个表达式的值
    leftside = hasPathSum(root->left, targetSum - root->val);
    rightside = hasPathSum(root->right, targetSum - root->val);
    return leftside || rightside;
}
// @lc code=end

int main()
{
    // 为根节点分配内存
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = 1;

    // 为左节点分配内存
    struct TreeNode *leftNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    leftNode->val = 2;

    // 为右节点分配内存
    struct TreeNode *rightNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    rightNode->val = 3;

    // 连接节点
    root->left = leftNode;
    root->right = rightNode;
    leftNode->left = NULL;
    leftNode->right = NULL;
    rightNode->left = NULL;
    rightNode->right = NULL;

    bool kuci = hasPathSum(root, 5);

    // 释放内存
    free(leftNode);
    free(rightNode);
    free(root);

    return 0;
}