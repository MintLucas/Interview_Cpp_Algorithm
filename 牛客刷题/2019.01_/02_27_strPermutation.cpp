#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> Permutation(string str) {
        vector<string> ret;
        if(str.length() == 0)
            return ret;
        int n = str.length();
        _str_permutation(str, ret, 0, n);
        return ret;
    }
private:
    void _str_permutation(string str,vector<string> &ret, int idx, int n){
        if(idx == n-1){
            ret.push_back(str);
            return;
        }
        for(int i = idx;i < n;i++){
            swap(str[idx], str[i]);
            _str_permutation(str, ret, idx+1, n);
            swap(str[idx], str[i]);
        }
    }
};