/*
加一 - LeetCode (中国) https://leetcode-cn.com/problems/plus-one/description/

题目来源：LeetCode

题目描述：
    给定一个非负整数组成的非空数组，在该数的基础上加一，返回一个新的数组。

    最高位数字存放在数组的首位， 数组中每个元素只存储一个数字。

    你可以假设除了整数 0 之外，这个整数不会以零开头。

    示例 1:

    输入: [1,2,3]
    输出: [1,2,4]
    解释: 输入数组表示数字 123。
    示例 2:

    输入: [4,3,2,1]
    输出: [4,3,2,2]
    解释: 输入数组表示数字 4321。

解题思路：
    1. 依次进位
    2. 如果--len则len为), 当len=0时代表无数
    3. 如果len--则len为[ 即所指为当前数字类似栈指针top=-1, 当-1时代表无数
提交记录：


*/
#pragma once

#include "../all.h"



方法一： 

vector<int> plusOneA(vector<int>& digits){
    int len = digits.size();
    if(len < 1) return digits;
    if(digits[--len] != 9)
        digits[len]++;
    else{
        while (digits[len] == 9) {
            digits[len--] = 0;
        }
        if(len == -1)
            digits.insert(digits.begin(), 1);
        else
            digits[len]++;
    }
    return digits;
}


方法二：直接加法进位
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> ret(digits);
        for (int i = ret.size() - 1; i >= 0; i--) {
            if (ret[i] < 9) {
                ret[i]++;
                return ret;
            }
            ret[i] = 0;
        }
        ret.insert(ret.begin(), 1);

        return ret;
    }
};

void
solve()
{

}

方法三：vector_to_num->num_to_vec

```cpp
long int vector_to_num(vector<int> &vec){
    int len = vec.size();
    long int sum = 0;
    for (int i = 0; i < len; ++i) {
        sum = sum * 10 + vec[i];
    }
    return sum;
}
vector<int> num_to_vec(vector<int> &vec,long int num){
    int len = vec.size();
    int i = 0;
    while (num != 0) {
        if(len == 0){
            vec.insert(vec.begin(), num%10);
            break;
        }
        vec[--len] = num%10;
        num /= 10;
    }
    return vec;
}

vector<int> plusOne(vector<int>& digits) {
    int len = digits.size();
    if(len < 1) return digits;
    long int num = vector_to_num(digits);
    digits = num_to_vec(digits, num+1);
    return digits;
}
```