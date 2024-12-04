/*
 * @lc app=leetcode.cn id=138 lang=cpp
 *
 * [138] 复制带随机指针的链表
 */

//#define NULL nullptr

// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node *Oldformer, *Oldlatter, *Newformer, *Newlatter;
        Node *newhead;
        Oldformer = head;

        //原本含有0、1、2个结点的
        if (head==NULL)
            return head;
        if (head->next==NULL)
        {
            newhead = Newformer = new Node(head->val);
            /*这里错了，指回原链表了*/
            //Newformer->random = Oldformer->random;
            Newformer->random = Oldformer->random ? Newformer : NULL;
            return newhead;
        }
        
        if (head->next->next==NULL)
        {
            newhead = Newformer = Newlatter = new Node(Oldformer->val);
            Newlatter = new Node(head->next->val);
            Newformer->next = Newlatter;
            //还有两个random的赋值
            if (head->random==head)
            {
                Newformer->random = Newformer;
            }
            else if (head->random==head->next)
            {
                Newformer->random = Newlatter;
            }
            /*else
                Newformer->random = NULL;*/
            if (head->next->random==head)
            {
                Newlatter->random = Newformer;
            }
            else if (head->next->random==head->next)
            {
                Newlatter->random = Newlatter;
            }
            /*else
                Newlatter->random = NULL;*/

            return newhead;
        }
        

        newhead = Newformer = Newlatter = new Node(Oldformer->val);
        while (Oldformer->next) //先完整构建普通单链表，因为random可能指向后面，那需要后面结点存在
        {
            Newlatter = new Node(Oldformer->next->val);
            Newformer->next = Newlatter;
            Newformer = Newlatter;
            Oldformer = Oldformer->next;
        }
        Newlatter = new Node(Oldformer->val); //last one
        Newlatter->next = NULL;
        //开始规整random指针
        /*难在对应的序号，不能通过对比值来确定是哪一个结点,
        因为示例3就是每个结点值一样，甚至random也可以一样，区分不了
        要通过对比指针，即内存地址，指向同一个地址，肯定是这个结点
        */
        Oldformer = Oldlatter = head;
        Newformer = Newlatter = newhead;
        int count = 0;//要是Node类自带排第几就方便了
        while (Oldformer->next)
        {
            //count自己会变回0!!!出大错！！
            //count会变-1，不是0，之后一直变-2-3！又符合while循环了
            if (Oldformer->random==Oldlatter)
            {
                while (count--) //注意是--count还是count--
                {
                    Newlatter = Newlatter->next;
                }
                count = 0;
                Newformer->random = Newlatter;
                Newformer = Newformer->next;
                Newlatter = newhead;
                Oldlatter = head; // 因为可能指向前面，从头来
            }
            else{//还未到random指向那个结点
                count++;
                Oldlatter = Oldlatter->next;
                continue;//避免执行下面的动Oldformer
            }
            Oldformer = Oldformer->next;
        }
        //最后结点的random还未规整好
        Oldlatter = head;
        count = 0;
        while (Oldformer->random!=Oldlatter)
        {
            Oldlatter = Oldlatter->next;
            count++;
        }
        while (count--)
        {
            Newlatter = Newlatter->next;
        }
        Newformer->random = Newlatter;
        return newhead;
    }
};
// @lc code=end
/*
int main(){
    Node *p0, *p1, *p2, *p3, *p4;
    p0 = new Node(7);
    p1 = new Node(13);
    p2 = new Node(11);
    p3 = new Node(10);
    p4 = new Node(1);
    p0->next = p1;
    p1->next = p2;
    p2->next = p3;
    p3->next = p4;

    p1->random = p0;
    p2->random = p4;
    p3->random = p2;
    p4->random = p0;

    Solution bozi;
    Node *kuci;
    kuci = bozi.copyRandomList(p0);

    return 0;
}
*/