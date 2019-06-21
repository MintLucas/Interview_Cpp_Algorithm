516. ����������� - LeetCode (�й�) https://leetcode-cn.com/problems/longest-palindromic-subsequence/description/

��Ŀ������
    ����һ���ַ���s���ҵ�������Ļ��������С����Լ���s����󳤶�Ϊ1000��

    ʾ�� 1:
        ����:
            "bbbab"
        ���:
            4
        һ�����ܵ������������Ϊ "bbbb"��

    ʾ�� 2:
        ����:
            "cbbd"
        ���:
            2
        һ�����ܵ������������Ϊ "bb"��

˼·��
    ����Ķ�̬�滮����
    �ǣ�
        dp[i][j] := �Ӵ� s[i..j] ������������еĴ�С
    ��ʼ����
        dp[i][j] = 1    i=j //s[i..i]Ϊ������ĸ,��s[0][0]��ȷ��֪��
                 = 0    other
    ���ƹ�ʽ��
        dp[i][j] = dp[i+1][j-1] + 2             s[i]==s[j]
                 = max(dp[i+1][j], dp[i][j-1])  other
                 
    1.���str�����һ��Ԫ�غ͵�һ��Ԫ������ͬ�ģ����У�lps(0,n-1)=lps(1,n-2)+2�������ַ������С�AABACACBA������һ��Ԫ�غ����һ��Ԫ����ͬ������lps(1,n-2)��ʾ��ɫ���ֵ�����������еĳ��ȣ�

    2.���str�����һ��Ԫ�غ͵�һ��Ԫ���ǲ���ͬ�ģ����У�lps(0,n-1)=max(lps(1,n-1),lps(0,n-2))�������ַ������С�ABACACB��������lps(1,n-1)��ʾȥ����һԪ�ص������У�lps(0,n-2)��ʾȥ�����һ��Ԫ�ص������С�
    
        ��� `i+1=j` �� `s[i]=s[j]`ʱ��`dp[i][j] = dp[i+1][j-1] + 2` ��Ȼ������
        ��Ϊ `i != j` ʱ���� `dp[i][j] = 0`

    ע�⣬������������ dp ���壬����ֵӦ���� dp[1][n] ������ dp[n][n]

    ����״̬ת��֮��Ĺ�ϵ��������ж�̬�滮����Ĺؼ���Ҳ���ѵ�
        s[i]==s[j] ʱ��s[i..j] ����һ��״̬Ӧ���� s[i+1..j-1]����ͷ������������ s[i+1..j+1] ����������������һ������Ȿ��Ĺؼ�
        s[i]!=s[j] ʱ��s[i..j] ����һ��״̬Ӧ���� s[i+1..j] �� s[i..j-1]
    �ݲ����� DP ���Ż�
    

    ״̬���µ�˳��Ҳ��һ��ע��㣺
    Ϊ��ö�ٸ����ַ������������ַ�����������Ҫö�����ǿ�ʼ�ͽ�����������
    ���迪ʼ�ͽ����������ֱ�Ϊ i �� j��
    ��ô������  0��i<j��n ������Ľ������� j �ǰ������ų��ģ�
    
    ��ȷʾ����
            
        //abcdef a-a-1 ... c-c-1����λ�ÿ���ȫ��
        for (int j = 1; j < n; j++)             // �Ӵ�����λ��
            for (int i = j-1; i >=0; i--) {     // �Ӵ���ʼλ��
            
        //abcdef f-f+1 ... d-d+1��ʼλ�ÿ���ȫ��
        for (int i = n-1; i >= 0; i--)          // �Ӵ���ʼλ��(>=0)
            for (int j = i + 1; j < n; j++) {   // �Ӵ�����λ��(<n)
            
        for (int j = 1; j < n; j++)             //�Ӵ�����(s[i..i+j])
            for (int i = 0; j + i < n; i++){    //�Ӵ���ʼλ��(��ʼ������������<n)
            
        for (int j = 1; j <= n; j++)            //�Ӵ����Ȼ��0��Ҳ�ǽ���λ�õĿ�����)
            for (int i = 0; i < j; i++)         //�Ӵ���ʼλ�û�ָ�λ�û��Ǵ�(j-1->0]
            
        s[i,j]������ȡsubΪj-i+1

    ����ʾ����
        for (int j = 1; j < n; j++)         // �Ӵ�����λ��
            for (int i = 0; i < j; i++) {   // �Ӵ���ʼλ��
        // ���Ǹ�˳���� "./������Ӵ�.hpp" ������ȷ��

    ע�⣺
        ��Ϊ DP �Ķ���Ϊ�˱�����⣬�±곣�� 1 ��ʼ������һ���������±겻ͬ������
        Ӧ��ʹ�ñ���ʱӦ��ʹ�� `s[i-1]==s[j-1]` ������ `s[i]==s[j]`

        **��ȻҲ�����ڱ���ʱ�� DP ���±�Ҳ�������� 0 ��ʼ**
        
    �������ֻ����������������еĳ��ȣ�һ����������Ҳֻ��Ҫ�󷵻س��ȼ��ɡ�
    ���������Ҳ��֪������������о�����ɶ������Զ������һ��������¼���������������Щ�ַ�������ά��һ����Ϊ lps[j][i + j]��ֵΪ String �� map��


```cpp
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.length();

        /* ��ֱ�۵�ѭ����ʽ
        */
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
            dp[i][i] = 1;
            
        for (int j = 1; j < n; j++)             // �Ӵ�����λ��
            for (int i = j-1; i >=0; i--) {     // �Ӵ���ʼλ��
                if (s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max({ dp[i + 1][j], dp[i][j - 1] });
            }

        return dp[0][n - 1];

        /* �±�� 0 ��ʼ
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
            dp[i][i] = 1;
            
        for (int i = n-1; i >= 0; i--)          // �Ӵ���ʼλ��(>=0)
            for (int j = i + 1; j < n; j++) {   // �Ӵ�����λ��(<n)
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
        
        for(int j = 1; j < n; ++j)             //�Ӵ�����(s[i..i+j]
            //ע��˴�Ϊi+j<len
            for(int i = 0; i + j < n; ++i){    //�Ӵ���ʼλ��(��ʼ������������<n)
                //s[i...i+j]
                if(s[i] == s[i+j])
                    dp[i][i+j] = dp[i+1][i+j-1] + 2;
                else
                    dp[i][i+j] = max(dp[i+1][i+j], dp[i][i+j-1]);
            }
        
        return dp[0][n-1];
        */
         
        /*�±�� 1 ��ʼ
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        //��ʼ��ʱ�ǵ�i<=n
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


5. ������Ӵ� - LeetCode (�й�) https://leetcode-cn.com/problems/longest-palindromic-substring/description/

����������
    ����һ���ַ��� s���ҵ� s ����Ļ����Ӵ�������Լ��� s ����󳤶�Ϊ1000��

    ʾ�� 1��
        ����: "babad"
        ���: "bab"
        ע��: "aba"Ҳ��һ����Ч�𰸡�
    ʾ�� 2��
        ����: "cbbd"
        ���: "bb"

˼·��
    ��̬�滮
    ���ֻ����������Ӵ��ĳ��ȣ�����ƹ�ʽ�� "�����������" ��ȫ��ͬ

    ������Ҫ����������Ӵ�����Ҫ���¶��� dp

    ���壺
        dp[i][j] := �Ӵ� s[i..j] �Ƿ��ǻ����Ӵ�
    ��ʼ��
        dp[i][j] = true     i=j
                 = false    other
    ���ƹ�ʽ��
        dp[i][j] = s[i]==s[j]                   j-i=1
                 = s[i]==s[j]&&dp[i+1][j-1]      j-i>1

    ������˶�̬�滮����һ���ѵ�����α�������һ���Ӵ�


```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();

        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        //���±�����¼,��ֹ���ֵ�һ�������
        int max_len = 1;    //����������Ӵ�����
        int start = 0;      //����������Ӵ����
        
        //��string max_str;��j=i��ʼ,���㵥һ���ĵ����
        //max_str = s.substr(i, j-i+1); return max_str;
        
        for (int i = 0; i < n; i++)
            dp[i][i] = 1;

        //for (int j = 1; j < n; j++)         // �Ӵ�����λ��
        //    for (int i = 0; i < j; i++) {   // �Ӵ���ʼλ��
        // ���ϣ�ѭ����ʽ����ȷ�ģ����� "./�����������" �в���
        // ���£������������ж���ȷ
        for (int j = 1; j < n; j++)             // �Ӵ�����λ��
            for (int i = j - 1; i >= 0; i--) {  // �Ӵ���ʼλ��
                if (j - i < 2)
                    dp[i][j] = (s[i] == s[j]);
                else
                    dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);

                // �����Ӵ�
                if (dp[i][j] && (j - i + 1) >= max_len) {
                    max_len = j - i + 1;
                    start = i;
                }
            }
        return s.substr(start, max_len);
    }
};
```


�տ�ʼ���뷨��ֱ��DFS�����ᳬʱ��Ҳ��¼һ�°�

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