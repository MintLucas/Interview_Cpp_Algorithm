#include <iostream>
#include <cstdio>
using namespace std;
int main() {
    int a,b;
    //单行多行输入输出规范，输入1 2 输出3
    //返回流的引用输入不合法即退出
    while(cin >> a >> b)//注意while处理多个case
        cout << a+b << endl;
    
    //freopen("1.in","r",stdin);多行输入输出规范
    int n,ans = 0;
    //求n阶方阵的和，第一行输入n，空格隔开
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int x; scanf("%d",&x);
            ans += x;
        }
}
