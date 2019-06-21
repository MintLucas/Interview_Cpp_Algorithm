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
#include "LeetCode11_20.hpp"
#include <unordered_set>
using namespace std;

RandomListNode *createRandomList(){
    int n;
    cin >> n;
    RandomListNode *head = new RandomListNode(n);
    RandomListNode *rear = head;
    cin >> n;
    while (n) {
        RandomListNode *newNode = new RandomListNode(n);
        rear->next = newNode;
        rear = newNode;
        cin >> n;
    }
    return head;
}

//s ="catsanddog",
//dict =["cat", "cats", "and", "sand", "dog"].
//A solution is["cats and dog", "cat sand dog"].
//vector<string> wordBreak(string s, unordered_set<string> &dict){
//    vector<string> res;
//    if(s.size() < 1) return res;
//
//
//}


RandomListNode *copyRandomList(RandomListNode *head){
    if(head == NULL) return head;
    //1、原地拷贝
    RandomListNode *cur1 = head, *aft1 = NULL;
    while (cur1) {
        aft1 = cur1->next;
        RandomListNode *copyNode = new RandomListNode(cur1->label);
        copyNode->next = cur1->next;
        cur1->next = copyNode;
        cur1 = aft1;
    }
    
    //2、深层拷贝random指针
    cur1 = head;
    RandomListNode *cur2 = cur1->next, *aft2 = NULL;
    while (cur1) {
        aft1 = cur1->next->next;
        if(aft1)
            aft2 = aft1->next;
        else
            aft2 = NULL;
        if(cur1->random)
            cur2->random = cur1->random->next;
        else
            cur2->random = NULL;
        cur1 = aft1;
        cur2 = aft2;
        
    }
    
    //3.两链表分离
    cur1 = head;
    cur2 = head->next;
    RandomListNode *head2 = cur2;
    while (cur1) {
        aft1 = cur1->next->next;
        if(aft1)
            aft2 = aft1->next;
        else
            aft2 = NULL;
        cur1->next = aft1;
        cur2->next = aft2;
        cur1 = aft1;
        cur2 = aft2;
    }
    return head2;
}

bool wordBreak(string s, unordered_set<string> &dict){
    vector<bool> dp(s.length() + 1, false);
    dp[0] = true;
    for (int i = 1; i <=s.length(); i++) {
        for (int j = 0; j < i; j++) {
            //f(i) = f(j) && f(j+1,i); 0 <= j < i;
            //左闭右开
            if(dp[j] && dict.find(s.substr(j,i)) != dict.end()){
                dp[i] = true;
                break;
            }
        }
    }
    return dp[s.length()];
    
}


int singleNumber(int A[], int n){
    if(n < 1) return -1;
    int ones = 0;
    int twos = 0;
    int threes = 0;
    //用一个数记录每个bit出现的次数,如果一个bit出现两次twos为那个数
    for (int i = 0; i < n ; ++i) {
        //或操作相当于加法,前提是出现过ones才继续操作
        twos = twos | (ones & A[i]);
        //出现过ones前面就会把twos置1所以这里把ones置0
        ones = ones ^ A[i];
        
        //下一题将这一句注释,threes会等于ones影响到ones
        threes = ones & twos;
        //当threes=1 ones*0置位
        ones = ones & ~threes;
        twos = twos & ~threes;
    }
    return ones;
}

int maxProfit1(vector<int> &prices) {
    
    if(prices.size() < 1) return 0;
    
    int min_num = prices[0], max_num = 0;
    
    ////贪心算法，从左往右遍历向量，遇到当前最小值，则保存，
    //如果不是最小值，则计算它到最小值的距离，保存为最大利润
    for(int i = 0; i < prices.size(); ++i){
        min_num = min(prices[i], min_num);
        //在最小值之前计算最大值
        max_num = max(max_num, prices[i] - min_num);
    }
    return max_num;
    
}

int maxProfit(vector<int> &prices) {
    if(prices.size() < 1) return 0;
    int min1 = prices[0], min2 = prices[0];
    int max1 = 0, max2 = 0;
    for (int i = 1; i < prices.size(); ++i) {
        if(prices[i] < min1){
            min2 = min1;
            min1 = prices[i];
        }
        if(prices[i] - min1 > max1){
            max2 = max1;
            max1 = prices[i] - min1;
        }
    }
    return max1 + max2;
    
}

int lengthOfLastWord(const char* s) {
    if(strlen(s) < 1) return 0;
    int count = 0, tail = strlen(s) - 1;
    //考虑末尾是空格的情况，遍历到第一个不是空格的字符为真正的末尾
    while(tail >= 0 && s[tail] == ' ') tail--;
    while(tail >= 0 && s[tail] != ' '){
        count++;
        tail--;
    }
    return count;
}

bool wordBreak2(string s, unordered_set<string> &dict){
    vector<bool> dp(s.size()+1);
    dp[0] = true;
    //s[0...j)
    //只需要0到j判断整串是否满足，故不用双层循环遍历
    for (auto j = 1; j <= s.size(); ++j) {
        //f(j) = f(k) && f(k,j-k);
        //k表示分割位置，从s[0,0)即一个都不切，到s[0,s.size)全切
        for (auto k = 0; k < j; ++k) {
            if(dp[k] && dict.find(s.substr(k, j - k)) != dict.end()){
                dp[j] = true;
                break;
            }
        }
    }
    return dp[s.size()];
}
//
//int main(){
//    string s = "leetcode";
//    unordered_set<string> set = {"leet", "code"};
//    bool flag = wordBreak2(s, set);
//    cout << flag;
//}
