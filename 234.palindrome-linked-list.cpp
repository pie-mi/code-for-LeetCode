/*
 * @lc app=leetcode id=234 lang=cpp
 *
 * [234] Palindrome Linked List
 */

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
Accepted
93 / 93 testcases passed
4ms Beats53.59%
114.27MB Beats97.59%
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
class Solution
{
public:
    bool isPalindrome(ListNode *head)
    {
        bool result = false;
        // 遍历一遍转进去vector，再前后双指针，这样时间也是O(n)，空间0(n)

        // 空间O(1)，先遍历一次，知道size，如果每次i与size-i对比，这样就要O(N^2)，环形链表也没区别
        // 知道size就知道中间点，原地反转半边链表，Leet206即是

        // 转为int也不是很OK，开头可能是0

        ListNode *curr = head;
        auto size = 0;
        while (curr)
        {
            size++;
            curr = curr->next;
        }
        if (size == 0 || size == 1) // 题目保证至少一个节点
        {
            return true;
        }

        auto n = size / 2; // 向下取整刚好
        if (size % 2)      // 奇数
        {
            // 将前半部分反转，后边对比，一次遍历即可
            ListNode *former, *latter;
            former = nullptr;
            latter = head;
            while (n-- > 0)
            {
                ListNode *temp = latter->next;
                latter->next = former;
                former = latter;
                latter = temp;
            }
            latter = latter->next; // 奇数，跳过正中间那一个
            n = size / 2;          // reset n
            while (n-- > 0)
            {
                if (former->val == latter->val)
                {
                    former = former->next;
                    latter = latter->next;
                    result = true;
                }
                else
                {
                    result = false;
                    break;
                }
            }
        }
        else
        {
            // 偶数
            ListNode *former, *latter;
            former = nullptr;
            latter = head;
            while (n-- > 0)
            {
                ListNode *temp = latter->next;
                latter->next = former;
                former = latter;
                latter = temp;
            }

            n = size / 2; // reset n
            while (n-- > 0)
            {
                if (former->val == latter->val)
                {
                    former = former->next;
                    latter = latter->next;
                    result = true;
                }
                else
                {
                    result = false;
                    break;
                }
            }
        }
        return result;
    }

private:
    // 比Leet206的加多一个n，反转指定个数，但是发现也不是很长代码，直接用了
    ListNode *reverseList(ListNode *head, int n)
    {
        ListNode *former, *latter;
        // 官方解答
        former = nullptr; // head;
        latter = head;    // head->next;
        while (latter)
        {
            ListNode *temp = latter->next;
            latter->next = former;
            former = latter;
            latter = temp;
        }
        return former;
    }
};
// @lc code=end
