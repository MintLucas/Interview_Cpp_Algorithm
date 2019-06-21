#include "BTree.hpp"
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <set>
#include <sstream>
#include <stack>
#include <algorithm>
using namespace std;

//建树，统计节点数，递归方法都用先序依次遍历，建根 再左再右的顺序
void createBiTree(TreeNode* &root) {
    int c;
    cin >> c;
    //需要将空结点赋值为-1，只能先序建树
    if(c == -1) root = NULL;
    else{
        root = new TreeNode(c);
        //void型传引用，也可以赋值->left=返回TNode型
        createBiTree(root->left);
        createBiTree(root->right);
    }
}

//用int* 做遍历指向也可以，遍历便创建节点，若ruturn TNode建树访问建树，root->left=fun(vec,idx);vec也可以全局出来
void createBiTree(TreeNode* &root, vector<int> vec, int& idx) {
    if(vec[idx] == -1) root = NULL;
    else{
        root = new TreeNode(vec[idx]);
        //idx为引用仅能++必须在前
        createBiTree(root->left, vec, ++idx);
        createBiTree(root->right, vec, ++idx);
    }
}


void preOrder(TreeNode* root){
    if(root == NULL) return;
    cout << root->val << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void preOrderUnrec(TreeNode* root){
    if(root == NULL) return;
    TreeNode* cur = root;
    stack<TreeNode*> s;
    
    //还有断点或还有节点没访问则继续
    while(!s.empty() || cur){
        if (cur) {
            cout << cur->val << " ";
            s.push(cur);//进入递归前保存当前断点
            cur = cur->left;//递归遍历左子树
        }
        else{
            //仅起回退的作用，已访问过直接向右递归右子树
            cur = s.top();
            s.pop();
            cur = cur->right;
        }
    }
}

void inOrder(TreeNode* root){
    if(root == NULL) return;
    inOrder(root->left);
    cout << root->val << " ";
    inOrder(root->right);
}

void inOrderUnrec(TreeNode* root){
    if(root == NULL) return;
    stack<TreeNode*> stk;
    while (!stk.empty() || root) {
        //注意不能if(root->left)，遍历当前存入继续遍历
        if(root){
            stk.push(root);
            root = root->left;
            //continue;多此一举,仅if else,if可以换位while
        }
        else{
            
            root = stk.top();
            
            //核心三句，后序需要判断回退是否可以访问
            //即在得到栈顶的回退时判断时从左还是从右子树回退的
            stk.pop();
            cout << root->val << " ";
            //指向右子节点,下一次循环时就会中序遍历右子树
            root = root->right;
        }
    }
}

void postOrder(TreeNode* root){
    if(root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->val << " " ;
}

void postOrderUnrec(TreeNode* root){
    if(root == NULL) return;
    TreeNode* cur = root;
    stack<TreeNode*> stk;
    while (!stk.empty() || cur) {
        if(cur){
            stk.push(cur);
            cur = cur->left;
        }
        else{
            cur = stk.top();
            //第一次从左子树返回
            if (cur->tag == 0) {
                cur->tag = 1;
                cur = cur->right;//去访问右子树
            } else {
                stk.pop();
                cout << cur->val << " " ;
                //结点访问完重置cur指针回退
                cur = NULL;//从右子树返回则遍历完继续回退
            }
        }
    }
}

void postOrderUnrec2(TreeNode* root){
    if(root == NULL) return;
    TreeNode* cur = root;
    TreeNode* from_r = NULL;
    stack<TreeNode*> stk;
    while(!stk.empty() || cur){
        if(cur){
            stk.push(cur);
            cur = cur->left;
        }
        else{
            //else一定是产生回退，判断右方是否能遍历
            cur = stk.top();
            //右方为空不能单纯的转向右，不然死循环
            //去访问右是有条件的：右方必须存在且不是从右回来的
            
            //看能不能访问，即tag==1,or cur->right=from_r
            if(cur->right && cur->right != from_r)
                cur = cur->right;
            else{
                stk.pop();
                cout << cur->val << " ";
                //记录上一次访问的节点
                from_r = cur;
                cur = NULL;
            }
        }
    }
}

stack<TreeNode*> printAncestor(TreeNode* root, int x){
    TreeNode* cur = root, *last_from = NULL;
    stack<TreeNode*> s;
    while (!s.empty() || cur) {
        if(cur){
            s.push(cur);
            cur = cur->left;
        }
        else{
            cur = s.top();
            if(cur->right && cur->right != last_from){
                cur = cur->right;
            }
            else{
                s.pop();
                last_from = cur;
                if(cur->val == x)
                    return s;
                cur = NULL;
            }
        }
        
    }
    return s;
}


void levelOrder(TreeNode* root){
    if(root == NULL) return;
    queue<TreeNode*> que;
    TreeNode* cur = NULL;
    que.push(root);
    while (!que.empty()) {
        cur = que.front();
        que.pop();
        cout << cur->val << " ";
        if(cur->left) que.push(cur->left);
        if(cur->right) que.push(cur->right);
    }
    return;
}

//先序遍历一遍，每个节点判断一次，有不符合的置flag=flase;
//改造一下,不用传入&flag或全局flag来维持判断,用&&的传递性
bool isSortTree(TreeNode* root){
    if(root == NULL) return true;
    int temp = root->val;
    if((root->left && root->left->val > temp) || (root->right && root->right->val < temp                                                          )){
        return false;
    }
//    isSortTree(root->left, flag);
//    isSortTree(root->right, flag);
    return isSortTree(root->left) && isSortTree(root->right);
}

bool isSortTreeUnrec(TreeNode* root){
    if(root == NULL) return true;
    TreeNode* cur = root;
    stack<TreeNode*> s;
    int lastvalue = -1;
    while (!s.empty() || cur) {
        if(cur){
            s.push(cur);
            cur = cur->left;
        }
        else{
            cur = s.top();
            s.pop();
            //第一次时需要更新
            //连续递增，必须相邻两个比较来更新值
            if(lastvalue == -1 || lastvalue < cur->val)
                lastvalue = cur->val;
            else
                return false;
            cur = cur->right;
        }
    }
    return true;
}

bool isCompleteTree(TreeNode* root){
    if(root == NULL) return true;
    TreeNode* cur = root, *temp = NULL;
    queue<TreeNode*> que;
    que.push(cur);
    while (!que.empty()) {
        cur = que.front();
        que.pop();
        if(cur == NULL)
            while (!que.empty()) {
                temp = que.front();
                if(temp) return false;
                que.pop();
            }
        else{
        que.push(cur->left);
        que.push(cur->right);
        }
    }
    return true;
}

int treeDepth(TreeNode* root){
    TreeNode* cur = root;
    queue<TreeNode*> que;
    int depth = 0;
    que.push(cur);
    while (!que.empty()) {
        depth++;
        //每层的节点个数做一个记录，第一层为1
        int size = int(que.size());
        while (size--) {
            cur = que.front();
            que.pop();
            if(cur->left) que.push(cur->left);
            if(cur->right) que.push(cur->right);
        }
    }
    return depth;
}

//销毁cur，仅能后序遍历不然断链
void deleteTreeNode(TreeNode* &root){
    if(root == NULL) return;
    deleteTreeNode(root->left);
    deleteTreeNode(root->right);
    delete root;
    root = NULL;
}

//层序适合用父节点操作子节点，在子节点入队时判断并操纵
void findXandDelete(TreeNode* &root, int x){
    if(root == NULL) return;
    queue<TreeNode*> que;
    TreeNode* cur = root;
    que.push(cur);
    while (!que.empty()) {
        cur = que.front();
        que.pop();
        if(cur->left){
            if(cur->left->val == x){
                deleteTreeNode(cur->left);
                cur->left = NULL;
            }
        else
            que.push(cur->left);
        }
        if(cur->right){
            if(cur->right->val == x){
                deleteTreeNode(root->right);
                cur->right = NULL;
            }
        else
            que.push(cur->right);
        }
    }
    return;
}

void core(TreeNode *root, string &s){
    if(root == NULL){
        s.push_back('#');
        s.push_back(',');
        return;
    }
    //整数作为ascii码存进去,超过128报错要一个一个按char存
    s.push_back(root->val);
    s.push_back(',');
    core(root->left, s);
    core(root->right, s);
}

char* Serialize(TreeNode *root) {
    string s;
    core(root, s);
    char* res = new char[s.length() + 1];
    strcpy(res, s.c_str());
    return res;
}

void dcore(TreeNode* &root, string s, int &len){
    if(len >= s.length()) return;
    if(s[len] == '#'){
        len = len+2;
        root = NULL;
    }
    else{
        root = new TreeNode(s[len]);
        len = len+2;
        dcore(root->left, s, len);
        dcore(root->right, s, len);
    }
}

TreeNode* Deserialize(char *str) {
    string s(str);
    TreeNode *root = NULL;
    int len = 0;
    dcore(root, s, len);
    return root;
}

int count_kth;
void kthcore(TreeNode* pRoot, TreeNode* &res){
    if(pRoot == NULL) return;
    kthcore(pRoot->left, res);
    
    //如果找到res，就不往下递归保证不修改res的值
    if(res) return;
    //无论如何count都要--，否则count-为0便会一直不变
    if (--count_kth == 0) {
        res = pRoot;
        return;
    }
    
    kthcore(pRoot->right, res);
    if(res) return;
}

TreeNode* KthNode(TreeNode* pRoot, int k)
{
    if(pRoot == NULL || k < 1) return NULL;
    TreeNode *res = NULL;
    count_kth = k;
    kthcore(pRoot, res);
    return res;
}

vector<int> PrintFromTopToBottom(TreeNode* root) {
    vector<int> res;
    if(root == NULL) return res;
    queue<TreeNode*> que;
    que.push(root);
    TreeNode *temp = NULL;
    while (!que.empty()) {
        temp = que.front();
        que.pop();
        res.push_back(temp->val);
        if(temp->left) que.push(temp->left);
        if(temp->right) que.push(temp->right);
    }
    return res;
}

bool verifyCore(vector<int> &vec, int l, int r){
    //l==r对应的是叶子结点，l>r对应的是空树，这两种情况都是true
    if(l >= r) return true;
    int i = r;//若用左闭右开，r=size(),
    //这里用的是闭区间，当然你也可以用左闭右开区间
    //[left,i-1]和[i,right-1]
    
    //用i-1来比较早滞,停在不满足条件节点前(倒着走的)
    while(i > l && vec[i - 1] > vec[r]) i--;
    
    //    while(i >= l && vec[i] < vec[r]) i++;
    //    if(i  >= l) return false;
    //遍历vec[j]>vec[r]时需要return false;上面会停止但没有return
    for (int j = i - 1; j>=l; --j) {
        if (vec[j] > vec[r]) {
            return false;
        }
    }
    
    return verifyCore(vec, l, i - 1) && verifyCore(vec, i, r - 1);
}

bool verifyCore2(vector<int> &vec, int l, int r){
    //l==r对应的是叶子结点，l>r对应的是空树，这两种情况都是true
    if(l >= r) return true;
    int i = l;//若用左闭右开，r=size(),
    //这里用的是闭区间，当然你也可以用左闭右开区间
    //[left,i-1]和[i,right-1]
    
    //用i-1来比较早滞,停在不满足条件节点前(倒着走的)
    while(i < r && vec[i] < vec[r]) i++;
    //上面退出时vec[i]>vec[r]or i=r,因此可以从i也可以从j=i+1开始比较
    for (int j = i; j<r; ++j) {
        if (vec[j] < vec[r]) {
            return false;
        }
    }
    
    return verifyCore(vec, l, i - 1) && verifyCore(vec, i, r - 1);
}


bool VerifySquenceOfBST(vector<int> sequence) {
    if(sequence.size() < 1) return false;
    return verifyCore(sequence, 0, int(sequence.size() - 1));
}

vector<vector<int>> res;
vector<int> buf;
vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
    if(root == NULL) return res;
    expectNumber = expectNumber - root->val;
    buf.push_back(root->val);
    if (expectNumber == 0 && root->left == NULL && root->right == NULL) {
        res.push_back(buf);
    }
    FindPath(root->left, expectNumber);
    FindPath(root->right, expectNumber);
    buf.pop_back();
    return res;
}


//int main() {
//    TreeNode* root;
//    vector<int> vec = {9,4,3,-1,-1,8,
//        7,-1,-1,-1,9,-1,-1};
//    int len = 0;
//    createBiTree(root, vec, len);
//    levelOrder(root);
//    TreeNode *res = KthNode(root, 1);
//    string s = "aaa";
//    cout << s.size() << s.length();
//    char * c = new char[100];
//    c = Serialize(root);
//    TreeNode* root2;
//    root2 = Deserialize(c);
//    levelOrder(root2);
//
//
//    return 0;
//}
