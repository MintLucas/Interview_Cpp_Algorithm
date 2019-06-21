#include <bits/stdc++.h>

using namespace std;


int main(){
    int N, M;
    cin >> N >> M;
    int c[1001][2];
    for(int i = 1; i <= N; i++){
        scanf("%d%d", &c[i][0], &c[i][1]);       
    }
    int dp[1001];
    //股票最低价>=1
    for(int i=1;i <= 1000;i++) dp[i] = i;

    for(int i = 1; i <= N; i++){
        for(int j = c[i][0]; j <= M; j++)
            dp[j] = max(dp[j], dp[j-c[i][0]] + c[i][1]);
        //按从大到小排序存入dp数组  
    }
    printf("%d\n", dp[M] - M);
    return 0;  
}

