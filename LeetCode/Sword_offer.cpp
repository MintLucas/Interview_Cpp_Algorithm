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
#include "Sword_offer.hpp"

using namespace std;

int findSingleAlphabat(string s){
    int array[256] = {0};
    //这里不考虑大小即没有除余，有限的key,key直接当地址来索引
    //标准hash存自然数无限长度，关键字除余映射到地址
    //地址即数组下标，地址中存放出现次数
    for (int i = 0; i < s.size(); i++) {
        array[s[i]]++;
    }
    for (int i = 0; i < s.size(); i++) {
        if(array[s[i]] == 1)
            return i;
    }
    return -1;
}

string deleteSubChar(const string &s1, const string &s2){
    string result;
    int hash[256] = {0};
    for (size_t i = 0; i < s2.size(); i++)
        hash[s2[i]] = 1;
    
    for (size_t i = 0; i < s1.size(); i++)
        if(hash[s1[i]] == 0) result.push_back(s1[i]);
    
    return result;
}

void vecdeleteDuplication(vector<int> &array){
    size_t size = array.size();
    int count = 0;
    vector<int> hash(size, -1);
    
    for (int i = 0; i < size; i++)
        if(hash[array[i] % size] == -1){
            //hash表里取值任意，可以取简单的数量，区分非初始值即可
            hash[array[i] % size] = array[i];
            array[count++] = array[i];
        }
    //在原array操作；也可以新建一个vector在后面添加,return vec
    array.resize(count);
}

void deleteStrDuplication(string &str){
    vector<int> temp(str.size());
    size_t i = 0;
    for (i = 0; i < str.size(); i++) {
        temp[i] = str[i] - 'a';
    }
    vecdeleteDuplication(temp);
    
    for (i = 0; i < temp.size(); i++) {
        str[i] = temp[i] + 'a';
    }
    str.erase(str.begin() + temp.size(), str.end());
    return;
}

bool Anagram(const string &s1, const string &s2){
    //字符串的hash用静态数组即可
    int hash[256] = {0};
    for (int i = 0; i <s1.size(); i++)
        hash[s1[i]]++;
    
    for (int i = 0; i < s2.size(); i++)
        hash[s2[i]]--;
    
    for(int i = 0; i < 256; i++)
        if(hash[i] != 0) return false;
    return true;
}

int inversePairs(vector<int> data){
    int count = 0;
    for (int i = 0, j; i < data.size(); i++) {
        for (j = int(data.size() - 1); j > i; j--) {
            if(data[j] < data[i])
                count++;
        }
    }
    return count;
}

//vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
//    //两个放全局
//    vector<vector<int>> res;
//    vector<int> buf;
//
//    if(root == NULL) return res;
//    expectNumber = expectNumber - root->val;
//    buf.push_back(root->val);
//    if (expectNumber == 0 && root->left == NULL && root->right == NULL) {
//        res.push_back(buf);
//    }
//    FindPath(root->left, expectNumber);
//    FindPath(root->right, expectNumber);
//    buf.pop_back();
//    return res;
//}

void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
    size_t size = data.size();
    vector<int> hash(size, 0);
    for (int i = 0; i < size; i++) {
        int idx = data[i] % size;
        if(hash[idx]) hash[idx]--;
        else hash[idx]++;
    }
    int temp[2] = {0};
    int count = 0;
    for (int i = 0; i < size; i++) {
        int idx = data[i] % size;
        if(hash[idx] == 1){
            temp[count++] = data[i];
        }
    }
    static_cast<void>(*num1 = temp[0]), *num2 = temp[1];
}

vector<vector<int> > FindContinuousSequence(int sum){
    vector<int> natural(sum);
    for (int i = 0; i < sum; i++) {
        natural[i] = i + 1;
    }
    int total = 0;
    vector<vector<int>> result;
    for (int i = 0; i < sum/2; i++) {
        int begin = i, end = i, cur = i;
        total = 0;
        vector<int> temp;
        while (total < sum) {
            total += natural[cur++];
            if (total == sum) {
                end = cur;
                while(begin < end)
                    temp.push_back(natural[begin++]);
                result.push_back(temp);
                temp.clear();
                break;
            }
        }
    }
    return result;
}

vector<int> FindNumbersWithSum(vector<int> array,int sum) {
    vector<int> result;
    int low = 0, high = int(array.size() - 1), cursum = 0;
    while (low < high) {
        cursum = array[low] + array[high];
        //找到及时保存退出，最外层积即最小
        if(cursum == sum){
            result.push_back(array[low]);
            result.push_back(array[high]);
            break;
        }
        if(cursum < sum) low++;
        else high--;
    }
    return result;
}

void strReverse(string &str, int low, int high) {
    while(low < high)
        swap(str[low++], str[high--]);
    return;
}

string LeftRotateString(string str, int n) {
    //注意判断空字符串和n>字符串长度的情况
    if(str.empty()) return str;
    n = n % str.size();
    
    string s1 = str.substr(n);
    string s2 = str.substr(0, n);
    string result = s1 + s2;
    return result;
}

string ReverseSentence(string str) {
    if(str.empty() || str == " ") return str;
    vector<string> vec;
    string temp;
    stringstream input(str);
    while (input >> temp) {
        vec.push_back(temp);
    }
    string result;
    //这步可以从前往后，vec[i]+result,每次在前添加
    for (int i = int(vec.size() - 1); i >= 0; i--) {
        result = result + vec[i] + ' ';
    }
    result.pop_back();
    return result;
}
string ReverseSentence1(string str) {
    string result = "", temp = "";
    for(size_t i = 0; i < str.size(); i++)
        if(str[i] != ' ') temp.push_back(str[i]);
        else{
            result = " " + temp + result;
            temp = "";
        }
    if(temp.size()) result = temp + result;
    return result;
}

bool IsContinuous( vector<int> numbers ) {
    if(numbers.size() < 5) return false;
    int count = 0;
    sort(numbers.begin(), numbers.end());
    for (size_t i = 0; i < 4; i++) {
        if(numbers[i] == 0) {
            count++;
            continue;
        }
        if(numbers[i+1] == numbers[i]) return false;
        else count -= numbers[i+1] - numbers[i] - 1;
    }
    return count >= 0;
}

int LastRemaining_Solution(int n, int m){
    vector<int> vec(n, 1);
//    for (int i = 0; i < vec.size(); i++) {
//        vec[i] = i;
//    }
    int step = 0, i = -1, count = n;
    
    //循环跳出条件混乱,vec[i]置0即删除,删除时用count--来模拟数组减少
    while (count > 1) {
        i = (i + 1) % n;
        if(vec[i] == 1){
            step++;
        }
        if(step == m){
            step = 0;
            vec[i] = 0;
            count--;
        }
    }
    for(int i = 0; i < vec.size(); i++)
        if(vec[i] == 1) return i;
    return step;
}
    
    
int Sum_Solution(int n) {
    int res = n;
    res && (res += Sum_Solution(n - 1));
    return res;
}

int StrToInt(string str) {
    if (str.size() < 1)
        return 0;
    int res = 0;
    int cur = 0;
    int flag = 1;
    
    //****第一位在循环外判断，flag和cur分开修改
    if(str[cur] == '-') flag = -1;
    if(str[cur] == '+' || str[cur] == '-') cur++;
    
    while (str[cur] != '\0') {
        if(str[cur] > '9' || str[cur] < '0')
            return 0;
        //从前往后遍历，新加入的最前方自动*基底
        //若从后往前，更新temp=temp*10;
        res += (res << 1) + (res << 3) +(str[cur++] & 0xf);
    }
    return flag*res;
}

ListNode* EntryNodeOfLoop2(ListNode* pHead){
    if(pHead == NULL) return NULL;
    ListNode* low = pHead, *fast = pHead;
    while (low->next != NULL || fast->next != NULL) {
        low = low->next;
        fast = fast->next->next;
        if (low == fast) {
            fast = pHead;
            while(low != fast){
                low = low->next;
                fast = fast->next;
            }
            return low;
        }
    }
    return NULL;
}

ListNode* EntryNodeOfLoop1(ListNode* pHead)
{
    if(pHead == NULL || pHead->next == NULL)
        return NULL;
    
    //slow和Fast不能初始化为头节点,不然直接跳出
    ListNode* fast = pHead->next->next;
    ListNode* slow = pHead->next;
    
    //第一次相遇时2low = fast
    while(slow != fast)
    {
        if(slow == NULL || fast == NULL)
            return NULL;
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = pHead;
    while(slow != fast){
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
    
}

vector<vector<int> > Print(TreeNode* pRoot) {
    vector<vector<int>> res;
    if(pRoot == NULL) return res;
    TreeNode* cur = pRoot;
    int size = 0, idx = 0;
    queue<TreeNode*> que;
    que.push(cur);
    while(!que.empty()){
        size = int(que.size());
        vector<int> temp;
        
        while(size--){
            cur = que.front();
            que.pop();
            if(idx % 2 == 0)
                temp.push_back(cur->val);
            else
                temp.insert(temp.begin(), cur->val);
            if(cur->left) que.push(cur->left);
            if(cur->right) que.push(cur->right);
            
        }
        idx++;
        res.push_back(temp);
    }

    return res;
    
}

vector<vector<int> > Print2(TreeNode* pRoot) {
    vector<vector<int>> res;
    if(pRoot == NULL) return res;
    TreeNode* cur = pRoot;
    int size = 0, idx = 0;
    queue<TreeNode*> que;
    que.push(cur);
    while(!que.empty()){
        size = int(que.size());
        //vecrot没push之前不能下标索引
        vector<int> temp;
        idx++;
        while(size--){
            cur = que.front();
            que.pop();
            temp.push_back(cur->val);
            if(cur->left) que.push(cur->left);
            if(cur->right) que.push(cur->right);
        }
        res.push_back(temp);
        
    }
    
    return res;
}
//TreeLinkNode* GetNext(TreeLinkNode* pNode)
//{
//    if(pNode == NULL) return NULL;
//    if(pNode->left == NULL && pNode->right == NULL)
//        return pNode;
//    else if (pNode->right){
//        TreeLinkNode* temp = pNode->right;
//        while (temp->left)
//            temp = temp->left;
//        return temp;
//    }
//    else{
//        TreeLinkNode* temp = pNode->next;
//        while (temp == temp->next->left) {
//            temp = temp->next;
//        }
//        return temp;
//    }
//}

//int main(){
//    TreeNode* root;
//    vector<int> vec = {6,2,1,-1,-1,4,
//        15,-1,-1,-1,8,-1,-1};
//    int len = 0;
//    createBiTree(root, vec, len);
//    vector<vector<int>> res = Print(root);
//    levelOrder(root);
//    
//}

class Solution {
public:
    bool isSymmetrical(TreeNode* pRoot)
    {
        if(pRoot == NULL || (pRoot->left == NULL && pRoot->right == NULL))
            return true;
        if((pRoot->left && pRoot->right == NULL) || (pRoot->left == NULL && pRoot->right))
            return false;
        if(pRoot->left->val == pRoot->right->val)
            return isSymmetrical(pRoot->left) && isSymmetrical(pRoot->right);
        return false;
    }
};
