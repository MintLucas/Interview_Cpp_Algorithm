/*
��һ - LeetCode (�й�) https://leetcode-cn.com/problems/plus-one/description/

��Ŀ��Դ��LeetCode

��Ŀ������
    ����һ���Ǹ�������ɵķǿ����飬�ڸ����Ļ����ϼ�һ������һ���µ����顣

    ���λ���ִ�����������λ�� ������ÿ��Ԫ��ֻ�洢һ�����֡�

    ����Լ���������� 0 ֮�⣬��������������㿪ͷ��

    ʾ�� 1:

    ����: [1,2,3]
    ���: [1,2,4]
    ����: ���������ʾ���� 123��
    ʾ�� 2:

    ����: [4,3,2,1]
    ���: [4,3,2,2]
    ����: ���������ʾ���� 4321��

����˼·��
    1. ���ν�λ
    2. ���--len��lenΪ), ��len=0ʱ��������
    3. ���len--��lenΪ[ ����ָΪ��ǰ��������ջָ��top=-1, ��-1ʱ��������
�ύ��¼��


*/
#pragma once

#include "../all.h"



����һ�� 

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


��������ֱ�Ӽӷ���λ
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

��������vector_to_num->num_to_vec

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