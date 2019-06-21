/*
用C/C++实现一个函数，

LeetCode: https://leetcode.com/problems/implement-strstr/

函数声明
    int* match (const char* substr, const char* target)
    返回 substr 在 target 中出现的所有位置

思路：
    KMP 算法
*/
#pragma once

```cpp
int strStr(string haystack, string needle) {
    if(needle == "") return 0;
    if(haystack == "") return -1;
    int i = 0, j = 0;
    while(i < haystack.size() && j < needle.size()){
        if(haystack[i] == needle[j]){
            ++i;
            ++j;
        }
        else{
            i = i - j + 1;
            j = 0;
        }
    }
    if(j == needle.size()) return i - j;
    return -1;
}
```