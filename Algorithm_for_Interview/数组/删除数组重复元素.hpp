/* 
ţ�� (�й�)https://www.nowcoder.com/ta/leetcode?query=remove

��Ŀ��Դ��LeetCode

��Ŀ������
    �������½����飬������ԭ�������һ������޸�--ɾ��ĳ��Ԫ�أ�ȥ���ظ�����������ظ����εȵȡ�

����˼·��
    1. i����j��¼��Ч����
    2. ע��j���Դ�0��ʼ�滻ʱnums[++j]=nums[i], Ҳ�ɴ�1��ʼnums[j++]=nums[i], ����jʼ����[)ֱ�ӷ���j
    3. countҲһ�����Դ�0��++ʱΪ1���ظ������ж�ʱҪ<2��Ҳ���Դ�1��ʼ++
    4. �Ƚ�ʱ����i��i-1Ҳ����i��j����Ϊi�ظ����Ƽ���, j��Զ�Ƿ�����ĿҪ���ֵ���±�
�ύ��¼��

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

