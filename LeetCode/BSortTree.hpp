#ifndef BSortTree_hpp
#define BSortTree_hpp

#include "01_ListNode.hpp"
#include "BTree.hpp"
#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

class BSTNode
{
public:
    int val;
    BSTNode *parent;
    BSTNode *left;
    BSTNode *right;
    BSTNode() : val(-1), parent(NULL), left(NULL), right(NULL) {};
    BSTNode(int x) : val(x), parent(NULL), left(NULL), right(NULL) {};
};

class BSTree
{
public:
    BSTree(vector<int> vec);
    //封装性考虑,root私有成员变量,即不给外部控制root仅传入要插入的节点值,但递归需要cur来传递遍历,因此核心函数私有封装
    void insertNode(int x);//调用递归实现插入
    
    //非递归,root默认已构造函数create过
    void insertNodeUnrec(int x);
    
    //同理，递归调用需要core,利用cur=seach(x),直接删除cur即可
    BSTNode* searchNode(int x);

    void deleteNode(int x);
    
    void inOrder();
    
    void static inOrderCore(BSTNode *cur);
private:
    void insertNodeCore(BSTNode *cur, int x);//递归实现
    BSTNode* searchNodeCore(BSTNode *cur, int x);
    
    void deleteNodeCore(BSTNode *cur);
    
    
    
private:
    //类中的静态成员或方法不属于类实例，属于类本身且在所有类实例间共享
    //static means: hidden in modols and persistence
    BSTNode *root;
};

void BSTinsert(BSTNode *&root, int x);
BSTNode* BSTsearch(BSTNode *root, int x);
BSTNode* BSTsearchUnrec(BSTNode *root, int x);
#endif /* BSortTree_hpp */
