#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        if(pHead == NULL) return NULL;
        ListNode* cur = pHead;
        ListNode *front = NULL, *pnext = NULL;
        
        while(cur != NULL){
            if(cur->next != NULL && cur->next->val == cur->val){
                pnext = cur->next;
                while(pnext->next != NULL && pnext->next->val == cur->val)
                    pnext = pnext->next;
                if(cur == pHead)
                    pHead = pnext->next;
                front->next = pnext->next;
                cur = pnext->next;
            }
            else{
                front = cur;
                cur = cur->next;
            }
        }
        return pHead;
    }
};

int main(){
    Solution s;
    s.deleteDuplication

}
