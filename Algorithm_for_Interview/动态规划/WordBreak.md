动态规划问题​
记：
        dp[j] :                   子串 s[i..j)是否能被拆分为词典单词
    初始化：
        dp[0] = true         由于是右开空间s[0]预设为true方便遍历
    递推公式： 
        dp[j] = dp[i] && dp[i,j)即substr(i, j - i)           注意dp[j]是左闭右开空间
        
     
```cpp
class Solution {
public:
    bool wordBreak(string s, unordered_set<string> &dict) {
        vector<bool> dp(s.size() + 1);
        dp[0] = true;
        //字符串结束位置,左闭右开s[i,j)
        for(auto j = 1; j <= s.size(); ++j)
            for(auto i = j - 1; i >= 0; --i){//字符串起始位置
                if(dp[i] && dict.find(s.substr(i, j - i)) != dict.end()){
                    dp[j] = true;
                    break;
                }
            }
        return dp[s.size()];
        
    }
};
```