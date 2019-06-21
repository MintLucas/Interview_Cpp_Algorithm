//
//  01_ListNode.cpp
//  LeetCode
//
//  Created by 李志鹏 on 2019/3/17.
//  Copyright © 2019 李志鹏. All rights reserved.
//
#include "Sword_offer.hpp"
#include "01_ListNode.hpp"
#include <iostream>
using namespace std;

ListNode* creatListNode(){
    //无头节点，遇0退出
    int value;
    cin >> value;
    ListNode* head = new ListNode(value);
    ListNode* rear = head;
    cin >> value;
    //可以用int n来技术while(1)循环里用break
    while(value){
        ListNode* newNode = new ListNode(value);
        rear->next = newNode;
        rear = newNode;
        cin >> value;
    }
    rear->next = NULL;//链表最后一个节点置空
    return head;
}

ListNode* creatListNode2(){
    int n = 0;
    int value = 0;
    ListNode* head = new ListNode(value);
    ListNode* rear = head;
    while(1){
        cin >> value;
        if(value == 0) break;
        ListNode *newNode = new ListNode(value);
        if(++n == 1){
            head->next = newNode;
            rear = newNode;
        }
        else{
            rear->next = newNode;
            rear = newNode;
        }
    }
    rear->next = NULL;//链表最后一个节点置空
    return head;
}

void printList(ListNode* head){
    while(head){
        cout << head->val << ' ';
        head = head->next;
    }
    cout << endl;
}

void rPrintList(ListNode* head){
    if (head == NULL) {
        return;
    }
    rPrintList(head->next);
    cout << head->val << ' ';
    return;
}

void deleteX(ListNode* &head, int x){
    if(head == NULL) return;
    ListNode* pre = head, *cur = head;
    while(cur){
        if(cur->val == x){
            if(cur == head){
                cur = cur->next;
                head = cur;
                pre = cur;
            }
            else{
                pre->next = cur->next;
                cur = cur->next;
            }
        }
        else{
            pre = cur;
            cur = cur->next;
        }
    }
}

void reverseList(ListNode* &head){
    ListNode* pre = head, *cur = head->next, *aft = NULL;
    head->next = NULL;
    while(cur){
        aft = cur->next;
        cur->next = pre;
        pre = cur;
        cur = aft;
    }
    head = pre;
}

//链表的直接插入排序
void sortList(ListNode* &head){
    ListNode* cur1 = head, *cur2 = head->next;
    ListNode* temp = NULL;//保证不断链
    head = new ListNode(0);
    head->next = cur1;
    cur1->next = NULL;
    cur1 = head;
    while (cur2) {
        temp = cur2->next;
        //找到插入位置，注意要用并用交cur1->next为空时短路
        while(cur1->next != NULL && cur1->next->val >= cur2->val){
            cur1 = cur1->next;
        }
        cur2->next = cur1->next;
        cur1->next = cur2;
        cur2 = temp;
        cur1 = head;
    }
    head = head->next;
}

ListNode* commonNode(ListNode* head1, ListNode* head2){
    ListNode* cur1 = head1, *cur2 = head2;
    int len1=0, len2=0, dis=0;
    while (cur1) {
        len1++;
        cur1 = cur1->next;
    }
    while (cur2) {
        len2++;
        cur2 = cur2->next;
    }
    cur1 = head1;cur2 = head2;
    if (len1 > len2) {
        dis = len1 - len2;
        while(dis--)
            cur1 = cur1->next;
    }
    else{
        dis = len2 - len1;
        while(dis--)
            cur2 = cur2->next;
    }
    while(cur1 != NULL && cur1->val != cur2->val){
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    if (cur1) {
        return cur1;
    }
    return NULL;
}

void deleteDuplication(ListNode* &head){
    ListNode* pre = head, *cur = head, *aft = NULL;
    //也可以新建一个头节点,删除时不用考虑为头的情况,最后return start->next
//    ListNode* start = new ListNode(0);
//    pre = start;
//    start->next = head;

    while(cur)//cur可能等空不能判断cur->next存在
        if(cur->next && cur->val == cur->next->val){
            aft = cur->next;
            //用到Aft->next需先判断其不为空
            while(aft->next && aft->next->val == cur->val)
            //可以将while()里的终止条件在{}加入if break实现
                aft = aft->next;
            if (cur == head) {
                cur = aft->next;
                head = cur;
                pre = cur;
            }
            else{
                pre->next = aft->next;
                cur = aft->next;
            }
        }
        else{
            pre = cur;
            cur = cur->next;
        }
}

void mergeList(ListNode* &head1, ListNode* &head2){
    ListNode* cur1 = head1, *cur2 = head2;
    ListNode* newHead = new ListNode(0);
    
    //cur1已经记录了head1,引用过去即原链表上更改！！
    head1 = newHead;//很关键的一步,head1指到newHead
    
    ListNode* rear = newHead;
    //或||的情况很容易出现错误，一个为空条件也成立👇
    while(cur1 && cur2){
        if(cur1->val < cur2->val){
            rear->next = cur1;
            rear = cur1;
            cur1 = cur1->next;
        }
        else{
            rear->next = cur2;
            rear = cur2;
            cur2 = cur2->next;
        }
    }
    if(cur1)
        rear->next = cur1;
    if(cur2)
        rear->next = cur2;
    head1 = head1->next;
}

ListNode* mergeTwoList(ListNode *head1, ListNode *head2){
    if(head1 == nullptr)
        return head2;
    if(head2 == nullptr)
        return head1;
    if(head1->val <= head2->val){
        //小的往里进，进到最后是最大的，指向大的即可
        head1->next = mergeTwoList(head1->next, head2);
        return head1;
    }
    else{
        head2->next = mergeTwoList(head1, head2->next);
        return head2;
    }
}

ListNode* intersection(ListNode* head1, ListNode* head2){
    ListNode* headNode = new ListNode(0);
    ListNode* cur1 = head1, *cur2 = head2, *rear = headNode;
    while (cur1 && cur2) {
        if (cur1->val == cur2->val) {
            ListNode* temp = new ListNode(cur1->val);
            rear->next = temp;
            rear = temp;
        }
        if (cur1->val < cur2->val) {
            cur1 = cur1->next;
        }
        else
            cur2 = cur2->next;
    }
    headNode = headNode->next;
    return headNode;
}

bool isSubsequence(ListNode* head1, ListNode* head2){
    ListNode* cur1 = head1, *cur2 = head2, *cur11;
    while (cur1) {
        if (cur1->val == cur2->val) {
            cur11 = cur1;
            while (cur11 && cur2 && cur11->val == cur2->val) {
                cur11 = cur11->next;
                cur2 = cur2->next;
                if (cur2 == NULL) {
                    return true;
                }
            }
            cur2 = head2;
            cur1 = cur1->next;
        } else {
            cur1 = cur1->next;
        }
     
    }
    return false;
}

int lastKnum(ListNode* head, int k){
    ListNode* front = head, *cur = head;
    while (k--) {
        front = front->next;
    }
    while (front) {
        front = front->next;
        cur = cur->next;
    }
    return cur->val;
}

//int main(int argc, const char * argv[]) {
////
////    cout << "hello";
//    ListNode* head1 = creatListNode();
//    printList(head1);
//    //ListNode* head2 = creatListNode();
//    //bool whether = isSubsequence(head1, head2);
//    //int lastK = lastKnum(head1, 3);
//    //cout << lastK << endl;
//    return 0;
//}
