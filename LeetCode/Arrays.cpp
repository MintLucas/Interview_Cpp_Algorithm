#include "Arrays.hpp"
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;





char *Trim(char *str,char c)
{

    //strlen不带最后的结束符
    int len = strlen(str) + 1;
    int i = 0;
    int count = 0;
    
    if(0 == len)
    {
        return str;
    }
    
    for (i = 0; i < len; ++i) {
        if(str[i] == c){
            count++;
            continue;
        }
        else{
            str[i - count] = str[i];
        }
    }
//    if(str[len-count - 2] == '\n')
//        str[len - count - 2] = '\0';
    
        
    int len2 = strlen(str);
//    str[len - count] = '\0';
    int len3 = strlen(str);
    return str;
    
}

int removeElement(vector<int>& nums, int val) {
    int count = 0;
    for(int i = 0; i < nums.size(); ++i){
        if(nums[i] == val){
            count++;
            continue;
        }
        else{
            nums[i - count] = nums[i];
        }
    }
    nums.erase(nums.end()-count,nums.end());
    return nums.size() - count;
}

int main(){
    int pause_distance = 20;
    int pause_shrink_rate = 2;
    int cut_distance = 5;
    int cut_shrink_rate = 2;
    double warmup_rate_0 = exp(log(pause_shrink_rate)/pause_distance);
    double warup_rate_1 = exp(log(cut_shrink_rate)/cut_distance);
    char readbuf[20000];
    char *s = (char*)malloc(200);
    char *s2 = " They say he carved it himself\n";
    cout << s2;
    cout << s2;
    memcpy(s, s2, strlen(s2));
    s = Trim(s, ' ');
    s = Trim(s, '\n');
    cout << s << endl;
    
    vector<int> vec = {0,1,2,2,3,0,4,2};
    removeElement(vec, 2);
    return 0;
}
