/*
��C/C++ʵ��һ��������

LeetCode: https://leetcode.com/problems/implement-strstr/

��������
    int* match (const char* substr, const char* target)
    ���� substr �� target �г��ֵ�����λ��

˼·��
    KMP �㷨
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