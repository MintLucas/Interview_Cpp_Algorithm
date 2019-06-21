//
//  Sword_offer.hpp
//  LeetCode
//
//  Created by 李志鹏 on 2019/3/24.
//  Copyright © 2019 李志鹏. All rights reserved.
//

#ifndef Sword_offer_hpp
#define Sword_offer_hpp
#include "01_ListNode.hpp"
#include "BTree.hpp"
#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

int findSingleAlphabat(string s);
string deleteSubChar(const string &s1, const string &s2);
void deleteStrDuplication(string &str);
bool Anagram(const string &s1, const string &s2);

int inversePairs(vector<int> data);

void FindNumsAppearOnce(vector<int> data,int* num1,int *num2);
vector<vector<int> > FindContinuousSequence(int sum);
vector<int> FindNumbersWithSum(vector<int> array,int sum);
string LeftRotateString(string str, int n);
void strReverse(string &str);
string ReverseSentence(string str);
bool IsContinuous( vector<int> numbers );
int LastRemaining_Solution(int n, int m);
int Sum_Solution(int n);
int StrToInt(string str);
//ListNode* EntryNodeOfLoop(ListNode* pHead);
vector<vector<int> > Print(TreeNode* pRoot);


#endif /* Sword_offer_hpp */
