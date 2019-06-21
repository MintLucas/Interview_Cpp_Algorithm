// 思路1：分治算法，基于两个排序链表的合并，两两合并后继续合并，每一轮复杂度o(n),n为总节点个数，T(n) = 2T(n/2) + o(n),迭代次数为lg(k),因此复杂度为o(nlgk)
```cpp
class Solution {
public:
//注意这里是用递归合并的
ListNode* mergeTwoList(ListNode *head1, ListNode *head2){
    if(head1 == nullptr)
        return head2;
    if(head2 == nullptr)
        return head1;
    if(head1->val <= head2->val){
        //小的往里进，进到最后是最大的，指向大的即可
        head1->next = mergeTwoList(head1->next, head2);
        return head1;
    }
    else{
        head2->next = mergeTwoList(head1, head2->next);
        return head2;
    }
}

    
ListNode* mergeKLists(vector<ListNode*>& lists) {
    if(lists.empty())
        return nullptr;
    
    while(lists.size() > 1){
        lists.push_back(mergeTwoList(lists[0], lists[1]));
        lists.erase(lists.begin());
        lists.erase(lists.begin());
        
    }
    return lists.front();
}
```

思路2：使用堆（默认最大堆，改成最小堆，链表依次加入最小堆弹出节点，加入该节点所在链表新节点，不断调整堆......STL中提供heap算法

```cpp
static bool compareLess(ListNode* l1,ListNode* l2)
{
    return l1->val > l2->val;
}
ListNode* mergeKLists(vector<ListNode*> &lists)
{
    if(lists.size() < 1) return nullptr;
    vector<ListNode *> vec;

    for(auto i : lists)
        if(i) vec.push_back(i);
    
    make_heap(vec.begin(),vec.end(),compareLess);      // 建堆
    ListNode *newHead = new ListNode(-1);
    ListNode *rear = newHead, *cur;
    while(!vec.empty())
    {
        cur = vec.front();                       // 堆第一个节点first为最小值节点
        rear->next = cur;
        rear = cur;
        pop_heap(vec.begin(),vec.end(),compareLess);   // 它把first和last-1交换，然后重新生成一个堆
        vec.pop_back();                                // 容器弹出最后一个节点
        
        if(cur->next)                                  // 添加弹出的最小值的节点所在链表节点 last-1位置
        {
            vec.push_back(cur->next);
            push_heap(vec.begin(),vec.end(),compareLess);  // first到last-1是一个有效堆，新加入元素重新生成堆
        }
    }
    return newHead->next;
}
```

思路3: 使用优先队列(实质与堆相差无几)  priority_queue
  /*
  struct compare
   {
     bool operator()(const ListNode* l, const ListNode* r)
       {
           return l->val > r->val;
       }
   };
   ListNode *mergeKLists(vector<ListNode *> &lists)
   {
      priority_queue<ListNode *, vector<ListNode *>,compare> q;  //compare
      for(auto l:lists)
        if(l)  q.push(l);
      if(q.empty())  return NULL;
       ListNode fake(0);
       ListNode *result = &fake;
       while(!q.empty())
       {
           result->next = q.top();
           q.pop();
           result = result->next;
           if(result->next)
               q.push(result->next);
       }
       return fake.next;
   }
   */