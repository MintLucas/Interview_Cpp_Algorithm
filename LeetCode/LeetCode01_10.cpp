#include "LeetCode01_10.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <set>
#include <sstream>
#include "BTree.hpp"
#include "01_ListNode.hpp"

int run(TreeNode *root) {
    if(root == NULL) return 0;
    queue<TreeNode*> que;
    TreeNode* cur = NULL;
    int depth = 0, width = 0;
    que.push(root);
    while (!que.empty()) {
        width = int(que.size());
        depth++;
        while (width--) {
            cur = que.front();
            que.pop();
            if (cur->left == NULL && cur->right == NULL) {
                return depth;
            }
            if(cur->left) que.push(cur->left);
            if(cur->right) que.push(cur->right);
        }
    }
    return depth;
}

int evalRPN(vector<string> &tokens) {
    if(tokens.empty()) return 0;
    stack<int> stk;
    int num1 = 0, num2 = 0, res = 0;
    for (int i = 0; i < tokens.size(); i++) {
        string s = tokens[i];
        if (s == "+" || s == "-" || s == "*" || s == "/") {
            num2 = stk.top();
            stk.pop();
            num1 = stk.top();
            stk.pop();
            if(s == "+") res = num1+num2;
            if(s == "-") res = num1-num2;
            if(s == "*") res = num1*num2;
            if(s == "/") res = num1/num2;
            stk.push(res);
        }
        else{
            stk.push(stoi(s));
        }
    }
    return stk.top();
}

//int maxPoints(vector<Point> &points) {
//
//}

ListNode *findhalf(ListNode *head){
    ListNode *low = head,*fast = head;
    
    //不能仅判断fast->next->next
    while(fast->next && fast->next->next){
        low=low->next;
        fast=fast->next->next;
    }
    return low;
}
ListNode *mergeSort(ListNode *head){
    //归并排序划分到空或仅有一个节点时,list中是l>=时退出
    if(head==nullptr || head->next==nullptr) return head;
    ListNode* hf = findhalf(head);
    
    //最后一步pb = 1,2,9
    ListNode* pb = mergeSort(hf->next);
    //先找右，再断链！！
    hf->next=nullptr;
    //pa = 3,4,7,8
    //head还指向pa,如果不接收return的新head则仅输出head段的链表
    ListNode* pa = mergeSort(head);
    
    return merge(pa,pb);//经过merge变为78和9链接
}
ListNode* merge(ListNode *pa,ListNode *pb){
    ListNode dummy(0);
    ListNode *rear=&dummy;//上面结构体,这里取地址,不是new放在堆栈的临时变量,出括号自动消失
    
    //也不用cur1和cur2来遍历
    while(pa && pb){
        if(pa->val < pb->val) {
            rear->next = pa;
            pa = pa->next;
        }
        else{
            rear->next = pb;
            pb = pb->next;
        }
        rear = rear->next;
    }
    if(pa)
        rear->next = pa;
    if(pb)
        rear->next = pb;
    
    return dummy.next;
}

ListNode *insertionSortList(ListNode *head) {
    if(head == NULL || head->next == NULL) return head;
    ListNode* origin = new ListNode(-1);
    origin->next = head;
    ListNode *cur1 = origin, *cur2 = head->next, *post = NULL;
    head->next = NULL;
    while (cur2) {
        post = cur2->next;
        cur1 = origin;
        while (cur1->next != NULL && cur1->next->val <= cur2->val) {
            cur1 = cur1->next;
        }
        cur2->next = cur1->next;
        cur1->next = cur2;
        cur2 = post;
    }
    return origin->next;
}

vector<int> postorderTraversal(TreeNode *root) {
    vector<int> res;
    if(root == NULL) return res;
    stack<TreeNode*> stk;
    TreeNode *cur = root, *from_last = NULL;
    while (cur || !stk.empty()) {
        if (cur) {
            stk.push(cur);
            cur = cur->left;
        }
        else{
            cur = stk.top();
            //cur->right不存在时也可直接访问当前
            if (cur->right && cur->right != from_last)
            {
                cur = cur->right;
            }
            else{
                stk.pop();
                from_last = cur;//记得更新
                res.push_back(cur->val);
                cur = NULL;
            }
        }
    }
    return res;
}

vector<int> preorderTraversal(TreeNode *root){
    vector<int> res;
    if(root == NULL) return res;
    stack<TreeNode*> stk;
    TreeNode* cur = root;
    while (cur || !stk.empty()) {
        if(cur){
            res.push_back(cur->val);
            stk.push(cur);
            cur = cur->left;
        }
        else{
            cur = stk.top();
            stk.pop();
            cur = cur->right;
        }
    }
    return res;
}

void reorderList2(ListNode *head){
    if(head == NULL) return;
    ListNode *mid = findhalf(head);
    ListNode *head2 = mid->next;
    mid->next = NULL;
    reverseList(head2);
    ListNode *cur1 = head, *aft1 = NULL, *aft2 = NULL;
    while (head2) {
        aft1 = cur1->next;
        aft2 = head2->next;
        head2->next = cur1->next;
        cur1->next = head2;
        head2 = aft2;
        cur1 = aft1;
    }
    return;
}

void reorderList(ListNode *head){
    if(head == NULL) return ;
    ListNode *fast = head, *low = head;
    while (fast->next && fast->next->next) {
        low = low->next;
        fast = fast->next->next;
    }
    ListNode *head2 = low->next;
    
    //断链加逆置
    low->next = NULL;
    ListNode *cur2 = head2, *aft2 = NULL;
    while (cur2) {
        aft2 = cur2->next;
        cur2->next = low->next;
        low->next = cur2;
        cur2 = aft2;
    }
    
    ListNode *cur1 = head, *aft1 = NULL;
    //这里head2已经逆转,以前的头节点现在是尾节点,因此cur2!=head2
    cur2 = low->next;
    
    //且两个链表合并时链表1的尾不能链接链表2的头,不断开会1的尾会指向插入1的2的头然后变循环链表
    low->next = NULL;
    
    while (cur2) {
        aft2 = cur2->next;
        aft1 = cur1->next;
        cur2->next = cur1->next;
        cur1->next = cur2;
        cur1 = aft1;
        cur2 = aft2;
    }
    
}

ListNode *detectCycle(ListNode *head){
    if(head == NULL) return head;
    ListNode *fast = head, *low = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        low = low->next;
        if(fast == low){
            fast = head;
            while (fast != low) {
                fast = fast->next;
                low = low->next;
            }
            return low;
        }
    }
    return NULL;
}

bool hasCycle(ListNode *head){
    if(head == NULL) return false;
    ListNode *fast = head, *low = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        low = low->next;
        if(fast == low){
            return true;
        }
    }
    return false;
}



//int main(){
//    ListNode *head = creatListNode();
//    printList(head);
//    reorderList2(head);
//    printList(head);
    
//    TreeNode* root;
//    vector<int> vec = {9,4,3,-1,-1,8,
//        7,-1,-1,-1,10,-1,-1};
//    int len = 0;
//    createBiTree(root, vec, len);
//    levelOrder(root);
//    vector<int> res = postorderTraversal(root);
//    cout << res[0] << endl;
//    return 0;
//}
