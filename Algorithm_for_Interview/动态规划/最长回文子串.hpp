/*
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
*/
#pragma once

#include "../all.h"

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


void
solve()
{
    string s{ "abbaabccba" };
    auto ret = Solution().longestPalindrome(s);
    print(ret);
}