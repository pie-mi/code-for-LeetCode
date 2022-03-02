#include<iostream>
using namespace std;
/**
 * Definition for singly-linked list.*/
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution { //注意两链表可长度不一致，其中一个尽头后，再处理进位，后面就可以直接将result后面指向未尽的链表，即第三个构造函数的提示
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carrier =0 ; //进位
        ListNode* p1 = l1;
        ListNode* p2 = l2;
        ListNode *result; //不需这么快新建第一个节点= new ListNode;
        ListNode* k;
        bool flag = 1; //用于创造第一个节点,应该可用static代替

        while((p1 != nullptr) && (p2 != nullptr)){ 
            if(flag==0){ //0要放在前面
                k->next = new ListNode;
                k = k->next;
            }
            if(flag==1){
                result = new ListNode;
                k = result;
                flag = 0; //第一个节点才给result
            }
            
            int co_carrier = carrier; //备份原进位
            (p1->val + p2->val + carrier) >= 10 ? carrier = 1 : carrier = 0; //进位
            k->val = (p1->val + p2->val + co_carrier) % 10;
            
            p1 = p1->next;
            p2 = p2->next;
            
            }

        /*之前版本
        while((p1->next != nullptr) && (p2->next != nullptr)){ //最后一位未处理
            int co_carrier = carrier; //备份原进位
            (p1->val + p2->val + carrier) >= 10 ? carrier = 1 : carrier = 0; //进位
            k->val = (p1->val + p2->val + co_carrier) % 10;
            k->next = new ListNode;
            k = k->next;
            p1 = p1->next;
            p2 = p2->next;
            }
        int co_carrier = carrier; //备份原进位
        (p1->val + p2->val + carrier) >= 10 ? carrier = 1 : carrier = 0; //进位
        k->val = (p1->val + p2->val + co_carrier) % 10;
        */ 
        
        if((p1==nullptr) && (p2==nullptr)){
            if(carrier == 1)
                k->next = new ListNode(1);
            goto ENND; // return result;
        }
        if((p1 == nullptr) && (p2 != nullptr)){ //第一个链表空了，再处理，之前的进位嘛，后面照抄  原来出错版本(p1->next == nullptr) && (p2->next != nullptr)
                while((p2!= nullptr) && (p2->val == 9) && (carrier ==1)){ //如果剩余的全是9，进位是1
                    k->next = new ListNode(0);
                    k = k->next;
                    p2 = p2->next;
                }
                if(p2 == nullptr && carrier==1){
                    k->next = new ListNode(1);
                    goto ENND;
                }
                if(p2 == nullptr && carrier==0)
                    goto ENND;
                k->next = new ListNode(p2->val + carrier);
                k = k->next;
                k->next = p2->next; //将后面接去result即可，链表嘛，后边连着的
                goto ENND;          // return result;
            }
        if((p2 == nullptr) && (p1 != nullptr)){
                while((p1!= nullptr) && (p1->val == 9) && (carrier ==1)){ //如果剩余的全是9，进位是1，这个判空必要p1是null，无p1->val
                    k->next = new ListNode(0);
                    k = k->next;
                    p1 = p1->next;
                }
                if(p1 == nullptr && carrier==1){ //9完之后结束了，p1是null，无p1->val
                    k->next = new ListNode(1);
                    goto ENND;
                }
                if(p1 == nullptr && carrier==0)
                    goto ENND;
                k->next = new ListNode(p1->val + carrier);
                k = k->next;
                k->next = p1->next; //将后面接去result即可，链表嘛，后边连着的
                goto ENND;          // return result;
            }
ENND:        return result;
    }
};

int main(){
    ListNode* l1;
    ListNode* l2;
    ListNode *k1;
    ListNode* k2;
    ListNode *resul;
    l1 = new ListNode(0);
    l2 = new ListNode(7);
    k1 = l1;
    k2 = l2;
    /*for (int i = 0; i < 1;i++){
        k1->next = new ListNode(9);
        k1 = k1->next;
    }*/
    k1->next = new ListNode(1);
    /*for (int j = 0; j < 3;j++){
        k2->next = new ListNode(9);
        k2 = k2->next;
    }*/
    k2->next = new ListNode(3);

    Solution test;
    resul = test.addTwoNumbers(l1, l2);
    while(resul!= nullptr){
        cout << resul->val << " ";
        resul = resul->next;
    }
    return 0;
}