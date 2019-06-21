#include "BSortTree.hpp"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <set>
#include <sstream>
#include "BTree.hpp"
#include "01_ListNode.hpp"
#include "Sword_offer.hpp"

BSTree::BSTree(vector<int> vec){
    root = new BSTNode(vec[0]);
    for (int i = 1; i < vec.size(); i++) {
        insertNode(vec[i]);
    }
}

void BSTree::insertNodeUnrec(int x){
    BSTNode *par, *p;
    //默认根节点存在，p遍历par记录上一个，插入par之下即可
    BSTNode *newNode = new BSTNode(x);
    
    p = par = root;
    while (p != NULL) {
        par = p;
        if(x > p->val)
            p = p->right;
        else if(x < p->val)
            p = p->left;
        else if(x == p->val){
            delete newNode;
            return;
        }
    }
    newNode->parent = par;
    if(par->val > newNode->val)
        par->left = newNode;
    else
        par->right = newNode;
}

void BSTree::insertNode(int x){
    if(root)
        insertNodeCore(root, x);
}

void BSTree::insertNodeCore(BSTNode *cur, int x){
    if (x < cur->val) {
        //search模式类似,左子树为空返回否则递归
        //不会递归到null的情况,因为存在才递归否则就返回
        if(cur->left == NULL){
            cur->left = new BSTNode(x);
            cur->left->parent = cur;
        }
        else
            insertNodeCore(cur->left, x);
    }
    else if(x > cur->val){
        if (cur->right == NULL) {
            cur->right = new BSTNode(x);
            cur->right->parent = cur;
        }
        else
            insertNodeCore(cur->right, x);
    }
    
    //x等于当前节点值时，不插入，这里满足条件才new所以不用删除
    return;
}

void BSTree::inOrder(){
    if(root)
        inOrderCore(root);
}

void BSTree::inOrderCore(BSTNode *cur){
    if(cur == NULL) return ;
    inOrderCore(cur->left);
    cout << cur->val << " ";
    inOrderCore(cur->right);
}

//直接对引用操作，由于每次插入时都是在叶结点，所以遍历到空新建节点插入亦可
void BSTinsert(BSTNode *&root, int x){
    if(root == NULL){
        root = new BSTNode(x);
        return;
    }
    if(root->val > x)
        return BSTinsert(root->left, x);
    else if(root->val < x)
        return BSTinsert(root->right, x);
    else
        return;//已经有了就不插入了
}

//递归核心，封装到类的话不用传root参数即可,因为root类私有成员可访问
BSTNode* BSTsearch(BSTNode* root, int x){
    if(root == NULL) return NULL;
    if(root->val == x)
        return root;
    else if(root->val > x)
        return BSTsearch(root->left, x);
    else
        return BSTsearch(root->right, x);
}

//非递归查找，顺着遍历不用栈
BSTNode* BSTsearchUnrec(BSTNode *root, int x){
    if(root == NULL) return NULL;
    while (root != NULL && root->val != x) {
        //root往下走时可以加一句parent=root保存父节点
        if(x < root->val)
            root = root->left;
        else root = root->right;
    }
    return root;//while循环退出root为NULL或root->val=x
}



//int main(){
//    vector<int> vec = {3, 4, 8, 7, 9, 9, 1};
//    class BSTree bst(vec);
//    bst.inOrder();
//    cout << endl;
//
//    //不封装类普通构造方法
//    vector<int> vec2(vec);
//    //指针初始化声明为空，或调用BSTNode的构造函数初始化NULL但值为-1
//    BSTNode* root2 = NULL;
//    for (int i = 0; i < vec2.size(); i++) {
//        BSTinsert(root2, vec2[i]);
//    }
//
//    //static,没类对象外部也能访问
//    BSTree::inOrderCore(root2);
//    BSTNode* searched = BSTsearchUnrec(root2, 8);
//    cout << searched->val;
//}
