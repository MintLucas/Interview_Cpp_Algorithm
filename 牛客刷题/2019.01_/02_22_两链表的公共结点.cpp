struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

class Solution {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        if (pHead1 == NULL || pHead2 == NULL)
            return NULL;
        int len1 = GetLen(pHead1), len2 = GetLen(pHead2);
        ListNode* long_p = NULL,*short_p = NULL;
        int dis = 0;
        
        if(len1 > len2){
            dis = len1 - len2;
            long_p = pHead1;
            short_p = pHead2;
        }
        
        else{
            dis = len2 - len1;
            long_p = pHead2;
            short_p = pHead1;
        }
        for(;dis > 0;dis--)
            long_p = long_p->next;
        while(long_p != short_p){
            if(long_p == NULL)
                return NULL;
            long_p = long_p->next;
            short_p = short_p->next;
        }
        return long_p;
        
    }
    int GetLen(ListNode* pHead){
        if(pHead == NULL)
            return 0;
        int length = 0;
        while(pHead != NULL){
            length++;
            pHead = pHead->next;
        }
        return length;
    }
};

