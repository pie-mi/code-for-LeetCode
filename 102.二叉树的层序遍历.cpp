/*
 * @lc app=leetcode.cn id=102 lang=cpp
 *
 * [102] 二叉树的层序遍历
 */

#include <vector>
#include <queue>
#include <cmath>
using namespace std;

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
 * 
 */

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        //层次遍历，课本当然是利用队列
        vector<vector<int>> result;
        // 可以使用vector<vector<int>> result(x,vector<int>(n));但现在不知道树的高度
        queue<TreeNode *> bozi;
        /*没想到空指针也能进入队列*/
        if (!root)
        {
            vector<vector<int>> result0({});
            return result0;
        }
        
        bozi.push(root);
        //result[0].push_back(root->val);
        //vector<int> kuci;
        //kuci.push_back(root->val);
        //result.push_back(kuci);
        //int upperNULL, lowerNULL;
        //upperNULL = lowerNULL = 0;
        
        //int countNULL = 0;
        for (int i = 0; !bozi.empty(); i++)
        {
            
            //upperNULL = lowerNULL;
            //lowerNULL = 0;
            //countNULL *= 2;
            //int j = countNULL + 1;
            //j = upperNULL ? 1 : 2 * upperNULL; // pow(2, upperNULL);
            int j = bozi.size();
            vector<int> dalai({});
            while (j>0)
            {
                if(bozi.front())
                    dalai.push_back(bozi.front()->val);
                if(bozi.front()->left)
                    bozi.push(bozi.front()->left);
                if(bozi.front()->right)
                    bozi.push(bozi.front()->right);
                bozi.pop();
                j--;
            }
            result.push_back(dalai);

/*我自己的方法，最后一个测试用例未通过：利用二叉树每一层的结点数*/
            int countNULL = 0;
        int newNULL = 0;
        for (int i = 0; !bozi.empty(); i++)
        {
            
            //countNULL =countNULL*2;
            //countNULL = countNULL * pow(2, i - 1);
            int j = countNULL + 1;
            newNULL = 0;
            vector<int> dalai;
            while (j<=pow(2,i) && !bozi.empty())
            {
                if(bozi.front())
                {
                    dalai.push_back(bozi.front()->val);
                    //j++;
                }
                
                j++;
                
                if(bozi.front()->left)
                {
                    //j++;
                    bozi.push(bozi.front()->left);
                }
                else
                    newNULL++; //即使是空也计个数，也算
                
                if(bozi.front()->right)
                {
                    //j++;
                    bozi.push(bozi.front()->right);
                }
                else
                    newNULL++;
                
                bozi.pop();
            }
            result.push_back(dalai);
            countNULL = countNULL * 2 + newNULL;
        }

            /*
            while (j<=pow(2,i) && !bozi.empty()) //这样可以避免空节点的计数
            {
                if(bozi.front())
                {
                    dalai.push_back(bozi.front()->val);
                    //j++;
                }

                j++;
                
                if(bozi.front()->left)
                {
                    //j++;
                    bozi.push(bozi.front()->left);
                }
                else
                    countNULL++; // lowerNULL++; //  lowerNULL += pow(2, i);//即使是空也计个数，也算

                if(bozi.front()->right)
                {
                    //j++;
                    bozi.push(bozi.front()->right);
                }
                else
                    countNULL++; // lowerNULL++;

                bozi.pop();
            }
            result.push_back(dalai);
            */
            

            /*
            if (j<=pow(2,i))
            {
                if(bozi.front()->val)
                    kuoci.push_back(bozi.front()->val);
                    //result[j].push_back(bozi.front()->val);
            }
            else
            {
                result.push_back(kuoci);
                continue; //第i层完成了，去i+1层
            }
            if(bozi.front()->left)
                bozi.push(bozi.front()->left);
            if(bozi.front()->right)
                bozi.push(bozi.front()->right);
            bozi.pop();
            */
        }

        return result;
    }
};
// @lc code=end

