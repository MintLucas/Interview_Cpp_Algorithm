#include "LeetCode01_10.hpp"
#include <cctype>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <numeric>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include "BTree.hpp"
#include "01_ListNode.hpp"
#include "LeetCodeTopInterview01_20.hpp"

vector<int> twoSum(vector<int> &numbers, int target) {
    vector<int> res;
    map<int, int> m;
    for (int i = 0; i < numbers.size(); ++i) {
        int a = target - numbers[i];
        if(m.find(a) == m.end())
            //key到下标位置的map
            m[numbers[i]] = i + 1;
        else{
            //找到了就把找到的下标放进去
            res.push_back(m[a]);
            //当前下标放进去
            res.push_back(i + 1);
            return res;
        }
    }
    return res;
}
vector<int> twoSum2(vector<int> &numbers, int target){
    vector<int> res;
    int i = 0, j = numbers.size() - 1;
    while (i < j) {
        if (numbers[i] + numbers[j] == target) {
            res.push_back(i+1);
            res.push_back(j+1);
            //去重
            while(i < j && numbers[i] == numbers[i+1]) ++i;
            while(i < j && numbers[j] == numbers[j-1]) --j;
            ++i, --j;
        }
        //针对有序数组才行,threeSum里前提排序
        else if(numbers[i] + numbers[j] < target){
            ++i;
        }
        else if(numbers[i] + numbers[j] > target)
            --j;
    }
    return res;
}

int lengthOfLongestSubstring(string s) {
    if(s.size() < 2) return s.size();
    int idx = 0;
    int max = 0;
    for(int i = 1; i <= s.size(); ++i){
        string temp =s.substr(idx, i-idx);
        if(i == s.size() && temp.size() > max){
            max = temp.size();
            break;
        }
        if(temp.find(s[i]) != -1){
            idx = s.substr(0, i).rfind(s[i])+1;
            if(temp.size() > max) max = temp.size();
        }
    }
    return max;
}

int lengthOfLongestSubstring1(string s) {
    int n = s.size();
    set<char> set;
    int i = 0, j = 0, res = 0;
    //s[i,j) 0 <= i < j < n
    while(i < n && j < n){
        // try to extend the range [i, j)
        if(set.find(s[j]) == set.end()){
            set.insert(s[j++]);
            res = max(res, j - i);
        }
        else
            set.erase(s[i++]);
    }
    return res;
}

int lengthOfLongestSubstring2(string s) {
    int n = s.size();
    map<char, int> mp;
    int i = 0, j = 0, res = 0;
    //s[i,j) 0 <= i < j < n
    for (; j != n; ++j) {
        if(mp.find(s[j]) != mp.end()){
            i = max(i, mp[s[j]]);
        }
        //已存在key值再插入key无法更新value值,需要单独处理
        auto ret = mp.insert(pair<char, int>(s[j], j));
        //insert返回pair<map<char, int>::iterator, bool>
        
        if(!ret.second)
            ret.first->second = max(res, j - i);
    }
    return res;
}

int lengthOfLongestSubstring3(string s) {
    vector<int> dict(256, -1);
    int maxLen = 0, start = -1;
    for (int j = 0; j != s.length(); j++) {
        //已存在，更新起点和下标索引
        if (dict[s[j]] > start)
            start = dict[s[j]];
        dict[s[j]] = j;
        //左开右闭(start,j]
        maxLen = max(maxLen, j - start);
    }
    return maxLen;
}

int lengthOfLongestSubstring4(string s) {
    vector<int> dict(256, 0);
    int maxLen = 0, start = 0;
    for (int j = 0; j != s.length(); j++) {
        //已存在，更新起点和下标索引
        if (dict[s[j]] > start)
            start = dict[s[j]];
        //直接跳到重复的下一个单词处
        dict[s[j]] = j + 1;
        //左闭右闭[start,j]
        maxLen = max(maxLen, j - start + 1);
    }
    return maxLen;
}

int sumOfVector(vector<int> sum){
    int res = 0;
    for(int i = 0; i < sum.size(); ++i){
        res *= 10;
        res +=  sum[i];
    }
    return res;
}
int sumNumbers(TreeNode *root){
    TreeNode* stk[1000] = {0};
    int top = -1;
    TreeNode *cur = root, *f_last = NULL;
    vector<int> res;
    long long totalSum = 0;
    while(cur || top != -1){
        if(cur){
            stk[++top] = cur;
            cur = cur->left;
        }
        else{
            cur = stk[top];
            if(cur->right && f_last != cur->right){
                cur = cur->right;
            }
            else{
                f_last = cur;
                if(cur->left == NULL && cur->right == NULL){
                    vector<int> sum;
                    for(int i = 0; i <= top; ++i)
                        sum.push_back(stk[i]->val);
                    res.push_back(sumOfVector(sum));
                }
                top--;
                cur = NULL;
            }
        }
    }
    for (int i = 0; i < res.size(); ++i)
        totalSum += res[i];
    return totalSum;
}

int longestConsecutive(vector<int> &num){
    unordered_set<int> st(num.begin(), num.end());
    int pre, aft, len = 0;
    for (int i = 0; i < num.size(); ++i) {
        if(st.find(num[i]) != st.end()){
            pre = num[i];
            while(st.find(--pre) != st.end()) st.erase(pre);
            aft = num[i];
            while(st.find(++aft) != st.end())
                st.erase(aft);
            len = max(len, aft-pre-1);
        }
    }
    return len;
}

//用迭代器达到和a[]一样的效果
double findKthMin(vector<int>::iterator a, int m, vector<int>::iterator b, int n, int k){
    //asume m<=n
    if(m > n)
        return findKthMin(b, n, a, m, k);
    
    //assume nums1 and nums2 cannot be both empty
    if(m == 0)
        return b[k-1];
    
    if(k == 1)
        return min(a[0], b[0]);
    
    //每次找k/2小数组可能小于这个值则全部抛弃
    int pa = min(k/2, m), pb = k - pa;
    
    //devide and conquer
    if(a[pa - 1] < b[pb - 1])
        return findKthMin(a + pa, m - pa, b, n, k - pa);
    else if(b[pb - 1] < a[pa - 1])
        return findKthMin(a, m, b + pb, n - pb, k - pb);
    else
        return a[pa - 1];
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    vector<int>::iterator a = nums1.begin();
    vector<int>::iterator b = nums2.begin();
    int total = nums1.size() + nums2.size();
    
    //向下取整,这里仅考虑第几小不在0下标范围因此/2后要+1
    if(total & 0x1)
        return findKthMin(a, nums1.size(), b, nums2.size(), total/2 + 1);
    else
        return (findKthMin(a, nums1.size(), b, nums2.size(), total/2) + findKthMin(a, nums1.size(), b, nums2.size(), total/2 + 1))/2;
}

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

int longestPalindromeSubseq(string s) {
    int n = s.size();
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
    for(int i = 0; i < n; ++i)
        dp[i][i] = 1;
    
    for(int j = 1; j < n; ++j)
        //注意此处为i+j<len
        for(int i = 0; i + j < n; ++i){
            //s[i...i+j]
            if(s[i] == s[i+j])
                dp[i][i+j] = dp[i+1][i+j-1] + 2;
            else
                dp[i][i+j] = max(dp[i+1][i+j], dp[i][i+j-1]);
        }
    
    return dp[0][n-1];
    
}

string longestPalindromeStr(string s) {
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

int reverse(int x) {
    long long res;
    while (x) {
        res = res*10 + x%10;
        x = x/10;
    }
    return (res > INT_MAX || res < INT_MIN) ? 0 : res;
}

int myAtoi(string str) {
    if(str.size() < 1) return 0;
    int flag = 1, i = 0;
    //先过滤空格
    while(isspace(str[i]))
        ++i;
    if(str[i] == '-' || str[i] == '+'){
        if(str[i] == '-') flag = -1;
        ++i;
    }
    long long res = 0;
    if(isdigit(str[i])){
        int tail = 0;
        while (isdigit(str[i])) {
            tail = (str[i] - '0') % 10;
            res = res*10 + tail;
            if(++i > 9)
                break;
        }
    }
    else
        return 0;
    res = (res*flag > INT_MAX || res*flag  < INT_MIN) ? 0 : res*flag;
    return res;
}

bool isPalindrome(int x) {
    //最后一个元素为0前面没有元素为0
    if(x < 0 || (x!=0 && x%10==0)) return false;
    int sum = 0;
    while(x > sum){
        sum = sum*10 + x%10;
        x /= 10;
    }
    //一半考虑奇偶，10的整数倍最后都会为0
    return sum == x || sum/10 == x ;
}

int maxArea(vector<int>& height) {
    int res = 0, l = 0, r = height.size() - 1;
    while(l < r){
        int h = min(height[l], height[r]);
        res = max(res, (r-l)*h);
        while(height[l] <= h && l < r) ++l;
        while(height[r] <= h && l < r) --r;
    }
    return res;
}

int romanToInt(string s) {
    if(s.size() < 1) return 0;
    map<char, int> mp = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
    int sum = mp[s.back()];
    for (int i = s.size() - 2; i >= 0; --i) {
        //当前比之后的小则减去，逆序遍历之后的已经加过
        if(mp[s[i]] < mp[s[i+1]])
            sum -= mp[s[i]];
        else
            sum += mp[s[i]];
    }
    
//    for (int i = 0; i < s.size(); ++i) {
//        if(mp[s[i]] == 1 && (mp[s[i+1]] == 5 || mp[s[i+1]] == 10)){
//            sum += mp[s[i+1]] - mp[s[i]];
//            ++i;
//        }
//        else if(mp[s[i]] == 10 && (mp[s[i+1]] == 50 || mp[s[i+1]] == 100)){
//            sum += mp[s[i+1]] - mp[s[i]];
//            ++i;
//        }
//        else if(mp[s[i]] == 100 && (mp[s[i+1]] == 500 || mp[s[i+1]] == 1000)){
//            sum += mp[s[i+1]] - mp[s[i]];
//            ++i;
//        }
//        else
//            sum += mp[s[i]];
//    }
    return sum;
}

string longestCommonPrefix(vector<string>& strs) {
    string res;
    if(strs.size() < 1) return res;
    sort(strs.begin(), strs.end(), [] (const string &a, const string &b) { return a.size() < b.size(); });
    for (int i = 1; i <= strs[0].size(); ++i) {
        string temp = strs[0].substr(0, i);
        static bool flag = true;
        for_each(strs.begin(), strs.end(), [temp] (const string &s) mutable { if(s.find(temp, 0) == string::npos) flag = false;});
        if(flag == true)
            res = temp;
        else
            break;
    }
    return res;
}
string longestCommonPrefix2(vector<string>& strs) {
    string res;
    if(strs.size() < 1) return res;
    sort(strs.begin(), strs.end());
    string first = strs[0], last = strs[strs.size() - 1];
    
    int dif = min(first.size(), last.size());
    
    for(int i = 1; i <= dif; ++i){
        if(first[i - 1] == last[i - 1])
            res = first.substr(0, i);
        else
            break;
    }
    return res;
}


void threeSumCore(set<vector<int>> &res, vector<int> &cur, vector<int> &nums, vector<int>::iterator p,int dep){
    if(dep == 4){
        if(accumulate(cur.begin(), cur.end(), 0) == 0)
            res.insert(cur);
        return;
    }
    for (; p != nums.end(); ++p) {
        cur.push_back(*p);
        threeSumCore(res, cur, nums, p + 1, dep + 1);
        cur.pop_back();
    }
}

vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    set<vector<int>> temp;
    if(nums.size() < 1) return res;
    
    //关键要素，排序组合一致，最后结果则相邻，结果再去重
    sort(nums.begin(), nums.end());
    vector<int> cur;
    threeSumCore(temp, cur, nums, nums.begin(), 1);
    for(auto i : temp)
        res.push_back(i);
    return res;
}
vector<vector<int>> threeSum2(vector<int>& nums) {
    vector<vector<int>> res;
    if(nums.size() < 1) return res;
    sort(nums.begin(), nums.end());
    for (int k = 0; k < nums.size(); ++k) {
        //已排序如果第一个都大于0则没有之和为0的组合
        if(nums[k] > 0)
            break;
        //跳过重复的元素
        if(k > 0 && nums[k] == nums[k-1])
            continue;
        //转换为twoSum求固定和的问题，但要考虑重复
        int target = -nums[k];
        int i = k + 1, j = nums.size() - 1;
        while (i < j) {
            //可以nums[i]+nums[j]+nums[k]=0固定一个一样的
            if (nums[i] + nums[j] == target) {
                res.push_back({nums[k], nums[i], nums[j]});
                //去重
                while(i < j && nums[i] == nums[i+1]) ++i;
                while(i < j && nums[j] == nums[j-1]) --j;
                ++i;
                --j;
            }
            else if(nums[i] + nums[j] < target){
                ++i;
            }
            else if(nums[i] + nums[j] > target)
                --j;
        }
    }
    return res;
}

int threeSumClosest(vector<int>& nums, int target) {
    int res = 0, ret = 0, min_dif = INT_MAX;
    if(nums.size() < 1) return res;
    sort(nums.begin(), nums.end());
    //三个数第一个数遍历到n-2即可
    for (int k = 0; k < nums.size() - 2; ++k) {
        //转换为twoSum求固定和的问题，但要考虑重复
        int twoSum = target-nums[k];
        int i = k + 1, j = nums.size() - 1;
        while (i < j) {
            if(nums[i] + nums[j] < twoSum)
                ++i;
            else
                --j;
        }
        //放在while里不必跳出i=j判断从那边返回
        //这里res保存的距离，直接保存和可以减和来算最小
        if(j == nums.size() - 1 || abs(twoSum - nums[i-1] - nums[i]) < abs(twoSum - nums[i] - nums[i+1]))
           res = twoSum - nums[i-1] - nums[i];
        else
            res = twoSum - nums[i] - nums[i+1];
    
        if(res < min_dif){
            min_dif = res;
            ret = nums[k] + nums[i] + nums[j];
        }
    }

    return res;
}
int threeSumClosest2(vector<int>& nums, int target) {
    if(nums.size() < 3) return 0;
    int n = nums.size();
    sort(nums.begin(), nums.end());
    
    //按照需求设一个值后梯度下降类似min=vec[0]
    int res = nums[0] + nums[1] + nums[n-1];
    for(int k = 0; k < n - 2; ++k){
        int i = k+1, j = n - 1;
        while(i < j){
            //不要吝啬重新定义一个值
            int sum = nums[k] + nums[i] + nums[j];
            if(sum < target)
                ++i;
            else
                --j;
            //result直接保存和，计算距离选最小的距离
            if(abs(sum-target) < abs(res-target))
                res = sum;
        }
    }
    return res;
}

vector<string> letterCombinations1(string digits){
    unordered_map<char,string> mp={{'2',"abc"},{'3',"def"},{'4',"ghi"},
        {'5',"jkl"},{'6',"mno"},{'7',"pqrs"},
        {'8',"tuv"},{'9',"wxyz"}};
    vector<string> res = {""};
    for(auto c : digits){
        int sz = res.size();
        for (int i = 0; i < sz; ++i) {
            for(auto t : mp[c])
                res.push_back(res[i] + t);
            res.erase(res.begin(), res.begin()+sz);
        }
    }
    return res;
    
}

void letterCombinationsDfs(map<char, string> &mp, const string &digits, vector<string> &res, string cur, int dep){
    if(dep == digits.size()) res.push_back(cur);
    
    //dfs全排列，展开方式多了映射digits[dep]里的值来展开组合
    for(auto c : mp[digits[dep]]){
        cur.push_back(c);
        letterCombinationsDfs(mp, digits, res, cur, dep+1);
        cur.pop_back();
    }
        
        
}

vector<string> letterCombinations(string digits){
    vector<string> res;
    if(digits.size() < 1) return res;
    map<char,string> mp={{'2',"abc"},{'3',"def"},{'4',"ghi"},
        {'5',"jkl"},{'6',"mno"},{'7',"pqrs"},
        {'8',"tuv"},{'9',"wxyz"}};
    string cur = "";
    letterCombinationsDfs(mp, digits, res, cur, 0);
    return res;
}

void fourSumDfs(const vector<int> &nums, const int target, int sumNow, vector<int> &cur, set<vector<int>> &res, int dep, vector<int>::iterator p){
    if(dep == 4){
        if(sumNow == target)
            res.insert(cur);
        return;
    }
    for(; p != nums.end(); ++p){
        cur.push_back(*p);
        fourSumDfs(nums, target, sumNow+*p, cur, res, dep+1, p+1);
        cur.pop_back();
    }
}
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> ret;
    int n = nums.size();
    if(n < 1) return ret;
    vector<int> cur;
    set<vector<int>> res;
    sort(nums.begin(), nums.end());
    fourSumDfs(nums, target, 0, cur, res, 0, nums.begin());
    for(auto i : res)
        ret.push_back(i);
    return ret;
}

ListNode* removeNthFromEnd(ListNode* head, int n) {
    if(head == nullptr || n < 1) return NULL;
    ListNode *newHead = new ListNode(-1);
    newHead->next = head;
    ListNode *front = newHead, *pre = NULL, *cur = newHead;
    while (n--)
        front = front->next;
    while (front) {
        front = front->next;
        pre = cur;
        cur = cur->next;
    }
    if(cur->next)
        pre->next = cur->next;
    else
        pre->next = NULL;
    return newHead->next;
}

bool isValid(string s) {
    int n = s.size();
    if(n < 1) return true;
    
    stack<char> sk;
    //关键建立一个反映射，这里用的map，入栈时入对应括号出栈再判断也可以
    map<char, char> mp = {{')','('}, {']','['}, {'}','{'}};
    
    for(int i = 0; i < n; ++i){
        if(s[i] == '(' || s[i] == '[' || s[i] == '{')
            sk.push(s[i]);
        else if(!sk.empty() && mp[s[i]] == sk.top()){
            sk.pop();
        }
        else{
            return false;
        }
    }
    if(!sk.empty())
        return false;
    
    return true;
}

void generateParenthesisCore(const string &input, int n, vector<int> &visit, int dep, set<string> &res, string &cur){
    if(dep == n){
        if(isValid(cur))
            res.insert(cur);
        return;
    }
    
    for(int i = 0; i < input.size(); ++i){
        if(!visit[i]){
            cur.push_back(input[i]);
            visit[i] = 1;
            generateParenthesisCore(input, n, visit, dep + 1, res, cur);
            cur.pop_back();
            visit[i] = 0;
        }
    }
}
           
vector<string> generateParenthesis1(int n) {
    set<string> res;
    
    string cur;
    string input = string(n, '(') + string(n, ')');
    vector<int> visit(2*n, 0);
    generateParenthesisCore(input, 2*n, visit, 0, res, cur);
    vector<string> ret;
    for(auto i : res)
        ret.push_back(i);
    return ret;
    
}

//字符串+操作相当于push，如果字符串个数少从0到1递归
void generateParenthesisDfs(vector<string> &res, int left, int right, string cur){
    //3.跳出条件
    if(left == 0 && right == 0){
        res.push_back(cur);
    }
    
    //1.choice
    if(left > 0) generateParenthesisDfs(res, left - 1, right, cur + '(');
    
    //2.constrain
    if(right > 0 && right > left) generateParenthesisDfs(res, left, right - 1, cur + ')');
    
}

vector<string> generateParenthesis(int n) {
    vector<string> res;
    if(n < 1) return res;
    int left = n, right = n;
    generateParenthesisDfs(res, left, right, "");
    return res;
}

ListNode* mergeKLists1(vector<ListNode*>& lists) {
    if(lists.empty())
        return nullptr;
    
    //lists.size()动态在变,不能设置一个n来控制循环
    while(lists.size() > 1){
        lists.push_back(mergeTwoList(lists[0], lists[1]));
        lists.erase(lists.begin());
        lists.erase(lists.begin());
        
    }
    return lists.front();
}

static bool compareLess(ListNode* l1,ListNode* l2)
{
    return l1->val > l2->val;
}
ListNode* mergeKLists(vector<ListNode*> &lists)
{
    if(lists.size() < 1) return nullptr;
    vector<ListNode *> vec;

    for(auto i : lists)
        if(i) vec.push_back(i);
    
    make_heap(vec.begin(),vec.end(),compareLess);      // 建堆
    ListNode *newHead = new ListNode(-1);
    ListNode *rear = newHead, *cur;
    while(!vec.empty())
    {
        cur = vec.front();                       // 堆第一个节点first为最小值节点
        rear->next = cur;
        rear = cur;
        pop_heap(vec.begin(),vec.end(),compareLess);   // 它把first和last-1交换，然后重新生成一个堆
        vec.pop_back();                                // 容器弹出最后一个节点
        
        if(cur->next)                                  // 添加弹出的最小值的节点所在链表节点 last-1位置
        {
            vec.push_back(cur->next);
            push_heap(vec.begin(),vec.end(),compareLess);  // first到last-1是一个有效堆，新加入元素重新生成堆
        }
    }
    return newHead->next;
}

int removeDuplicates(vector<int>& nums) {
    int k = 0, n = nums.size();
    if(nums.size() < 1) return k;
    for (int i = 0; i < n; ++i) {
        if(nums[i+1] != nums[i])
            nums[k++] = nums[i];
        else
            ;
    }
    return k;
}

char *strStr(char *haystack, char *needle) {
    int l1 = strlen(haystack), l2 = strlen(needle);
    if(l2 == 0) return haystack;
    if(l1 < l2) return nullptr;
    for(int i = 0; i < l1; ++i){
        int j = 0, k = i;
        while(k < l1 && j < l2 && *(haystack+k) == *(needle+j)){
            ++k;
            ++j;
        }
        if(j == l2)
            return haystack + i;
    }
    return nullptr;
}

int strStr(string haystack, string needle) {
    if(needle == "") return 0;
    if(haystack == "") return -1;
    int i = 0, j = 0;
    while(i < haystack.size() && j < needle.size()){
        if(haystack[i] == needle[j]){
            ++i;
            ++j;
        }
        else{
            i = i - j + 1;
            j = 0;
        }
    }
    if(j == needle.size()) return i - j;
    return -1;
}

int divide(int dividend, int divisor) {
    if(dividend == INT_MIN && divisor == -1) return INT_MAX;
    //m被除数n除数 m/n = res商
    long long m = abs((long long)dividend), n = abs(divisor), res = 0;
    int flag = ((dividend > 0) ^ (divisor > 0)) ? -1 : 1;
    //规定不能用乘法
    if(divisor == 1) return (flag == 1 ? m : -m);
    while (m >= n) {
        long long temp_divisor = n, temp_res = 1;
        while (m >= (temp_divisor << 1)) {
            temp_divisor <<= 1;
            temp_res <<= 1;
        }
        res += temp_res;
        m -= temp_divisor;
    }
    return (flag == 1 ? res : -res);
}

bool isUniqueVector(vector<char> v){
    vector<int> visit(10);
    
    for(auto i : v){
        if(i == '.')
            visit[0]++;
        else if(visit[i-'0'])//重复
            return false;
        else
            visit[i-'0']++;
    }
    
    //判断没有数字的情况,题意没有数字也为true
    //if(visit[0] == 9)
      //  return false;
    return true;
}

bool isValidSudoku1(vector<vector<char>>& board) {
    char input[82];
    //{'.','1','2','3','4','5','6','7','8','9'};
    bool tag = true;
    //检查行
    for(auto &i : board){
        tag = isUniqueVector(i);
        if(!tag)
            return false;
    }
    
    for(int i = 0; i < board.size(); ++i){
        vector<char> temp;
        for(int j = 0; j < board[0].size(); ++j){
            temp.push_back(board[j][i]);
        }
        //检查列
        tag = isUniqueVector(temp);
        if(!tag) return false;
    }
    
    //检查每个方格
    for(int m = 0; m < 9; m+=3){
        for(int n = 0; n < 9; n+=3){
            vector<char> temp;
            for(int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    temp.push_back(board[i+m][j+n]);
            tag = isUniqueVector(temp);
            if(!tag) return false;
        }
    }
    
    return tag;
}
bool isValidSudoku(vector<vector<char>>& board) {
    int rowNum[9][9] = {0};
    int colNum[9][9] = {0};
    int blockNum[3][3][9] = {0};
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            if(board[i][j] != '.'){
                //一行行遍历时格子的数,下标从0
                int curNum = board[i][j] - '1';
                if(rowNum[i][curNum]++) return false;
                if(colNum[j][curNum]++) return false;
                if(blockNum[i/3][j/3][curNum]++) return false;
            }
        }
    }
    return true;
}

int minDistance(string word1, string word2) {
    int l1 = word1.size(), l2 = word2.size();
    if(l1 == 0) return l2;
    if(l2 == 0) return l1;
    vector<vector<int>> dp(l1+1, vector<int>(l2+1, 0));
    dp[0][0] = 0, dp[0][1] = 1, dp[1][0] = 1;
    
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

void countAndSayCore(string &res){
    string cur = "";
    int k = 0;
    //每次以输入字符串来生成新的字符串,新字符串为下一个输入
    while(k < res.size()){
        int count = 1;
        while(k+1 < res.size() && res[k+1] == res[k]){
            //统计当前k位置处字符的个数
            ++count;
            ++k;
        }
        cur += to_string(count) + res[k++];
    }
    res = cur;
}

string countAndSay(int n) {
    string res = "1";
    if(n == 1) return res;
    
    for(int i = 1; i < n; ++i){
        countAndSayCore(res);
    }
    return res;
}

int firstMissingPositive(vector<int>& nums) {
    int n = nums.size();
    if(n < 1) return 1;
    for (int i = 0; i < n; ++i) {
        //用while前有跳出判断,当前i不符合就下一个最多一个地方放一个
        while(nums[i] > 0 && nums[i] <= n && nums[nums[i]-1] != nums[i])
            //把5放在nums[5-1]处,下标从0但最小正数不考虑0
            swap(nums[i], nums[nums[i]-1]);
    }
    for (int i = 0; i < n; ++i) {
        if(nums[i] != i+1)
            return i+1;
    }
    //[0,n)都满足
    return n+1;
}

int binary_search_lowwer(vector<int> nums, int v){
    if(nums.size() < 1) return -1;
    //左开右开
    int lo = -1, hi = nums.size() - 1;
    while(hi - lo > 1){
        int mid = lo + (hi - lo)/2;
        if(nums[mid] <= v)
            lo = mid;
        //由于nums[mid]=v情况在else，即hi=mid右变闭区间
        else
            hi = mid;
    }
    //(lo,hi]为结束，查找对象在hi
    return nums[lo] == v ? lo+1 : -1;
}

int search(vector<int>& nums, int target) {
    if(nums.size() < 1) return -1;
    int lo = -1, hi = nums.size() - 1;
    while(lo + 1 < hi){
        int mid = lo + (hi - lo)/2;
        if(nums[mid] < nums[hi])
            hi = mid;
        else
            lo = mid;
    }
    //找到旋转数组分界点hi
    if(nums[lo] >= target) lo = -1;
    else hi = nums.size();
    while(lo + 1 < hi){
        int mid = lo + (hi - lo)/2;
        if(nums[mid] < target)
            lo = mid;
        else
            hi = mid;
    }
    if(hi == nums.size()) return -1;
    return nums[hi] == target ? hi : -1;
}

int main(){
    vector<int> test{4,5,6,7,0,1,2};
    auto ret = search(test, 0);
    cout << ret;
}

