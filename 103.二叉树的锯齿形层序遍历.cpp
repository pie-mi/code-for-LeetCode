/*
 * @lc app=leetcode.cn id=103 lang=cpp
 *
 * [103] 二叉树的锯齿形层序遍历
 */
#include <vector>
#include <queue>
#include <cmath>
#include <stack>
using namespace std;
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
protected:
    void timetoReverse(vector<int> &kuci){
        stack<int> tom;
        vector<int>::iterator it;
        for ( it = kuci.begin(); it != kuci.end();it++) {
            tom.push(*it);
        }
        kuci.clear();
        while (!tom.empty())
        {
            kuci.push_back(tom.top());
            tom.pop();
        }
        
    }
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        //轮流进队列和栈，栈的儿子进队列，队列儿子进栈
        queue<TreeNode *> bozi;
        //stack<TreeNode *> dalai;
        bool sequence_order_queue = true;
        if (!root)
        {
            vector<vector<int>> result0({});
            return result0;
        }
        
        bozi.push(root);
        while (!bozi.empty())
        {
            int j = bozi.size();
            vector<int> kuci({});
            while (j>0)
            {
                if(bozi.front())
                    kuci.push_back(bozi.front()->val);
                if(bozi.front()->left)
                    bozi.push(bozi.front()->left);
                if(bozi.front()->right)
                    bozi.push(bozi.front()->right);
                bozi.pop();
                j--;
            }
            if(!sequence_order_queue)
                timetoReverse(kuci);
            result.push_back(kuci);
            sequence_order_queue = !sequence_order_queue;
        }
        /*
        while (!bozi.empty() || !dalai.empty())
        {
            //int j ;
            //j = sequence_order_queue ? bozi.size() : dalai.size();
            vector<int> kuci({});
            //while (!bozi.empty())//j>0
            
                if (sequence_order_queue)
                {
                    while (!bozi.empty())
                    {
                        if(bozi.front())
                            kuci.push_back(bozi.front()->val);
                        if(bozi.front()->left)
                            dalai.push(bozi.front()->left); //下一次反向，入栈了
                        if(bozi.front()->right)
                            dalai.push(bozi.front()->right);
                        bozi.pop();
                    }
                    
                    
                    //j--;
                    
                }
                else
                {
                    while (!dalai.empty())
                    {
                        if (dalai.top())
                        {
                            kuci.push_back(dalai.top()->val);
                        }
                        if (dalai.top()->left)
                        {
                            bozi.push(dalai.top()->left);
                        }
                        if (dalai.top()->right)
                        {
                            bozi.push(dalai.top()->right); //这里写成left了，粗心
                        }
                        dalai.pop();
                        }
                    
                    
                }
                
                
            
            result.push_back(kuci);
            sequence_order_queue = !sequence_order_queue;
        }*/
        return result;
    }
};
// @lc code=end

