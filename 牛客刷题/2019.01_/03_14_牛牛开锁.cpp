#include <iostream>
using namespace std;

int main(){
    int n = 3, count=0, dis, big, small;
    //返回流的引用输入不合法即退出
    while(cin >> n >> big >> small){
        cout << n <<endl;
    }
    //char*c 复制的地址 char c[]指向静态区的临时变量地址
    string s1;
    string s2;
    //空格也结束输入
    cin >> s1;
    cin >> s2;
    for(int i = 0; i < n; i++){
        big = s1[i] - '0'; small = s2[i] - '0';
        if(s1[i] < s2[i])
            swap(big, small);
        dis = big - small;
        //不区分大小(a-b+10)%10, (b-a+10)%10正走和反走
        if(dis > 5)
            count += (10 - big + small);
        else
            count += big - small;
    }
    cout << count;
}