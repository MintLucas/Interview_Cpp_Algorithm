#include <math.h>
#include <iostream>
#include <queue>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include "BTree.hpp"
#include "01_ListNode.hpp"
#include <unordered_set>

#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#include "dfs.hpp"

void combineDfs(int dep, vector<int> &cur, vector<vector<int>> &res, int len, int vis[]){
    if(dep == len + 1)//到达终点状态
    {
        res.push_back(cur);
        return ;
    }
    
    for(int i = 1; i <= len; ++i){
        if(vis[i] == false)//扩展方式所达到状态合法(结点可访问
        {
            vis[i] = true;
            cur.push_back(i);
            combineDfs(dep+1, cur, res, len, vis);
            //一趟深搜结束,还原标记下次还可用来深搜
            cur.pop_back();
            vis[i] = false;
        }
    }
        
}

bool isPalindrome(string s){
    return s == string(s.rbegin(), s.rend());
}

void palindromeDfs(string s, vector<string> &cur, vector<vector<string>> &res){
    if(s == ""){
        res.push_back(cur);
        return ;
    }
    
    //展开方式,每次从0开始取i个单位当子串
    for (int i = 1; i <= s.size(); ++i) {
        string sub = s.substr(0, i);
        if (isPalindrome(sub)) {
            cur.push_back(sub);
            //当前是回文,从i开始再取len-i个子串
            palindromeDfs(s.substr(i, s.size() - i), cur, res);
            cur.pop_back();
        }
    }
}

vector<vector<string>> partition(string s){
    vector<vector<string>> res;
    vector<string> cur;
    palindromeDfs(s, cur, res);
    return res;
}
                                     
bool isPrime(int x){
    bool tag = true;
    for(int i = 2; i < x; ++i){
        if(x % i == 0)
            tag = false;
    }
    return tag;
}

void sumIsPrimeDfs(int dep, vector<int> &cur, vector<vector<int>> &res, vector<int> &vis, int len, int sum, vector<int> input){
    if(dep == len + 1){
        if(isPrime(sum))
            res.push_back(cur);
        return ;
    }
    
    for(int i = 0; i < input.size(); ++i){
        if(vis[i] == false)//&& input[i] > cur[dep]剪枝顺序输入
        {
            sum+= input[i];
            vis[i] = true;
            cur.push_back(input[i]);
            sumIsPrimeDfs(dep+1, cur, res, vis, len, sum, input);
            cur.pop_back();
            vis[i] = false;
            sum -= input[i];
        }
    }
}


void sumIsPrimeDfsTest(){
    int n, k;
    cin >> n >> k;
    vector<int> input(n);
    for(int i = 0; i < n; ++i)
        cin >> input[i];
    vector<int> vis(n, 0);
    vector<int> cur;
    vector<vector<int>> res;
    sumIsPrimeDfs(1, cur, res, vis, 3, 0, input);
}

bool canPut(int rows, int cols, vector<string> cur, int n){
    bool tag = true;
    //检查列
    for (int i = 0; i < rows; ++i) {
        if(cur[i][cols] == 'Q')
            tag = false;
    }
    
    //检查行,每行放一个可不检查
    for(int i = 0; i < cols; ++i)
        if(cur[rows][i] == 'Q')
            tag = false;
    
    //左上角斜
    for(int i = rows-1,j = cols-1; i>=0 && j>=0; j--, i-- )
        if(cur[i][j] == 'Q')
            tag = false;
    
    //右上角倾斜
    for(int i = rows-1,j = cols+1; i>=0 && j<n; j++, i-- )
        if(cur[i][j] == 'Q')
            tag = false;
    
    return tag;
}

void NQueensDfs(int dep, vector<string> &cur, vector<vector<string>> &res, int n){
    if(dep == n){
        res.push_back(cur);
        return;
    }
    
    //每行一个，用递进层数代表行,列展开判断是否能放
    for(int i = 0; i < n; ++i){
        if(canPut(dep, i, cur, n)){
            cur[dep][i] = 'Q';
            NQueensDfs(dep+1, cur, res, n);
            cur[dep][i] = '.';
        }
    }
}

vector<vector<string>> solveNQueens(int n){
    vector<vector<string>> res;
    // 初始化棋盘，所有的位置都没有摆放皇后
    vector<string> cur(n, string(n, '.'));
    NQueensDfs(0, cur, res, n);
    return res;
}


void surrounded_regions(int rows, int cols, vector<vector<char>> &board){
    if(rows < 0 || rows >= board.size() || cols < 0 || cols >= board[0].size()) return ;
    
    if(board[rows][cols] == 'O'){
        board[rows][cols] = '1';
        surrounded_regions(rows-1, cols, board);
        surrounded_regions(rows+1, cols, board);
        surrounded_regions(rows, cols-1, board);
        surrounded_regions(rows, cols+1, board);
    }
}
void solve1(vector<vector<char>> &board) {
    if(board.size() <= 0) return;
    int rows = int(board.size());
    int cols = int(board[0].size());
    for (int i = 0; i < rows; ++i) {
        surrounded_regions(i, 0, board);
        surrounded_regions(i, cols-1, board);
    }
    for (int i = 0; i < cols; ++i) {
        surrounded_regions(0, i, board);
        surrounded_regions(rows-1, i, board);
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if(board[i][j] == '1')
                board[i][j] = 'O';
            else
                board[i][j] = 'X';
        }
    }
}
                              
                              
                              
void testSurrounded(){
    int n = 4;
    vector<vector<char>> board(n, vector<char>(n,'X'));
    board[1][1] = 'O';
    board[1][2] = 'O';
    board[2][2] = 'O';
    board[3][1] = 'O';
    solve1(board);
    cout << board[3][1];
    
}

string to_num(ListNode *root){
    string res;
    while(root){
        res.insert(res.begin(), root->val + '0');
        root = root->next;
    }
    return res;
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    string s1 = to_num(l1);
    string s2 = to_num(l2);
    //当链表代表的数超过int出错比如19999999
    int res = stoi(s1) + stoi(s2);
    string s3 = to_string(res);
    ListNode* l3 = new ListNode(-1);
    for(int i = 0; i < s3.size(); ++i){
        ListNode *newNode = new ListNode(s3[i]-'0');
        newNode->next = l3->next;
        l3->next = newNode;
    }
    return l3->next;
}


//
//int main(){
//    string s = "sssac";
//    bool tag = (s.find("c") != -1);
//
//    cout << tag;
//}
