/*
归并排序
- 归并排序是稳定排序

思路：
    分治
    划分子区间、子区间排序、合并子区间
    
*/
#pragma once


template<typename T>
void merge(vector<T> &vec, int left, int mid, int right){
    //假设new出来一个空数组在空数组里排序
    vector<T> temp(vec);

    int k = 0;
    int cur1 = left, cur2 = mid+1;

    //令人崩溃的大括号...把这里到return全括住了找了半天
    while(cur1 <= mid && cur2 <= right)
        if(vec[cur1] <= vec[cur2])
            temp[k++] = vec[cur1++];
        else
            temp[k++] = vec[cur2++];
    
    while(cur1 <= mid)
        temp[k++] = vec[cur1++];
    while(cur2 <= right)
        temp[k++] = vec[cur2++];

    //将空数组里的值拷贝回原数组注意考虑到右半边原数组下标需要[left+cur1]
    for (cur1 = 0; cur1 < k; cur1++)
        vec[left + cur1] = temp[cur1];

    return;    

}
template<typename T>
void mergeSort(vector<T> &vec, int left, int right){
    if(left >= right)
        return;
    
    //分解原问题为若干子问题
    int mid = left + (right - left)/2;

    //递归求解子问题，若足够小和直接求得
    mergeSort(vec, left, mid);
    mergeSort(vec, mid+1, right);

    //合并子问题的解
    merge(vec, left, mid, right);
}


/*

链表归并

*/


ListNode *findhalf(ListNode *head){
    ListNode *low = head,*fast = head;
    
    //不能仅判断fast->next->next
    while(fast->next && fast->next->next){
        low=low->next;
        fast=fast->next->next;
    }
    return low;
}
ListNode *mergeSort(ListNode *head){
    //归并排序划分到空或仅有一个节点时,list中是l>=时退出
    if(head==nullptr || head->next==nullptr) return head;
    ListNode* hf = findhalf(head);
    
    ListNode* pb = mergeSort(hf->next);
    //先找右，再断链！！
    hf->next=nullptr;
    ListNode* pa = mergeSort(head);
    return merge(pa,pb);
}
ListNode* merge(ListNode *pa,ListNode *pb){
    ListNode dummy(0);
    ListNode *rear=&dummy;//上面结构体,这里取地址,不是new放在堆栈的临时变量,出括号自动消失
    
    //也不用cur1和cur2来遍历
    while(pa && pb){
        if(pa->val < pb->val) {
            rear->next = pa;
            pa = pa->next;
        }
        else{
            rear->next = pb;
            pb = pb->next;
        }
        rear = rear->next;
    }
    if(pa)
        rear->next = pa;
    if(pb)
        rear->next = pb;
    
    return dummy.next;
}