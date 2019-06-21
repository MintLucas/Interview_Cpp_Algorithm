/*
���ֲ���ģ��

ע��㣺
    - �Ƿ�����ظ�Ԫ��

ģ�� 1 - binary_search
    - û���ظ�Ԫ��ʱ��Ŀ��ֵ�����ڣ��򷵻��������������ڣ����� -1
    - �����ظ�Ԫ��ʱ��Ŀ��ֵ�����ڣ��򷵻���С�������������ڣ����� -1

ģ�� 2 - lower_bound ��������<lo����,else������low,high]��ֵ�ڱ������Ҳ���6667(-1,0]
    - ���ش���(������)Ŀ��ֵ����С��������һ�����ڡ�����Ŀ��ֵ����������0��
    
ģ�� 3 - upper_bound ��������<=lo����,=���������ҵ�[low,high)6667[2,3)
    - ���ش��ڵ���Ŀ��ֵ���������+1����һ������Ŀ��ֵ����������3��
    
ע��㣺
    - ����ʱ����lo + 1 == hiͳһ����lo + 1��hi
    - lo = -1 and hi = nums.size()�� lo = 0 and hi = nums.size() - 1ȡ��ʱһ��
*/
#pragma once

#include "../all.h"


int binary_search(vector<int>& nums, int v) {
    if (nums.size()
     < 1) return - 1;

    int lo = -1, hi = nums.size();

    while (hi - lo > 1) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] < v)
            lo = mid;
        else
            hi = mid;
    }

    return nums[lo + 1] == v ? lo + 1 : -1;
}


int lower_bound(vector<int>& nums, int v) {
    if (nums.size() < 1) return -1;

    int lo = -1, hi = nums.size();

    while (hi - lo > 1) {                       // �˳�ѭ��ʱ�У�lo + 1 == hi
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] < v)
            lo = mid;                           // ��Ϊʼ�ս� lo �˵��������䣬����û�б�Ҫ `lo = mid + 1;`
        else
            hi = mid;                           // ���� else �У�mid ���ܾ������Ľ�������Բ��� `hi = mid - 1`
    }

    return lo + 1; // ��� binary_search��ֻ�з���ֵ��ͬ
}
/*Ϊʲô���� `lo+1`�������� `hi`�����˳�ѭ��ʱ�� lo + 1 == hi��
    ģ�忪ʼʱ�� (lo, hi) ������һ�������䣬ͨ�����϶��֣��������������ֻ�Ậ��һ��ֵ���� (lo, hi]
    ���� lo+1 �ĺ����ǣ�������� lo ����һ����
    �ڵ����Ĺ����У�hi ��ӿ������Ϊ�����䣬�� lo ʼ���ǿ����䣬
    ���� lo+1 �Եø���ͳһ��
    ��Ȼ�����������д������صģ���Ҳ����ʹ���յĽ�������� [lo, hi)nums[mid]<=v��
    ��ȡ���ڸ���ϰ�ߡ�
*/


int upper_bound(vector<int>& nums, int v) {
    if (nums.size() < 1) return -1;

    int lo = -1, hi = nums.size();

    while (hi - lo > 1) {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] <= v)                     // ��� lower_bound��Ψһ��ͬ�㣺`<` -> `<=`
            lo = mid;
        else
            hi = mid;
    }

    return lo + 1;
}

void
solve()
{
    vector<int> v{ 1,2,2,3,4,6,6,6,8,9 };
    cout << v.size() << endl;       // 10

    auto ret = binary_search(v, 7);
    cout << ret << endl;            // -1

    ret = lower_bound(v, 6);
    cout << ret << endl; // 5

    ret = lower_bound(v, 7);
    cout << ret << endl; // 8

    ret = upper_bound(v, 6);
    cout << ret << endl; // 8

    ret = upper_bound(v, 7);
    cout << ret << endl; // 8
}

template<typename T>
int binarySearch(vector<T> &vec, T key){
    if(vec.size() < 0)
        return -1;
    int low = 0;
    int high = vec.size() - 1;
    int mid = 0;
    //low=highʱ������������ʱ��Ҫ��ȥ����vec[mid]==key�ж�
    while(low <= high){
        mid = low + (high - low)/2;
        if(vec[mid] == key)
            return mid;
        if(vec[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    //û�ҵ�����-1
    return -1;
}

    int lowwer_bound(vector<int> nums, int  n){
        if(nums.size() < 1) return -1;
        int lo = -1, hi = nums.size();
        while(lo + 1 < hi){
            int mid = lo + (hi - lo)/2;
            if(nums[mid] < n)
                lo = mid;
            else
                hi = mid;
        }
        return nums[hi] == n ? hi : -1;
    }
    int upper_bound(vector<int> nums, int  n){
        if(nums.size() < 1) return -1;
        int lo = -1, hi = nums.size();
        while(lo + 1 < hi){
            int mid = lo + (hi - lo)/2;
            if(nums[mid] <= n)
                lo = mid;
            else
                hi = mid;
        }
        return nums[lo] == n ? lo : -1;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res;
        res.push_back(lowwer_bound(nums, target));
        res.push_back(upper_bound(nums, target));
        return res;
    }