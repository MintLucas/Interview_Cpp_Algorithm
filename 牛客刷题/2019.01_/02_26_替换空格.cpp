#include <bits/stdc++.h>;
using namespace std;

class Solution {
public:
	void replaceSpace(char *str,int length) {
        char* s = str;
        int num = 0;
        for(int i = 0; i < length; i++){
            if(s[i] == ' ')
                num++;
        }        
        int new_length = length + 2*num;
        
        // int new_last = new_length - 1;
        // int last = length - 1;

        // while(new_last >= 0 && last >= 0){
        //     if(s[last] != ' '){
        //         s[new_last] = s[last];
        //         new_last = new_last - 1;
        //     }
        //     else{
        //         s[new_last] = '0';
        //         s[new_last-1] = '2';
        //         s[new_last-2] = '%';
        //         new_last = new_last - 3;
        //     }
        //     last--;
        // }
        // return;

        for(int j = new_length; j >= 0; j--){
            if(s[j] != ' '){
                s[j] = s[j-1];
            }
            else{
                s[j] = '%';
                s[j+1] = '2';
                s[j+2] = '0';
            }
        }    
	}
};

int main(){
    char* test = "We are family";
    string s= "We are family";  
    // printf(strlen(test));
    // printf(s.length);
    s = test;
    int length = s.length();

    Solution solu;
    // solu.replaceSpace(test, length);
}