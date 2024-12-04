/*
 * @lc app=leetcode.cn id=206 lang=cpp
 *
 * [206] 反转链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *pre;
        ListNode *p;
        ListNode *next;
        /*不带头结点的
        p = head->next;
        pre = head->next;
        next = p->next;
        head->next->next = NULL;
        */
        pre = p = head;
        if(!head || !(head->next)) //本来就是空链表或只有一个结点
            return head;
        else
            next = head->next;
        p->next = NULL;
        p = next;
        next = p->next; //这种写法对只有一个结点会出错，可以修改进入whlie中顺序
        while (p->next)
        {
            p->next = pre;
            pre = p;
            p = next;
            next = p->next;
        }
        p->next = pre;
        //head->next = p; 若带有头节点就这样
        return p;
    }
};
// @lc code=end

