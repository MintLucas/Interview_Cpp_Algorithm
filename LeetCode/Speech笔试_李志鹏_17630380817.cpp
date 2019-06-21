//#include <iostream>
//#include <vector>
//#include <string>
//#include <algorithm>
//using namespace std;
//
///*题目一：花费约16分钟。
//    有一个棋盘有n个格子。有一只青蛙在一开始处于0号格子。每个时刻，设青蛙当前处在第K个格子。它可以选择跳到第K + 1个格子或者第K + 2个格子。问，青蛙跳到第n个格子总共有多少种不同的跳法。
//
//思路：
//    一维动态规划问题，记DP[n]为青蛙跳到n个格子的跳法个数。
//
//    1.考虑边界条件：
//        DP[0] = 0
//        DP[1] = 1
//        DP[2] = 2
//
//    2.找状态转移方程：
//        DP[n] = n                                n = 0,1,2
//              = DP[n-1] + DP[n-2]                n > 2
//*/
//
//
//int jumpBoard(int n) {
//    //1.边界条件
//    if (n <= 2)
//        return n;
//
//    //本题一维DP且动规方程仅涉及前两个状态
//    //故用pre记录上一个状态用ppre记录上上个状态
//    int ppre = 1, pre = 2;
//    int cur = 0;
//
//    for (int i = 3; i <= n; ++i) {
//        //2.动规方程DP[n] = DP[n-1] + DP[n-2]
//        cur = ppre + pre;
//        ppre = pre;
//        pre = cur;
//    }
//    return cur;
//}
//
//
///*题目二：花费约38分钟。
//    给定两个字符串比如：ref=“思必驰有限公司”hyp=“四必吃限公司啊啊”。编辑距离定义为，使用填加，删除，替换三种操作将hyp串变为ref串所需要的最少个数。例子中编辑距离为5，“SCSDCCCII”。其中，S表示替换，C表示正确，D表示删除，I表示插入。输入：两个字符串
//    输出：这两个字符串的编辑距离
//
//思路：
//    二维动态规划问题，记m为串s1长度,n为串s2长度,dp[i][j]为字符串s1到s2的最小编辑距离。
//
//    1.考虑边界条件：
//        dp[0][0] = 0
//        dp[0][j] = j 当s1字符串为空时距离等于s2字串长度
//        dp[i][0] = i 当s2字符串为空时距离等于s1字串长度
//
//    2.找状态转移方程：
//        dp[i][j] = 0                                                i=0, j=0
//                 = i                                                i>0, j=0
//                 = j                                                i=0, j>0
//                 = dp[i-1][j-1]                                     s1[i] == s2[j]
//                 = min{dp[i-1][j]+1, dp[i][j-1]+1, dp[i-1][j-1]+1}  s1[i] != s2[j]
//
//    解释：类似LCS自顶向下考虑
//          当s1[i] == s2[j]即不用修改
//          当s1[i] != s2[j]对串s1有三种可能操作(对s2同理)
//
//            dp[i][j] = min{dp[i-1][j]+1, // 删除操作
//                        dp[i][j-1]+1,    // 插入操作
//                       dp[i-1][j-1]+1}   // 替换操作
//
//
//*/
//int minDistance(string s1, string s2) {
//    int m = s1.length();
//    int n = s2.length();
//
//    //1.初始化边界条件
//    vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));
//    for (size_t i = 0; i <= m; ++i)
//        dp[i][0] = i;
//    for (size_t j = 0; j <= n; ++j)
//        dp[0][j] = j;
//
//    //2.二维动规方程写为两层迭代
//    for(size_t i = 1; i <= m; ++i)
//        for (size_t j = 1; j <= n; ++j) {
//            if (s1[i - 1] == s2[j - 1])
//                dp[i][j] = dp[i - 1][j - 1];
//            else {
//                int temp = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
//                dp[i][j] = min(temp, dp[i - 1][j - 1] + 1);
//            }
//        }
//
//    return dp[m][n];
//}
//
////测试
//int main() {
//    int n = 7;
//    auto res1 = jumpBoard(n);
//    cout << "共有" << res1 << "种跳法" << endl;
//
//    string s1 = "Speech";
//    string s2 = "Sibichi";
//    auto res2 = minDistance(s1, s2);
//    cout << "最少需要" << res2 << "次修改" << endl;
//}
