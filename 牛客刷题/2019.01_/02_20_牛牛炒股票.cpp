#include <bits/stdc++.h>

using namespace std;
//容量下最大价值
int dp[1005];
//价格表，重量和价值
int c[1005][2];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) dp[i] = i; 
    for(int i = 1; i <= n; i++) {
        //初始化价格表
        scanf("%d%d", &c[i][0], &c[i][1]);
        for(int j = c[i][0]; j <= m; j++)
        //动态规划，之前重量下的价值或当前重量价值c[i][1]+余下容量dp
            dp[j] = max(dp[j], dp[j-c[i][0]] + c[i][1]);
    }
    printf("%d\n", dp[m] - m);
    return 0;
}


    // int main(){
    //     int N, M, left = 0;
    //     cin >> N, M;
    //     int array[1000];
    //     for(int i = 0; i < N; i++){
    //         for(int j = 0; j < 2; j++){
    //             int x,y;
    //             scanf("%d, %d", &x, &y);
    //             array[i] = y - x;
    //             }
    //     }
    //     int max[1000];
    //     for(int i = 0; i < N; i++){
    //         //按从大到小排序存入max数组
            
    //     }
    //     int total_earn = 0;
    //     for(int i = 0; i < N; i++){
    //         if(M > array[i]){
    //             left = M % max[i]
    //         }
        
//     }
        
// }


// // 本题为考试多行输入输出规范示例，无需提交，不计分。
// #include <iostream>
// #include <cstdio>

// using namespace std;

// int main(){
//     //freopen("1.in","r",stdin);
//     int n,ans = 0;
//     cin >> n;
//     for(int i = 0; i < n; i++){
//         for(int j = 0; j < n; j++){
//             int x; scanf("%d",&x);
//             ans += x;
//         }
//     }
//     cout << ans << endl;
//     return 0;
// }