/*
����

ע�⣺
    - �����ǲ��ȶ�����

˼·��
    ѡ������˫ָ���ƶ�/����������

ʾ����
    > ������Ͱ�Ͽ��㷨���������� - 51CTO.COM http://developer.51cto.com/art/201403/430986.htm
    > ��������(�����㷨ʵ�ֺͷǵݹ�ʵ��) - CSDN���� https://blog.csdn.net/qq_36528114/article/details/78667034
    
    ��һ��
            i                               j
        6   1   2   7   9   3   4   5   10  8
        ���� x=6
        �ȴ� j ��ǰ����(j--)������С�� x ����ͣ�£��ٴ� i ����������������� x ����ͣ�£����� *j �� *i
                    i               j
        6   1   2   7   9   3   4   5   10  8
        6   1   2   5   9   3   4   7   10  8��������
        �ظ����ϲ��裬�������ƶ� j�����ƶ� i
                        i       j
        6   1   2   5   9   3   4   7   10  8
        6   1   2   5   4   3   9   7   10  8��������
                           ij
        6   1   2   5   4   3   9   7   10  8
        6   1   2   5   4   3   9   7   10  8��������
        ��ʱ i �� j ���������� *i �� *x
                           ij
        3   1   2   5   4   6   9   7   10  8
        ��һ����ɣ�֮��ݹ�����Ӳ���

    ������ѡ�񲻹̶���һ��ѡ���һ�������һ��������λ��
*/

#pragma once
#include "../all.h"

void quickSort(vector<int> &array, int low, int high){
    if(low >= high) return;
    
    //���int randomPivot = low+rand()%(right-low);
    //swap(array[low],array[randomPivot];)
    
    //*****partition����,�þֲ�����low,high
    //Ϊ��ȷ���ǴӶ������Ҳ���ֱ�������pivot��ֵ���������ͬ���ƶ�
    int i = low, j = high, pivot = i;
    while(i < j){
        //pivot�Ķ�������һ��С��pivot
        while(i < j && array[j] >= array[pivot])
            j--;
        while(i < j && array[i] <= array[pivot])
            i++;
        //�����겻������++���Զ�����
        swap(array[i], array[j]);
    }
    //���һ�ΰ�pivot�ŵ�����λ�����ڵĵ���Ԫ��ҲҪ�ŵ�pivot�ĵط�ȥ
    swap(array[pivot], array[i]);
    int mid = i;
    
    //д��һ����������Ҫ�µı�����������Ȼlow��high�Ѿ��ƶ�
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