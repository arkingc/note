#include <iostream>

using namespace std;

struct node{
    node() = default;
    node(int v) : val(v) {}

    int val = 0;
    node *next = NULL;
    node *prev = NULL;
};

/********************************************************************
 *  双链表节点删除（假设链表的节点使用动态内存）
 ********************************************************************/
void deletenode(node **head, node *n){
    if(!head || !n)  return;

    if(*head == n){//1.删除头节点
        //更新头节点
        *head = n->next;
        if(n->next){//链表中不只1个节点
            n->next->prev = NULL;
            n->next = NULL;
        }
    }
    else if(!n->next){//2.删除尾节点
        n->prev->next = NULL;
        n->prev = NULL;
    }
    else{//3.删除中间节点
        n->prev->next = n->next;
        n->next->prev = n->prev;
        n->prev = NULL;
        n->next = NULL;
    }

    delete n;
}


//打印链表函数
void printlist(node *head);

int main()
{
    node *n1 = new node(1);
    node *n2 = new node(2);
    node *n3 = new node(3);

    n1->next = n2;
    n2->next = n3;
    n2->prev = n1;
    n3->prev = n2;

    node *head = n1;        

    printlist(head);        //list : 1->2->3

    deletenode(&head,n2);   //删除中间节点，返回后head指针不变
    printlist(head);        //list : 1->3

    deletenode(&head,n3);   //删除尾节点，返回后head指针不变
    printlist(head);        //list : 1

    deletenode(&head,n1);   //删除唯一的节点，返回后head为NULL
    printlist(head);        //list :

    return 0;
}

void printlist(node *head){
    cout << "list : ";
    while(head){
        if(!head->next)
            cout << head->val << endl;
        else
            cout << head->val << "->";
        head = head->next;
    }
}