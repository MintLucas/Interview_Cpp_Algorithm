/*
二分查找模板

注意点：
    - 是否存在重复元素

模板 1 - binary_search
    - 没有重复元素时，目标值若存在，则返回索引；若不存在，返回 -1
    - 存在重复元素时，目标值若存在，则返回最小索引；若不存在，返回 -1

模板 2 - lower_bound 满足条件<lo往右,else收缩（low,high]终值在闭区间右侧上6667(-1,0]
    - 返回大于(含等于)目标值的最小索引（第一个大于、等于目标值的索引返回0）
    
模板 3 - upper_bound 满足条件<=lo往右,=继续往右找到[low,high)6667[2,3)
    - 返回大于等于目标值的最大索引+1（第一个大于目标值的索引返回3）
    
注意点：
    - 跳出时都有lo + 1 == hi统一返回lo + 1或hi
    - lo = -1 and hi = nums.size()和 lo = 0 and hi = nums.size() - 1取中时一致
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

    while (hi - lo > 1) {                       // 退出循环时有：lo + 1 == hi
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] < v)
            lo = mid;                           // 因为始终将 lo 端当做开区间，所以没有必要 `lo = mid + 1;`
        else
            hi = mid;                           // 而在 else 中，mid 可能就是最后的结果，所以不能 `hi = mid - 1`
    }

    return lo + 1; // 相比 binary_search，只有返回值不同
}
/*为什么返回 `lo+1`，而不是 `hi`？（退出循环时有 lo + 1 == hi）
    模板开始时将 (lo, hi) 看做是一个开区间，通过不断二分，最终这个区间中只会含有一个值，即 (lo, hi]
    返回 lo+1 的含义是，结果就在 lo 的下一个；
    在迭代的过程中，hi 会从开区间变为闭区间，而 lo 始终是开区间，
    返回 lo+1 显得更加统一。
    当然，这跟迭代的写法是相关的，你也可以使最终的结果区间是 [lo, hi)nums[mid]<=v，
    这取决于个人习惯。
*/


int upper_bound(vector<int>& nums, int v) {
    if (nums.size() < 1) return -1;

    int lo = -1, hi = nums.size();

    while (hi - lo > 1) {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] <= v)                     // 相比 lower_bound，唯一不同点：`<` -> `<=`
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