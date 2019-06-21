#include <bits/stdc++.h>
using namespace std;

template<typename T>
void swap1(T &a, T &b){
    T temp;
    temp = a;
    a = b;
    b = temp;
}

template<typename T>
void quickSort(vector<T> &vec,int left, int right){
    int low = left, high = right;
    if(vec.size() < 2 || low >= high)
        return;

    T key = low;
    while(low < high){
        //pivot的对立面找一个小于pivot
        while(vec[high] >= vec[key] && high > low)
            high--;
        //从左边找一个大于pivot
        while(vec[low] <= vec[key] && low < high)
            low++;
        //交换
        swap1(vec[low], vec[high]);
    }
    swap1(vec[low], vec[key]);

    //left和right不能变，此时low=high，左右分治递归下去
    quickSort(vec, left, high - 1);
    quickSort(vec, low + 1, right);
}

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
void bubbleSort(vector<T> &vec){
    for(int i = vec.size()-1; i >= 0; i--)
        for(int j = 0; j < i; j++)
            if(vec[j] > vec[j+1])
                swap1(vec[j], vec[j+1]);
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

template<typename T>
int binarySearch(vector<T> &vec, T key){
    if(vec.size() < 0)
        return -1;
    int low = 0;
    int high = vec.size() - 1;
    int mid = 0;
    //low=high时不能跳出，此时需要进去进行vec[mid]==key判断
    while(low <= high){
        mid = low + (high - low)/2;
        if(vec[mid] == key)
            return mid;
        if(vec[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    //没找到返回-1
    return -1;
}

int main(){
    //int a[] = {11,22,33,1,2,5};
    //double a[] = {3.0,6,3.5,4,5,3.2,3,2};
    //int a[] = {80,30,60,40,20,10,50,70};
    //vector<double> vec(a, a+8);

    //vector<double> vec = {3.0,6,3.5,4,5,3.2,3,2};在vs上出错百度是编译器问题

    //vector<int> vec1(vec);
    vector<std::string> vec;
    vec.push_back("lucas");
    vec.push_back("adam");
    vec.push_back("ardark");

    //for(int i = 0; i < 3; i++)
     //   vec.push_back(i);
    //swap1(vec[0], vec[1]);

    mergeSort(vec, 0, vec.size() - 1);
    //quickSort(vec, 0, vec.size() - 1);
    //bubbleSort(vec);
    //int idx = binarySearch(vec, 3.5);
    //cout << "the idx of finding is:" << idx << endl; 
    vector<string>::iterator ite;
    for(ite = vec.begin(); ite < vec.end(); ite++)
        cout << *ite << endl;
}
