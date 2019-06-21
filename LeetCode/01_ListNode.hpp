//
//  01_ListNode.hpp
//  LeetCode
//
//  Created by 李志鹏 on 2019/3/17.
//  Copyright © 2019 李志鹏. All rights reserved.
//

#ifndef _1_ListNode_hpp
#define _1_ListNode_hpp

#include <stdio.h>
struct ListNode {
    int val;
    struct ListNode* next;
    ListNode(int x):val(x), next(NULL){}
};

void printList(ListNode* head);
void rPrintList(ListNode* head);
void reverseList(ListNode* &head);

void deleteX(ListNode* &head, int x);

void sortList(ListNode* &head);
void deleteDuplication(ListNode* &head);

void mergeList(ListNode* &head1, ListNode* &head2);
ListNode* mergeTwoList(ListNode *head1, ListNode *head2);
ListNode* intersection(ListNode* head1, ListNode* head2);
ListNode* commonNode(ListNode* head1, ListNode* head2);
ListNode* creatListNode();
int lastKnum(ListNode* head, int k);

bool isSubsequence(ListNode* head1, ListNode* head2);
#endif /* _1_ListNode_hpp */
