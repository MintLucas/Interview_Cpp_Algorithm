/*
快排

注意：
    - 快排是不稳定排序

思路：
    选基数，双指针移动/交换，分治

示例：
    > 坐在马桶上看算法：快速排序 - 51CTO.COM http://developer.51cto.com/art/201403/430986.htm
    > 快速排序(三种算法实现和非递归实现) - CSDN博客 https://blog.csdn.net/qq_36528114/article/details/78667034
    
    第一轮
            i                               j
        6   1   2   7   9   3   4   5   10  8
        基数 x=6
        先从 j 往前遍历(j--)，遇到小于 x 的数停下，再从 i 往后遍历，遇到大于 x 的数停下，交换 *j 和 *i
                    i               j
        6   1   2   7   9   3   4   5   10  8
        6   1   2   5   9   3   4   7   10  8（交换后）
        重复以上步骤，继续先移动 j，再移动 i
                        i       j
        6   1   2   5   9   3   4   7   10  8
        6   1   2   5   4   3   9   7   10  8（交换后）
                           ij
        6   1   2   5   4   3   9   7   10  8
        6   1   2   5   4   3   9   7   10  8（交换后）
        此时 i 与 j 相遇，交换 *i 与 *x
                           ij
        3   1   2   5   4   6   9   7   10  8
        第一轮完成，之后递归完成子部分

    基数的选择不固定，一般选择第一个或最后一个，或中位数
*/

#pragma once
#include "../all.h"

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

void
solve()
{   
    int arr[]{ 10,6,1,2,2,7,9,3,4,5,8,8 };
    int n = sizeof(arr) / sizeof(int);

    quickSort(arr, 0, n - 1);

    for (auto i : arr)
        cout << i << ' ';
    print();
}