#include <math.h>
#include <iostream>
#include <queue>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include "BTree.hpp"
#include "01_ListNode.hpp"
#include <unordered_set>
#include "HuaWeiOJ0_108.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

//int main(){
//    string line;
//    while (getline(cin, line)) {
//        size_t idx = line.find(' ');
//        char c = line[idx+1];
//        char lc = tolower(c);
//        char uc = toupper(c);
//        int count = 0;
//        for(int i = 0; i < idx; i++)
//            if(line[i] == lc || line[i] == uc) count++;
//        cout << count;
//    }
//    return 0;
//}

int deleteDuplicationAndSort(){
    int n;
    while(cin >> n){
        vector<int> arr(n);
        for(int i = 0; i < n; ++i) cin >> arr[i];
        set<int> res(arr.begin(), arr.end());
        for(auto i : res) cout << i << endl;
    }
    return 0;
}

int lastWordLen(){
    string line;
    while(getline(cin, line)){
        size_t len = line.rfind(' ');
        string lword = line.substr(len+1);
        cout << lword.size() << endl;
    }
    return 0;
}

int numOfOneInBinary(){
    int n;
    while (cin >> n) {
        int count = 0;
        while(n > 0){
            if(n % 2 == 1) count++;
            n /= 2;
        }
        cout << count << endl;
    }
    return 0;
}

int to_decimal(string s){
    int res = 0;
    int temp = 1;
    for(int i = int(s.size() - 1); i >= 0; --i){
        if(s[i] >= '0' && s[i] <= '9'){
            res += (s[i] - '0')*temp;
            temp *= 16;
        }
        else if(s[i] >= 'A' && s[i] <= 'F'){
            res += (s[i] - 'A' + 10)*temp;
            temp *= 16;
        }
    }
    return res;
}

void sortStr()
{
    string s;
    while(cin >> s){
        vector<char> tempChar;
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < s.size(); ++j) {
                //按桶的顺序装桶
                if(s[j] - 'a' == i || s[j] - 'A' == i)
                    tempChar.push_back(s[j]);
            }
        }
        for (int i = 0, j = 0; i < s.size(); ++i) {
            if(isalpha(s[i]))
                s[i] = tempChar[j++];
        }
        cout << s << endl;
    }
}

//int main(){
//
//}
