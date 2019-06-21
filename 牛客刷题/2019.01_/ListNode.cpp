#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

//注意形参传递，在createList中为pHead开辟空间的时候，main中的head依旧指向NULL，所以要用引用绑定main里的head
//不使用返回值传递而使用参数传递时，注意函数内指针的改变不影响函数外的指针，所以参数类型为指针的指针或指针的引用
//因此要用ListNode** pHead;p= *pHead;此时相当于p==head；
//对链表进行修改时（包括，添加，删除等操作），需要对指针进行修改，头结点要单独拿出来操作，用cur或p来遍历
ListNode* createList(ListNode*& pHead){
    ListNode* tempHead = pHead;
    ListNode* cur = pHead;
    int num = 5,value = 0, temp = 0;
    cout << "请输入链表结点个数num:";
    //cin >> num;
    for(int i = 0; i < num; i++){
        //cin >> temp;
        //调用带参构造函数
        ListNode* newNode = new ListNode(i);
        cur->next = newNode;
        cur = newNode;  
        ListNode* newNod = new ListNode(i);
        cur->next = newNod;
        cur = newNod;  
    }
    //cur->next = NULL;不用多此一举构造函数创造next==NULL
    return tempHead;
}

void printList(ListNode* pHead){
    ListNode* cur = pHead;
    while(cur != NULL){
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << endl;
        
}

void deleteX(ListNode* head, int x){
    if(head == NULL) return;
    deleteX(head->next, x);
    if(head->val == x){
        head->val = 20;
        delete(head);
        head = NULL;
    }
    return;
}

void deleteX_cite(ListNode *head, int x){
    ListNode* p;
    if(head == NULL) return;
    if(head->val == x){
        p = head;
        head = head->next;
        delete(p);
        p = NULL;
        deleteX_cite(head, x);
    }
    else
        deleteX_cite(head->next, x);
}

void delete_mutiX(ListNode* head, int x){
    if(head == NULL) return;
    ListNode* pre = head, *cur = head, *aft = NULL;
    while(cur){
        if(cur->val == x){
            aft = cur->next;
            //只要aft->val==x，就后移，即找删除节点的后一个节点
            //考虑遍历到最后一个结点时，atfer==NULL时访问->val会出错，用短路避免
            if(cur == head){
                head = aft;
                pre = head;
                //加上这句话仅输出头节点后的第一个0
                //pre->next = NULL;
            }
            else
                pre->next = aft;
            cur = aft;
        }
        else{
            pre = cur;
            cur = cur->next;
        }
    }
    printList(head);
    return;
}

int main(){
    //带头节点的链表，在main里创建头节点
    ListNode* head = new ListNode(-1);
    head = createList(head);
    printList(head);
    //传入head->next即传入不带头节点的链表
    delete_mutiX(head->next, 4);
    
}