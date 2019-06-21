/*
72. 编辑距离 - LeetCode https://leetcode.com/problems/edit-distance/submissions/

    解析：https://github.com/youngwind/blog/issues/106

问题描述：
    给定两个单词 word1 和 word2，计算出将 word1 转换成 word2 所使用的最少操作数 。
    你可以对一个单词进行如下三种操作：
        插入一个字符
        删除一个字符
        替换一个字符
    示例 1:
        输入: word1 = "horse", word2 = "ros"
        输出: 3
        解释:
            horse -> rorse (将 'h' 替换为 'r')
            rorse -> rose (删除 'r')
            rose -> ros (删除 'e')
    示例 2:
        输入: word1 = "intention", word2 = "execution"
        输出: 5
        解释:
            intention -> inention (删除 't')
            inention -> enention (将 'i' 替换为 'e')
            enention -> exention (将 'n' 替换为 'x')
            exention -> exection (将 'n' 替换为 'c')
            exection -> execution (插入 'u')

思路：
    动态规划-经典问题

    记两个字符串分别为 A[0..m-1] 和 B[0..n-1]
    记 dp[i][j] := 串A 前 i 个字符与 串B 前 j 个字符的编辑距离

    1. 考虑边界情况：其中一个字符串为空串，显然此时从 s[0..i-1] 转换为 "" 至少需要 i次 操作，因此有

        dp[i][0] = i
        dp[0][j] = j

    2. 一般情况，考虑 A串的第 i 个字符和 B串的第 j 个字符
        假设已知 dp[i-1][j-1]，即从 A[0..i-2] 转换为 B[0..j-2] 需要的次数
        1）如果 A[i] == B[j]，那么 dp[i][j] == dp[i-1][j-1]
        2）如果 A[i] != B[j]，对串A 有三种可能的操作（对串B 是对称的）：
            a. 替换一个字符 dp[i][j] = dp[i-1][j-1] + 1
            b. 删除一个字符 dp[i][j] = dp[i-1][j] + 1，此时应有 A[0..i-2] == B[0..j-1]，所以需要从 A 删除中的一个字符
            c. 插入一个字符 dp[i][j] = dp[i][j-1] + 1，此时应有 A[0..i-1] == B[0..j-2]，所以需要向 A 插入中的一个字符
        
        问题的难点在于理解后这 3 种情况

    由此可得递推公式：

        dp[i][j] = 0                                                i=0, j=0
                 = i                                                i>0, j=0
                 = j                                                i=0, j>0
                 = dp[i-1][j-1]                                     A[i-1] == B[j-1]
                 = min{dp[i-1][j]+1, dp[i][j-1]+1, dp[i-1][j-1]+1}  A[i-1] != B[j-1]

    原帖还提供了空间优化的方案，只需要 O(m) 或 O(n) 的空间复杂度，这里不再深入。



如果 a[m] === b[n]，那么问题转化为求解：a[1]a[2]...a[m-1] => b[1]b[2]...b[n-1] 的最小编辑距离，因此 d[m][n] === d[m-1][n-1]。比如，"xyz" => "pqz" 的最小编辑距离等于 "xy" => "pq" 的最小编辑距离。
如果 a[m] !== b[n]，又分为三种情况：
比如，"xyz" => "efg" 的最小编辑距离等于 "xy" => "efg" 的最小编辑距离 + 1（因为允许插入操作，插入一个 "z"），抽象的描述便是 d[m][n] === d[m-1][n] + 1。
比如，"xyz" => "efg" 的最小编辑距离等于 "xyzg" => "efg" 的最小编辑距离 + 1，且因为最后一个字符都是 "g"，根据第一个判断条件，可以再等于 "xyz" => "ef" 的最小编辑距离 + 1，因此，得到结论："xyz" => "efg" 的最小编辑距离等于 "xyz" => "ef" 的最小编辑距离 + 1，抽象的描述便是：d[m][n] === d[m][n-1] + 1。
比如，"xyz" => "efg" 的最小编辑距离等于 "xyg" => "efg" 的最小编辑距离 + 1（因为允许替换操作，可以把 "g" 换成 "z"），再等于 "xy" => "ef" 的编辑距离 + 1（根据第一个判断条件），抽象的描述便是： d[m][n] === d[m-1][n-1] + 1。
上述三种情况都有可能出现，因此，取其中的最小值便是整体上的最小编辑距离。

动态规划看起来跟递归很像，不过推理逻辑正好是反过来的。递归的逻辑是：“要求得 d[m][n]，先要求得 d[m-1][n-1]……”，动态规划的逻辑是：“先求得 d[m-1][n-1]，再求 d[m][n]……”这是它们的主要区别。
举个例子，在已知 d[0][0]，d[0][1]，d[1][0] 的前提下，要求 d[1][1]：

如果 a[1] === b[1]，那么 d[1][1] 等于 d[0][0]，也就是 0；
如果 a[1] !== b[1]，那么 d[1][1] 等于 d[0][1]、d[1][0] 和 d[0][0] 三者中的最小值 + 1，也就是 1。
接着用同样的方式，可以求得 d[1][2]、d[1][3]、……、d[1][n]，然后继续求得 d[2][1]、d[2][2]、……、d[2][n]，一直到 d[m][n]。代码实现如下：


```cpp
int minDistance(string word1, string word2) {
    int l1 = word1.size(), l2 = word2.size();
    if(l1 == 0) return l2;
    if(l2 == 0) return l1;
    vector<vector<int>> dp(l1+1, vector<int>(l2+1, 0));
    
    for(int i = 0; i <= l1; ++i)
        dp[i][0] = i;
    for(int j = 0; j <= l2; ++j)
        dp[0][j] = j;
    
    for(int m = 1; m <= l1; ++m){
        for(int n = 1; n <= l2; ++n){
            if(word1[m-1] == word2[n-1])
                dp[m][n] = dp[m-1][n-1];
            else{
                int min1 = min(dp[m-1][n]+1, dp[m][n-1]+1);
                dp[m][n] = min(min1, dp[m-1][n-1]+1);
            }
        }
    }
    return dp[l1][l2];
}
```