/*
 * @lc app=leetcode id=108 lang=cpp
 *
 * [108] Convert Sorted Array to Binary Search Tree
 */
#include <vector>
using namespace std;
/*
Accepted
31/31 cases passed (4 ms)
Your runtime beats 35.48 % of cpp submissions
Your memory usage beats 9.64 % of cpp submissions (26.1 MB)
*/
struct TreeNode {
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
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // 递归 almost by AI
        if (nums.empty()){
            return nullptr;
        }
        if (nums.size() == 1)
        {
            return new TreeNode(nums[0]);
        }
        
        int mid = nums.size() / 2;
        vector<int> left(nums.begin(), nums.begin() + mid);
        vector<int> right(nums.begin() + mid + 1, nums.end());
        return new TreeNode(nums[mid], sortedArrayToBST(left), sortedArrayToBST(right));

        // 或者可以自己写个AVL树的左右旋，再一个个插入，但对于已排好序的浪费时间复杂度了
    }
};
// @lc code=end

