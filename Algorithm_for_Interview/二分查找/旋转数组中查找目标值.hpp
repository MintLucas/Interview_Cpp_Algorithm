/*
LeetCode 33. 搜索旋转排序数组 https://leetcode.com/problems/search-in-rotated-sorted-array/

题目描述：
    假设按照升序排序的数组在预先未知的某个点上进行了旋转。

    ( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

    搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。

    你可以假设数组中不存在重复的元素。

    你的算法时间复杂度必须是 O(log n) 级别。

    示例 1:
        输入: nums = [4,5,6,7,0,1,2], target = 0
        输出: 4
    示例 2:
        输入: nums = [4,5,6,7,0,1,2], target = 3
        输出: -1

思路：
    虽然可能通过各种条件判断直接一次二分，但是很容易出错

    保险的做法是通过两次二分，先找出最小值的位置，然后确定 target 的区间，再用一次二分去找
    > 寻找最小值的位置 > LeetCode 153、154

提交记录：
    提交了 N 次才过，边界条件太容易出错了
*/
#pragma once

#include "../all.h"

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.size() < 1) return -1;
        int lo = -1, hi = nums.size() - 1;
        
         //找到旋转数组分界点hi
        while(lo + 1 < hi){
            int mid = lo + (hi - lo)/2;
            if(nums[mid] < nums[hi])
                hi = mid;
            else
                lo = mid;
        }

        if(nums[hi] == target) return hi;//开区间把hi去除
        if(nums[hi] < target && nums[nums.size()-1] >= target)
        {
            lo = hi;
            hi = nums.size();//左开右开区间
        }
        else
            lo = -1;//在左排序数组中
        
        /*
        错误写法，不能用左排序数组最大值来确定是否在左,要判断是否在右
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