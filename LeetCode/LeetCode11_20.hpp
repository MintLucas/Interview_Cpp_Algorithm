#ifndef LeetCode11_20_hpp
#define LeetCode11_20_hpp

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <set>
#include <sstream>
#include "BTree.hpp"
#include <unordered_set>
#include "01_ListNode.hpp"
using namespace std;
struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};


//vector<string> wordBreak(string s, unordered_set<string> &dict);

RandomListNode *copyRandomList(RandomListNode *head);
bool wordBreak(string s, unordered_set<string> &dict);
int singleNumber(int A[], int n);
#endif /* LeetCode11_20_hpp */
