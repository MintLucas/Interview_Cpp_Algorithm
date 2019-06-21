//
//  00_constructTree.cpp
//  LeetCode
//
//  Created by 李志鹏 on 2019/3/17.
//  Copyright © 2019 李志鹏. All rights reserved.
//
#include <vector>
#include <iostream>
using namespace std;

//Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void vinOrder(TreeNode* root){
    if(root == NULL) return;
    vinOrder(root->left);
    cout << root->val << endl;
    vinOrder(root->right);
}

class Solution {
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        if(pre.size() != vin.size() || pre.size() < 1)
            return NULL;
        //error code:之前pre.size（）忘记-1,因为是给的下标范围
        return construct(pre, vin, 0, pre.size() - 1, 0, vin.size() - 1);
    }
    
    //一样的思想，这次才用下标法不需要额外vector的空间，建议和上述代码一一对应加深理解
    TreeNode* construct(vector<int> pre, vector<int> vin, int preL, int preR, int vinL, int vinR){
        //左序列为空或右序列为空停止递归
        if(preL > preR || vinL > vinR) return NULL;
        int key_root, idx_root = 0;
        int lenL, lenR;
        //error code:pre[0]
        key_root = pre[preL];
        TreeNode* root = new TreeNode(key_root);
        
        for(int i = 0; i < pre.size(); i++)
            if(key_root == vin[i]){
                idx_root = i;
                break;
            }
        
//        while(key_root != vin[idx_root])
//            idx_root++;
        
        //高低下标判断易出错，用单一个数来代替
        //error code:lexL = idx_root-preL
        lenL = idx_root - vinL;
        lenR = vinR - idx_root;
        if(lenL)
            //需要左右分别递归，代表的不是左右子树的范围而是单个树分别在前序和中序中的范围
            //先前序范围再中序范围，前序需要中序提供的len来确定范围
            root->left = construct(pre, vin, preL+1, preL+lenL, vinL, vinL+lenL-1);
        else
            root->left = NULL;
        if(lenR)
            //一个从左用左长度加另一个从右用减去又长度
            root->right = construct(pre, vin, preR-lenR+1, preR, vinR-lenR+1, vinR);
        else
            root->right = NULL;
        return root;
        
    }
    
    //递归思想，每次将左右**两棵子树当成新的子树**进行处理。
    //前序的第一个索引就是根节点，在中序数组中找到根节点的位置idx_root，idx_root的左边是左子树，右边是右子树。
    //进而得到中序遍历的左右子树的两个数组vL_vin, vR_vin。前序数组的左子树起点为idx_root+1,同理得到前序遍历的左右子树的数组。
    //对上述前序和中序得到的左右子树的数组分别进行二叉树重建，递归求解，递归一次，返回一次根节点。
    // 直到数组长度为1，说明左右子树只有一个节点，叶节点，二叉树整理完毕，不用递归建树，直接返回该叶节点，递归结束。
    TreeNode* ConstructBinaryTree(vector<int> pre,vector<int> vin){
        if(pre.size() == 0) return NULL;
        int key_root = pre[0];
        int idx_root = 0;
        vector<int> vL_pre, vR_pre, vL_vin, vR_vin;
        TreeNode* root = new TreeNode(key_root);

        while(key_root != vin[idx_root])
            idx_root++;
        
        for(int i = 0; i < idx_root; i++){
            vL_pre.push_back(pre[i + 1]);
            vL_vin.push_back(vin[i]);
        }
        for(int i = idx_root + 1; i < pre.size(); i++){
            vR_pre.push_back(pre[i]);
            vR_vin.push_back(vin[i]);
        }
        root->left = ConstructBinaryTree(vL_pre, vL_vin);
        root->right = ConstructBinaryTree(vR_pre, vR_vin);
        return root;
        
    }
};

//int main(){
//    vector<int> pre = {1,2,4,7,3,5,6,8};
//    vector<int> vin = {4,7,2,1,5,3,8,6};
//    Solution solu;
//    TreeNode* root = solu.reConstructBinaryTree(pre, vin);
//    vinOrder(root);
//    return 0;
//}
