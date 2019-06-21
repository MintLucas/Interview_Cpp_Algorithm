#include "Array.hpp"
#include <math.h>
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <set>
#include <sstream>

using namespace std;

int mainElement(vector<int> vec){
    int count = 1, idx = 0;
    //也可以从0开始遍历，count从0开始累加，判断放最前面
    //从1开始遍历，每次和之前的Key值比
    for(int i = 1; i < vec.size(); i++){
        if (vec[i] == vec[idx]) {
            count++;
        }
        else{
            if (count > 0) {
                count--;
            } else {
                count = 1;
                idx = i;
            }
        }
    }
    //不用再新定义一个变量来计数，可以在For循环里初始化之前的变量count
    if (count > 0)
        for(int i = count =  0; i < vec.size(); i++)
            if (vec[i] == vec[idx])
                count++;
    if(count > vec.size()/2) return vec[idx];
    return -1;
}

int continuousMaxSum(vector<int> vec){
    int cur_max = vec[0], end_max = vec[0];
    for(int i = 1; i < vec.size(); i++){
        cur_max = max(cur_max + vec[i], vec[i]);
        end_max = max(cur_max, end_max);
    }
    return end_max;
}

vector<int> getLeastKnumber(vector<int> input, int k){
    vector<int> result;
    if(input.size() < 0 || input.size() < k) return result;
    sort(input.begin(), input.end());
    for(int i = 0; i < k; i++){
        result.push_back(input[i]);
    }
    return result;
}



int numOfone(int n){
    string str = to_string(n);
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '1') {
            count++;
        }
    }
    return count;
}

bool cmp(int a, int b){
    string stra = to_string(a) + to_string(b);
    string strb = to_string(b) + to_string(a);
    //如果正序，return true不做交换
    if (stra <= strb) {
        return true;
    } else {
        return false;
    }
}

string printMinNum(vector<int> numbers){
    sort(numbers.begin(), numbers.end(), cmp);
    string result;
    for (int i = 0; i < numbers.size(); i++) {
        result += to_string(numbers[i]);
        cout << numbers[i] << endl;
    }
    return result;
}

bool isUglyNum(int num){
    while (num % 2 == 0) {
        num >>= 1;
    }
    while (num % 3 == 0) {
        num = num / 3;
    }
    while (num % 5 == 0) {
        num = num /5;
    }
    return num == 1;
}

int getKuglyNum(int K){
    if(K < 6) return K;
    vector<int> uglyVec;
    int que2 = 0, que3 = 0, que5 = 0, newNum = 1;
    uglyVec.push_back(newNum);
    while (uglyVec.size() < K) {
        newNum = min(min(uglyVec[que2] * 2, uglyVec[que3] * 3), uglyVec[que5] * 5);
        if(newNum == uglyVec[que2] * 2) que2++;
        if(newNum == uglyVec[que3] * 3) que3++;
        if(newNum == uglyVec[que5] * 5) que5++;
        uglyVec.push_back(newNum);
    }
    return uglyVec[K-1];
}

void reverseArray(vector<int> &array, int left, int right, size_t size){
    if(left < 0 || right > size) return;
    int low = left, high = right;
    while (low < high) {
        swap(array[low++], array[high--]);
    }
    return;
}

void rotateArray(vector<int> &array, int left, int mid, int right){
    reverseArray(array, left, mid - 1, array.size());
    reverseArray(array, mid, right, array.size());
    reverseArray(array, left, right, array.size());
    return;
    
}

void deleteX(vector<int> &array, int x){
    //count下标存储不等于X的元素
    int count = 0;
    for (int i = 0; i < array.size(); i++) {
        if (array[i] != x) {
            array[count++] = array[i];
        }
    }
}

void deleteDuplication(vector<int> &array){
    //和链表思想一致，需要用下标来🔗非重复结点
    int count = 0;
    int aft = 0;
    //count下标存储不重复的元素
    //int count=0, i=1;错位，利用for遍历，和count里最后一个元素比
    //if(!= [count]) [++count]=i;
    for (int i = 0; i < array.size(); i++) {
        if (array[i+1] == array[i]) {
            aft = i + 1;
            while(array[aft] == array[i])
                aft++;
            ////保存第一个非重复的,如果全删则不用这句话
            array[count++] = array[i];
            i = aft -1 ;//外层循环有i++
        }
        else
            array[count++] = array[i];
    }
}

void mergeSort(vector<int> &array, int low, int high){
    if(low >= high) return;
    int mid = low + (high - low)/2;
    mergeSort(array, low, mid);
    mergeSort(array, mid + 1, high);
    merge(array, low, mid, high);
}

void merge(vector<int> &array, int low, int mid, int high){
    vector<int> temp(array);
    //t取low按同样位置排序，t取0拷贝时从low下标开始拷贝
    int cur1 = low, cur2 = mid + 1, t = low;
    while (cur1 <= mid && cur2 <= high) {
        if (array[cur1] <= array[cur2])
            temp[t++] = array[cur1++];
        else
            temp[t++] = array[cur2++];
    }
    while(cur1 <= mid)
        temp[t++] = array[cur1++];
    while(cur2 <= high)
        temp[t++] = array[cur2++];
    for (t = low; t <= high; t++) {
        array[t] = temp[t];
    }
}

void bubbleSort(vector<int> &array){
    //n-1次找最轻
    for (int i = 0, j; i < array.size() - 1; i++) {
        bool flag = false;
        //for里一趟冒泡,最轻的气泡漂浮到顶部
        for(j = int(array.size() - 1); j > i; j--)
            if(array[j-1] > array[j]){
                swap(array[j-1], array[j]);//逆序则交换
                flag = true;
            }
        if(flag == false)
            return;
    }
}

void quickSort(vector<int> &array, int low, int high){
    if(low >= high) return;
    
    //随机int randomPivot = low+rand()%(right-low);
    //swap(array[low],array[randomPivot];)
    
    //*****partition部分,用局部变量low,high
    //为了确保是从对立面找不能直接随机化pivot的值，否则出现同侧移动
    int i = low, j = high, pivot = i;
    while(i < j){
        //pivot的对立面找一个小于pivot
        while(i < j && array[j] >= array[pivot])
            j--;
        while(i < j && array[i] <= array[pivot])
            i++;
        //交换完不用两边++会自动满足
        swap(array[i], array[j]);
    }
    //最后一次把pivot放到合适位置现在的单个元素也要放到pivot的地方去
    swap(array[pivot], array[i]);
    int mid = i;
    
    //写在一个函数里需要新的变量来遍历不然low和high已经移动
    quickSort(array, low, mid - 1);
    quickSort(array, mid + 1, high);
    return;
}

void selectSort(vector<int> &array){
    //和冒泡的FOR类似
    for (int i = 0, min = 0; i < array.size() - 1; i++) {
        //记录最小值的下标即可
        min = i;
        for (int j = int(array.size() - 1); j > i; j--)
            if (array[j] < array[min])
                min = j;
        swap(array[min], array[i]);
    }
}

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

void insertSort(vector<int> &array){
    //往前方已经有序的数组内插
    //初始时第一个为已排序
    for (int i = 1, j, temp; i < array.size(); i++) {
        if (array[i] < array[i-1]) {
            temp = array[i];//或array[0]=array[i]当哨兵
            for (j = i - 1; array[j] > temp && j >= 0; j--) {
                array[j+1] = array[j];
            }
            array[j+1] = temp;
        }
    }
}

void shellSort(vector<int> &array){
    for(int k = int(array.size()/2); k > 0; k/=2){
        for (int i = 1+k,j,temp; i < array.size(); i+=k) {
            if(array[i] < array[i-k]){
                temp = array[i];
                for(j = i-k; array[j] > temp && j>=0; j-=k)
                    array[j+k] = array[j];
                array[j+k] = temp;
            }
        }
    }
}


int find_max(int a[], int len){
    int max = a[0];
    for(int i = 0; i < len; ++i)
        if(a[i] > max) max = a[i];
    return max;
}
//计算number有多少位 即几个关键字254有百位
int digit_number(int number){
    int count = 0;
    do{
        number /= 10;
        count++;
    }while(number != 0);
    return count;
}
//返回number上第kth位的数字
int kth_digit(int number, int kth){
    number /= pow(10, kth);
    return number % 10;
}
void radix_sort(int a[], int len){
    int *temp[10];
    int count[10] = {0};
    int max = find_max(a, len);
    int maxDigit = digit_number(max);
    int i, j, k;
    for (i = 0; i < 10; ++i) {
        temp[i] = new int[len];
        memset(temp[i], 0, sizeof(int)*len);
    }
    for (int curDigit = 0; curDigit < maxDigit; ++curDigit) {
        memset(count, 0, sizeof(int)*10);
        for (int curNum = 0; curNum < len; ++curNum) {
            int xx = kth_digit(a[curNum], curDigit);
            temp[xx][count[xx]] = a[curNum];
            count[xx]++;
        }
        int idx = 0;
        //一趟22 32 53 47 19 29
        for (j = 0; j < 10; ++j) {
            for (k = 0; k < count[j]; ++k) {
                a[idx++] = temp[j][k];
            }
        }
    }
}

int binarySearch(vector<int> array, int x){
    int low = 0, high = int(array.size() - 1);
    while (low <= high) {
        int mid = low + (high - low)/2;
        if(array[mid] == x)
            return mid;
        if(array[mid] > x)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

vector<int> createHash(const vector<int> array){
    size_t size = array.size();
    vector<int> hash(size, -1);
    for (int i = 0; i < array.size(); i++) {
        int idx = array[i] % size;
        while(hash[idx] != -1)
            idx = (idx + 1) % size;
        hash[idx] = array[i];
    }
    return hash;
}


    
//int main(){
//    string s = "I am a cat.";
//    vector<int> vec = {2, 5, 7, 8, 10,15};
//    vector<int> temp = FindNumbersWithSum(vec, 12);
//    cout << temp[0] << endl;
//    //s = LeftRotateString(s, 3);
//    return 0;
//}
