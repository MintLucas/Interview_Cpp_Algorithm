#ifndef BTree_hpp
#define BTree_hpp

#include <stdio.h>
#include <vector>
#include <queue>
#include <string>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    int tag;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : tag(0), left(NULL), right(NULL) {};
    TreeNode(int x) : val(x), tag(0), left(NULL), right(NULL) {};
};

void createBiTree(TreeNode* &root);
void createBiTree(TreeNode* &root, vector<int> vec, int& idx);
void preOrder(TreeNode* root);
void inOrder(TreeNode* root);
void postOrder(TreeNode* root);
void postOrderUnrec(TreeNode* root);
void postOrderUnrec2(TreeNode* root);
stack<TreeNode*> printAncestor(TreeNode* root, int x);
void levelOrder(TreeNode* root);
bool isSortTree(TreeNode* root);
char* Serialize(TreeNode *root);
TreeNode* Deserialize(char *str);
vector<vector<int> > FindPath(TreeNode* root,int expectNumber);
#endif /* BTree_hpp */
