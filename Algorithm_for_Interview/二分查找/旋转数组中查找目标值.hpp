/*
LeetCode 33. ������ת�������� https://leetcode.com/problems/search-in-rotated-sorted-array/

��Ŀ������
    ���谴�����������������Ԥ��δ֪��ĳ�����Ͻ�������ת��

    ( ���磬���� [0,1,2,4,5,6,7] ���ܱ�Ϊ [4,5,6,7,0,1,2] )��

    ����һ��������Ŀ��ֵ����������д������Ŀ��ֵ���򷵻��������������򷵻� -1 ��

    ����Լ��������в������ظ���Ԫ�ء�

    ����㷨ʱ�临�Ӷȱ����� O(log n) ����

    ʾ�� 1:
        ����: nums = [4,5,6,7,0,1,2], target = 0
        ���: 4
    ʾ�� 2:
        ����: nums = [4,5,6,7,0,1,2], target = 3
        ���: -1

˼·��
    ��Ȼ����ͨ�����������ж�ֱ��һ�ζ��֣����Ǻ����׳���

    ���յ�������ͨ�����ζ��֣����ҳ���Сֵ��λ�ã�Ȼ��ȷ�� target �����䣬����һ�ζ���ȥ��
    > Ѱ����Сֵ��λ�� > LeetCode 153��154

�ύ��¼��
    �ύ�� N �βŹ����߽�����̫���׳�����
*/
#pragma once

#include "../all.h"

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.size() < 1) return -1;
        int lo = -1, hi = nums.size() - 1;
        
         //�ҵ���ת����ֽ��hi
        while(lo + 1 < hi){
            int mid = lo + (hi - lo)/2;
            if(nums[mid] < nums[hi])
                hi = mid;
            else
                lo = mid;
        }

        if(nums[hi] == target) return hi;//�������hiȥ��
        if(nums[hi] < target && nums[nums.size()-1] >= target)
        {
            lo = hi;
            hi = nums.size();//���ҿ�����
        }
        else
            lo = -1;//��������������
        
        /*
        ����д�����������������������ֵ��ȷ���Ƿ�����,Ҫ�ж��Ƿ�����
        if(nums[lo] >= target) lo = -1;
        else hi = nums.size();
        */
        
        while(lo + 1 < hi){
            int mid = lo + (hi - lo)/2;
            if(nums[mid] < target)
                lo = mid;
            else
                hi = mid;
        }
        if(hi == nums.size()) return -1;
        return nums[hi] == target ? hi : -1;
    }

void
solve()
{
    vector<int> nums{ 3,5,1 };
    Solution().search(nums, 5);
}