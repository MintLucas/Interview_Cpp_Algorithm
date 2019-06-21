/*
�鲢����
- �鲢�������ȶ�����

˼·��
    ����
    ���������䡢���������򡢺ϲ�������
    
*/
#pragma once


template<typename T>
void merge(vector<T> &vec, int left, int mid, int right){
    //����new����һ���������ڿ�����������
    vector<T> temp(vec);

    int k = 0;
    int cur1 = left, cur2 = mid+1;

    //���˱����Ĵ�����...�����ﵽreturnȫ��ס�����˰���
    while(cur1 <= mid && cur2 <= right)
        if(vec[cur1] <= vec[cur2])
            temp[k++] = vec[cur1++];
        else
            temp[k++] = vec[cur2++];
    
    while(cur1 <= mid)
        temp[k++] = vec[cur1++];
    while(cur2 <= right)
        temp[k++] = vec[cur2++];

    //�����������ֵ������ԭ����ע�⿼�ǵ��Ұ��ԭ�����±���Ҫ[left+cur1]
    for (cur1 = 0; cur1 < k; cur1++)
        vec[left + cur1] = temp[cur1];

    return;    

}
template<typename T>
void mergeSort(vector<T> &vec, int left, int right){
    if(left >= right)
        return;
    
    //�ֽ�ԭ����Ϊ����������
    int mid = left + (right - left)/2;

    //�ݹ���������⣬���㹻С��ֱ�����
    mergeSort(vec, left, mid);
    mergeSort(vec, mid+1, right);

    //�ϲ�������Ľ�
    merge(vec, left, mid, right);
}


/*

����鲢

*/


ListNode *findhalf(ListNode *head){
    ListNode *low = head,*fast = head;
    
    //���ܽ��ж�fast->next->next
    while(fast->next && fast->next->next){
        low=low->next;
        fast=fast->next->next;
    }
    return low;
}
ListNode *mergeSort(ListNode *head){
    //�鲢���򻮷ֵ��ջ����һ���ڵ�ʱ,list����l>=ʱ�˳�
    if(head==nullptr || head->next==nullptr) return head;
    ListNode* hf = findhalf(head);
    
    ListNode* pb = mergeSort(hf->next);
    //�����ң��ٶ�������
    hf->next=nullptr;
    ListNode* pa = mergeSort(head);
    return merge(pa,pb);
}
ListNode* merge(ListNode *pa,ListNode *pb){
    ListNode dummy(0);
    ListNode *rear=&dummy;//����ṹ��,����ȡ��ַ,����new���ڶ�ջ����ʱ����,�������Զ���ʧ
    
    //Ҳ����cur1��cur2������
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