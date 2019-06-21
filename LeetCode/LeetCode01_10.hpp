#ifndef LeetCode01_10_hpp
#define LeetCode01_10_hpp

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

int run(TreeNode *root);
int evalRPN(vector<string> &tokens);
//int maxPoints(vector<Point> &points);
ListNode *findhalf(ListNode *head);
ListNode* merge(ListNode *pa,ListNode *pb);
ListNode *mergeSort(ListNode *head);
ListNode *insertionSortList(ListNode *head);
vector<int> postorderTraversal(TreeNode *root);
vector<int> preorderTraversal(TreeNode *root);
void reorderList(ListNode *head);
ListNode *detectCycle(ListNode *head);
bool hasCycle(ListNode *head);
#endif /* LeetCode01_10_hpp */
