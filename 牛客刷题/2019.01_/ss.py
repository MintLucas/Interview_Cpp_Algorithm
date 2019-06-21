#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Feb 14 16:51:02 2019

@author: zhipeng
"""
from functools import reduce

# -*- coding:utf-8 -*-
class Solution:
    def multiply(self, A):
        # write code here
        B = []
        if len(A) == 0:
            return B
        else:
            for i in range(len(A)):
                tmp = A[i]
                A[i] = 1
                #B初始化为空不能直接用
                #B[i] = reduce(lambda x,y:x*y, A)
                B.append(reduce(lambda x,y:x*y, A))
                A[i] = tmp
            return B

if __name__ == '__main__':
    numbers = [2,1,3,1,4]
    s = Solution()
    ss = s.multiply(numbers)
    print(ss)