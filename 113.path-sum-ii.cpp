/*
 * @lc app=leetcode id=113 lang=cpp
 *
 * [113] Path Sum II
 */
#include <vector>
#include <unordered_set>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
Accepted
115/115 cases passed (0 ms)
Your runtime beats 100 % of cpp submissions
Your memory usage beats 43.31 % of cpp submissions (21.6 MB)
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
class Solution
{
public:
    vector<vector<int>> pathSum(TreeNode *root, int targetSum)
    {
        vector<vector<int>> path;
        if (!root)
        {
            return path;
        }
        vector<TreeNode *> singlePath{root};
        vector<int> singlePathVal{root->val}; // 要返回是值不是节点
        // path = pathSum(root->left, targetSum - root->val);
        // path.push_back(pathSum(root->right, targetSum - root->val));
        unordered_set<TreeNode *> visited{root}; //前几天做236题AI给的这个回溯是否访问过
        auto currentSum = root->val;
        while (!singlePath.empty())
        {
            if (singlePath.back()->left == nullptr && singlePath.back()->right == nullptr)
            {
                if (currentSum == targetSum)
                {
                    path.push_back(singlePathVal);
                }
                //到叶子节点了，是不是target都要弹走了，回溯了
                singlePath.pop_back();
                currentSum -= singlePathVal.back();
                singlePathVal.pop_back();
            }
            else if (singlePath.back()->left && !visited.count(singlePath.back()->left))
            {
                singlePath.push_back(singlePath.back()->left);
                singlePathVal.push_back(singlePath.back()->val); // 刚刚压进去了，就是back
                visited.insert(singlePath.back());
                currentSum += singlePathVal.back();
                continue;
            }
            else if (singlePath.back()->right && !visited.count(singlePath.back()->right))
            {
                singlePath.push_back(singlePath.back()->right);
                singlePathVal.push_back(singlePath.back()->val); // 刚刚压进去了，就是back
                visited.insert(singlePath.back());
                currentSum += singlePathVal.back();
                continue;
            }
            else
            {
                //左右非空且都visited了，pop，回溯
                singlePath.pop_back();
                currentSum -= singlePathVal.back();
                singlePathVal.pop_back();
            }
            
        }
        return path;
    }
};
// @lc code=end
