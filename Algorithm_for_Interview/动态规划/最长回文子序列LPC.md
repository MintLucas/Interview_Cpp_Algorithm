516. 最长回文子序列 - LeetCode (中国) https://leetcode-cn.com/problems/longest-palindromic-subsequence/description/

题目描述：
    给定一个字符串s，找到其中最长的回文子序列。可以假设s的最大长度为1000。

    示例 1:
        输入:
            "bbbab"
        输出:
            4
        一个可能的最长回文子序列为 "bbbb"。

    示例 2:
        输入:
            "cbbd"
        输出:
            2
        一个可能的最长回文子序列为 "bb"。

思路：
    经典的动态规划问题
    记：
        dp[i][j] := 子串 s[i..j] 的最长回文子序列的大小
    初始化：
        dp[i][j] = 1    i=j //s[i..i]为单个字母,即s[0][0]已确定知道
                 = 0    other
    递推公式：
        dp[i][j] = dp[i+1][j-1] + 2             s[i]==s[j]
                 = max(dp[i+1][j], dp[i][j-1])  other
                 
    1.如果str的最后一个元素和第一个元素是相同的，则有：lps(0,n-1)=lps(1,n-2)+2；例如字符串序列“AABACACBA”，第一个元素和最后一个元素相同，其中lps(1,n-2)表示红色部分的最长回文子序列的长度；

    2.如果str的最后一个元素和第一个元素是不相同的，则有：lps(0,n-1)=max(lps(1,n-1),lps(0,n-2))；例如字符串序列“ABACACB”，其中lps(1,n-1)表示去掉第一元素的子序列，lps(0,n-2)表示去掉最后一个元素的子序列。
    
        如果 `i+1=j` 且 `s[i]=s[j]`时，`dp[i][j] = dp[i+1][j-1] + 2` 依然成立，
        因为 `i != j` 时，有 `dp[i][j] = 0`

    注意，如果按照上面的 dp 定义，返回值应该是 dp[1][n] 而不是 dp[n][n]

    明白状态转移之间的关系是理解所有动态规划问题的关键，也是难点
        s[i]==s[j] 时，s[i..j] 的上一个状态应该是 s[i+1..j-1]，两头收缩，而不是 s[i+1..j+1] 或者其他，明白这一点是理解本题的关键
        s[i]!=s[j] 时，s[i..j] 的上一个状态应该是 s[i+1..j] 或 s[i..j-1]
    暂不考虑 DP 的优化
    

    状态更新的顺序也是一个注意点：
    为了枚举给定字符串的所有子字符串，我们需要枚举它们开始和结束的索引。
    假设开始和结束的索引分别为 i 和 j。
    那么我们有  0≤i<j≤n （这里的结束索引 j 是按惯例排除的）
    
    正确示例：
            
        //abcdef a-a-1 ... c-c-1结束位置控制全局
        for (int j = 1; j < n; j++)             // 子串结束位置
            for (int i = j-1; i >=0; i--) {     // 子串开始位置
            
        //abcdef f-f+1 ... d-d+1开始位置控制全局
        for (int i = n-1; i >= 0; i--)          // 子串开始位置(>=0)
            for (int j = i + 1; j < n; j++) {   // 子串结束位置(<n)
            
        for (int j = 1; j < n; j++)             //子串长度(s[i..i+j])
            for (int i = 0; j + i < n; i++){    //子串开始位置(开始到结束闭区间<n)
            
        for (int j = 1; j <= n; j++)            //子串长度或从0算也是结束位置的开区间)
            for (int i = 0; i < j; i++)         //子串开始位置或分割位置还是从(j-1->0]
            
        s[i,j]闭区间取sub为j-i+1

    错误示例：
        for (int j = 1; j < n; j++)         // 子串结束位置
            for (int i = 0; i < j; i++) {   // 子串起始位置
        // 但是该顺序在 "./最长回文子串.hpp" 中是正确的

    注意：
        因为 DP 的定义为了便于理解，下标常从 1 开始，这与一般容器的下标不同，所以
        应该使用编码时应该使用 `s[i-1]==s[j-1]` 而不是 `s[i]==s[j]`

        **当然也可以在编码时将 DP 的下标也调整至从 0 开始**
        
    最后，这题只返回了最长回文子序列的长度，一般面试题中也只是要求返回长度即可。
    但是如果你也想知道最长回文子序列具体是啥，这可以额外添加一个变量记录最长回文子序列是哪些字符，例如维护一个键为 lps[j][i + j]，值为 String 的 map。


```cpp
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.length();

        /* 更直观的循环方式
        */
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
            dp[i][i] = 1;
            
        for (int j = 1; j < n; j++)             // 子串结束位置
            for (int i = j-1; i >=0; i--) {     // 子串开始位置
                if (s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max({ dp[i + 1][j], dp[i][j - 1] });
            }

        return dp[0][n - 1];

        /* 下标从 0 开始
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
            dp[i][i] = 1;
            
        for (int i = n-1; i >= 0; i--)          // 子串开始位置(>=0)
            for (int j = i + 1; j < n; j++) {   // 子串结束位置(<n)
                if (s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max({ dp[i + 1][j], dp[i][j - 1] });
            }

        return dp[0][n-1];
        */
        
        /*
        int n = s.size();
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        for(int i = 0; i < n; ++i)
            dp[i][i] = 1;
        
        for(int j = 1; j < n; ++j)             //子串长度(s[i..i+j]
            //注意此处为i+j<len
            for(int i = 0; i + j < n; ++i){    //子串开始位置(开始到结束闭区间<n)
                //s[i...i+j]
                if(s[i] == s[i+j])
                    dp[i][i+j] = dp[i+1][i+j-1] + 2;
                else
                    dp[i][i+j] = max(dp[i+1][i+j], dp[i][i+j-1]);
            }
        
        return dp[0][n-1];
        */
         
        /*下标从 1 开始
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        //初始化时记得i<=n
        for (int i = 1; i <= n; i++)
            dp[i][i] = 1;
            
        for (int i = n; i >=1; i--)
            for (int j = i+1; j <= n; j++) {
                if (s[i-1] == s[j-1])
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max({ dp[i + 1][j], dp[i][j - 1] });
            }
        
        return dp[1][n];
        */
    }
};

int main(){
    string t = "cbbd";
    int res = Solution().longestPalindromeSubseq(t);
    
}
```


5. 最长回文子串 - LeetCode (中国) https://leetcode-cn.com/problems/longest-palindromic-substring/description/

问题描述：
    给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为1000。

    示例 1：
        输入: "babad"
        输出: "bab"
        注意: "aba"也是一个有效答案。
    示例 2：
        输入: "cbbd"
        输出: "bb"

思路：
    动态规划
    如果只是求最长回文子串的长度，其递推公式与 "最长回文子序列" 完全相同

    这里需要给出具体的子串，需要重新定义 dp

    定义：
        dp[i][j] := 子串 s[i..j] 是否是回文子串
    初始化
        dp[i][j] = true     i=j
                 = false    other
    递推公式：
        dp[i][j] = s[i]==s[j]                   j-i=1
                 = s[i]==s[j]&&dp[i+1][j-1]      j-i>1

    本题除了动态规划的另一个难点是如何保存其中一个子串


```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();

        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        //用下标来记录,防止出现单一回文情况
        int max_len = 1;    //保存最长回文子串长度
        int start = 0;      //保存最长回文子串起点
        
        //或string max_str;但j=i开始,计算单一回文的情况
        //max_str = s.substr(i, j-i+1); return max_str;
        
        for (int i = 0; i < n; i++)
            dp[i][i] = 1;

        //for (int j = 1; j < n; j++)         // 子串结束位置
        //    for (int i = 0; i < j; i++) {   // 子串起始位置
        // （上）循环方式是正确的，但在 "./最长回文子序列" 中不对
        // （下）在两个问题中都正确
        for (int j = 1; j < n; j++)             // 子串结束位置
            for (int i = j - 1; i >= 0; i--) {  // 子串开始位置
                if (j - i < 2)
                    dp[i][j] = (s[i] == s[j]);
                else
                    dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);

                // 保存子串
                if (dp[i][j] && (j - i + 1) >= max_len) {
                    max_len = j - i + 1;
                    start = i;
                }
            }
        return s.substr(start, max_len);
    }
};
```


刚开始的想法是直接DFS，但会超时，也记录一下吧

```cpp
bool isPalindrome1(string s){
    return s == string(s.rbegin(), s.rend());
}
void dfsPalindrome(string s, string &res){
    if(s == "")
        return ;
    for (int i = 1; i <= s.size(); ++i) {
        string temp = s.substr(0, i);
        if(isPalindrome1(temp)){
            if(temp.size() > res.size())
                res = temp;
            dfsPalindrome(s.substr(i), res);
        }
    }
}
string longestPalindrome(string s) {
    string res;
    dfsPalindrome(s, res);
    return res;
}
```