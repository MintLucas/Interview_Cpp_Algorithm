#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV){
        if(pushV.size() <= 0) return 0;
        
        //可以用i,j < popV.size()来遍历，可以用vector当栈
        vector<int>:: iterator p1 = pushV.begin();
        vector<int>:: iterator p2 = popV.begin();
        asist.push(*p1++);
        while(p2 != popV.end()){
            if(asist.top() == *p2){
                asist.pop();
                p2++;
                continue;
            }
            if(p1 != pushV.end()){
                asist.push(*p1++);
            }
            else
                return 0;
        }
        return true;
    }
private:
    stack<int> asist;
};

int main(){
    Solution solu;
    int a[] = {1,2,3,4,5};
    vector<int> pushV(a, a+5);
    int b[] = {4,5,3,2,1};
    vector<int> popV(b, b+5);
    bool tag = solu.IsPopOrder(pushV, popV);
    cout << tag;
}