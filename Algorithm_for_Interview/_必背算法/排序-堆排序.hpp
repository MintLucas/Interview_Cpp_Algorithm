/*
堆排序
- 堆排序是不稳定排序
- 堆的性质：
    每个节点的值小于等于其父节点 或 大于等于父节点；前者称为“最大堆”，用于升序，后者为“最小堆”，用于降序
- 堆是一棵**完全二叉树**，因此常用数组进行模拟

思路：
    建堆：
        建堆的过程实际上就是从最后一个 非叶子节点 开始不断向前做自顶向下的调整
    堆排序：
        建完堆后，每次交换堆顶和堆尾，
        然后对 a[0..n-1] 重新调整

    每次调整的操作时间复杂度为 O(logn)
    建堆的时间复杂度为 O(N)

*/

int heapsize = 0;
void maxHeapify(vector<int> &array, int k){

    //将元素k向下进行调整,即i是k的左孩子（i在k下）
    // 注意：自顶向下的操作只完成了一个节点的调整
    
    for(int i = 2*k+1; i < heapsize; i=i*2+1){
        //当前调整节点为k,和其子节点的最大值比较若小于则违背最大堆性质
        int largest = array[k];
        
        //largest=max(a[left],a[right])并且在不越界的情况下，right<heapsize
        // 实际上，以下操作就是为了找出 a[i] 和 a[i*2+1]、a[i*2+2] 之中的最大值
        if(i+1 < heapsize && array[i] < array[i+1])
            i++;
        
        //当前节点已满足大于其子节点，调整完毕
        if(largest >= array[i]) break;
        //否则a[i] 不是最大的，说明还需继续调整
        else{
            swap(array[k], array[i]);
            k = i;
        }
    }
}

void buildMaxHeap(vector<int> &array){
    //全局变量来控制堆的调整
    heapsize = int(array.size());
    // 建堆的过程实际上就是从最后一个 **非叶子节点** 开始不断往前调整
    for (int i = int(array.size()>>1); i >= 0; --i){
        maxHeapify(array, i);
    }
}

void heapSort(vector<int> &array){
    buildMaxHeap(array);
    for(int i = int(array.size() - 1); i >= 1; --i){
        //堆顶元素array[0]即最大值换到堆尾,再重新调整堆
        swap(array[i], array[0]);
        //从堆中删除该元素
        heapsize--;
        maxHeapify(array, 0);
    }
}

int main(){
    vector<int> vec = {45, 68, 20, 39, 88, 97, 46, 59};
    heapSort(vec);
    for(int i = 0; i < vec.size(); ++i)
        cout << vec[i] << " ";
    cout << endl;
}