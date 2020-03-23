/* 
牛客 (中国)https://www.nowcoder.com/ta/leetcode?query=remove

题目来源：LeetCode

题目描述：
    不允许新建数组，尽量在原数组遍历一次完成修改--删除某个元素，去除重复但最多允许重复几次等等。

解题思路：
    1. i遍历j记录有效数组
    2. 注意j可以从0开始替换时nums[++j]=nums[i], 也可从1开始nums[j++]=nums[i], 这样j始终在[)直接返回j
    3. count也一样可以从0即++时为1已重复两次判断时要<2，也可以从1开始++
    4. 比较时可以i和i-1也可以i和j比因为i重复后移即可, j永远是符合题目要求的值得下标
提交记录：

*/
#pragma once

#include "../all.h"

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() < 3) return nums.size();
        int i = 1, j = 1, count = 1;
        for(; i < nums.size(); ++i){
            if(nums[i] == nums[i - 1]){
                count++;
                if(count < 3)
                    nums[j++] = nums[i];
            }
            else{
                count = 1;
                nums[j++] = nums[i];
            }
        }
        return j;
    }
    
    
};

int main(){
    
    vector<int> vec = {0,0,1,1,1,1,2,3,3};
    int len = removeDuplicatesA(vec);
    return 0;
}

