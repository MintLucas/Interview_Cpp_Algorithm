/*
������
- �������ǲ��ȶ�����
- �ѵ����ʣ�
    ÿ���ڵ��ֵС�ڵ����丸�ڵ� �� ���ڵ��ڸ��ڵ㣻ǰ�߳�Ϊ�����ѡ����������򣬺���Ϊ����С�ѡ������ڽ���
- ����һ��**��ȫ������**����˳����������ģ��

˼·��
    ���ѣ�
        ���ѵĹ���ʵ���Ͼ��Ǵ����һ�� ��Ҷ�ӽڵ� ��ʼ������ǰ���Զ����µĵ���
    ������
        ����Ѻ�ÿ�ν����Ѷ��Ͷ�β��
        Ȼ��� a[0..n-1] ���µ���

    ÿ�ε����Ĳ���ʱ�临�Ӷ�Ϊ O(logn)
    ���ѵ�ʱ�临�Ӷ�Ϊ O(N)

*/

int heapsize = 0;
void maxHeapify(vector<int> &array, int k){

    //��Ԫ��k���½��е���,��i��k�����ӣ�i��k�£�
    // ע�⣺�Զ����µĲ���ֻ�����һ���ڵ�ĵ���
    
    for(int i = 2*k+1; i < heapsize; i=i*2+1){
        //��ǰ�����ڵ�Ϊk,�����ӽڵ�����ֵ�Ƚ���С����Υ����������
        int largest = array[k];
        
        //largest=max(a[left],a[right])�����ڲ�Խ�������£�right<heapsize
        // ʵ���ϣ����²�������Ϊ���ҳ� a[i] �� a[i*2+1]��a[i*2+2] ֮�е����ֵ
        if(i+1 < heapsize && array[i] < array[i+1])
            i++;
        
        //��ǰ�ڵ�������������ӽڵ㣬�������
        if(largest >= array[i]) break;
        //����a[i] �������ģ�˵�������������
        else{
            swap(array[k], array[i]);
            k = i;
        }
    }
}

void buildMaxHeap(vector<int> &array){
    //ȫ�ֱ��������ƶѵĵ���
    heapsize = int(array.size());
    // ���ѵĹ���ʵ���Ͼ��Ǵ����һ�� **��Ҷ�ӽڵ�** ��ʼ������ǰ����
    for (int i = int(array.size()>>1); i >= 0; --i){
        maxHeapify(array, i);
    }
}

void heapSort(vector<int> &array){
    buildMaxHeap(array);
    for(int i = int(array.size() - 1); i >= 1; --i){
        //�Ѷ�Ԫ��array[0]�����ֵ������β,�����µ�����
        swap(array[i], array[0]);
        //�Ӷ���ɾ����Ԫ��
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