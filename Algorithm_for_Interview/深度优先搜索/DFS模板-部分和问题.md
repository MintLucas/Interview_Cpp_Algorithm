---
title: cppDFS和BFS
categories:
  - 算法
tags: c++
date: 2019-04-19 09:11:44

---

### DFS核心代码：

参考：<https://blog.csdn.net/qq_40763929/article/details/81629800>

关于dfs参数问题，**什么在变化，就把什么设置成参数**。

- 如果要求输出所有可能的解，往往都是要用深度优先搜索。
- 如果是要求找出最优的解，或者解的数量，往往可以使用动态规划。

```cpp
void dfs()//参数用来表示状态  

    if(到达终点状态)  

    {  

        ...//根据题意添加  

        return;  

    }  

    if(越界或者是不合法状态)  

        return;  

    if(特殊状态)//剪枝

        return ;

    for(扩展方式)  

    {  

        if(扩展方式所达到状态合法)  

        {  

            修改全局变量;//根据题意来添加  

            visit标记；  

            dfs（）；

            恢复全局变量//回溯部分

            (还原标记)；  

            //是否还原标记根据题意

            //如果加上（还原标记）就是 回溯法 

        }  
 }
```



### 全排列问题



先给一个正整数 ( 1 < = n < = 10 ) 

例如n＝3，所有组合,并且按字典序输出： 

1 2 3 

1 3 2 

2 1 3 

2 3 1 

3 1 2 

3 2 1 





```cpp
#include<iostream>

#include<cmath>

using namespace std;

 

void combineDfs(int dep, vector<int> &cur, vector<vector<int>> &res, int len, int vis[]){

    if(dep == len + 1)//到达终点状态

    {

        res.push_back(cur);

        return ;

    }

    

    for(int i = 1; i <= len; ++i){

        if(vis[i] == false)//扩展方式所达到状态合法(结点可访问

        //if(vis[i]==false&& i>cur[dep])剪枝后一个进入的要比当前的大

        {

            vis[i] = true;

            cur.push_back(i);//当前层数用某个,若层数返回记得退回

            combineDfs(dep+1, cur, res, len, vis);

            //一趟深搜结束,还原标记下次还可用来深搜

            cur.pop_back();

            vis[i] = false;//结点是否可重复使用

        }

    }

        

}                                                                                                                                            
                                                                                                                                           
int main(){

    int vis[10] = {0};

    int n;

    n = 3;

    vector<int> cur;

    vector<vector<int>> res1;

    combineDfs(1, cur, res1, n, vis);



    return 0;

}

```

### 组合问题

https://www.nowcoder.com/practice/345e2ed5f81d4017bbb8cc6055b0b711?tpId=46&tqId=29163&tPage=1&rp=1&ru=/ta/leetcode&qru=/ta/leetcode/question-ranking

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]

```cpp
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
    
    //关键要
    sort(nums.begin(), nums.end());
    vector<int> cur;
    threeSumCore(temp, cur, nums, nums.begin(), 1);
    for(auto i : temp)
        res.push_back(i);
    return res;
}

int main()
{
    vector<int> vec = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> res = threeSum(vec);
    
}
```



### 回文字符串分割问题



类似全排列，亦是for 1:len展开所有



```cpp
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
    
        
    //LPS问题：展开方式,每次从j开始取i个单位当子串
    for (int i = 1; i < n; ++i)
    {
        tmp = 0;
        //考虑所有连续的长度为i+1的子串，str[j....j+i]
        for (int j = 0; j + i < n; j++)
        {
            //如果首尾相同
            if (str[j] == str[j + i])
                tmp = dp[j + 1][j + i - 1] + 2;
            //如果首尾不同
            else 
                tmp = max(dp[j + 1][j + i], dp[j][j + i - 1]);
            dp[j][j + i] = tmp;
        }
    }
   
    

}

vector<vector<string>> partition(string s){

    vector<vector<string>> res;

    vector<string> cur;

    palindromeDfs(s, cur, res);

    return res;

}

```



### N皇后问题：

题目链接：<http://codeup.cn/problem.php?cid=100000608&pid=3>

```cpp
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
```



### LeetCode:surrounded-regions

题目链接：<https://leetcode.com/problems/surrounded-regions/

**思路：**

- 遍历四条边上的O，并深度遍历与其相连的O，将这些O都转为1

- 1代表没被包围，再将这些1都变为O

```cpp
                 X X X X           X X X X             X X X X
         X X O X  ->       X X O X    ->       X X X X
         X O X X           X 1 X X             X O X X
         X O X X           X 1 X X             X O X X
```

```cpp
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
void solve(vector<vector<char>> &board) {
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
```



### BFS：

![è??é??????????????è?°](https://ws2.sinaimg.cn/large/006tNc79gy1g27odhyt8vj30cq07fdgf.jpg)

### 最典型的模版就是树的层序遍历：

```cpp
void levelOrder(TreeNode* root){
    if(root == NULL) return;
    queue<TreeNode*> que;//初始化队列Q
  
    TreeNode* cur = NULL;
  
    que.push(root);//Q=起点
  
    while (!que.empty()) {
        cur = que.front();//取队首元素出队
        que.pop();
      
        cout << cur->val << " ";
      
        if(cur->left) que.push(cur->left);//满足目标状态
        if(cur->right) que.push(cur->right);
    }
    return;
}
```







### 矩阵中的路径问题：

```cpp
int h[606][606];
const int mm = pow(10,9);
class point {
public:
    int x, y;
    point(int a, int b) :x(a), y(b){}
};

int maina()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> h[i][j];
        }
    }
    int x, y, z, w;
    cin >> x >> y >> z >> w;
  
    queue<point> q;
    q.push(point(x, y));
    int count = 0;
  
    while (!q.empty()) {
        point cur = q.front();
        q.pop();
        if (cur.x == z && cur.y == w) {
            ++count;
            count %= mm;
        }
        if (cur.x - 1 >= 0 && h[cur.x - 1][cur.y] > h[cur.x][cur.y])
            q.push(point(cur.x - 1, cur.y));
        if (cur.x + 1 < n && h[cur.x + 1][cur.y] > h[cur.x][cur.y])
            q.push(point(cur.x + 1, cur.y));
        if (cur.y - 1 >= 0 && h[cur.x][cur.y - 1] > h[cur.x][cur.y])
            q.push(point(cur.x, cur.y - 1));
        if (cur.y + 1 < m && h[cur.x][cur.y + 1] > h[cur.x][cur.y])
            q.push(point(cur.x, cur.y + 1));
    }
    cout << count << endl;
    
    return 0;
}
```



### 广搜或深搜可分为两大类题型：

1 . **地图型**：这种题型将地图输入，要求完成一定的任务。因为地图的存在。使得题意清楚形象化，容易理清搜索思路。

2 . **数据型**：这种题型没有给定地图，一般是一串数字或字母，要求按照一定的任务解题。相对于地图型，这种题型较为抽象，需要在数据中进行搜索。数据以数组的形式存储，那么只要将数组也当作一张图来进行搜索就可以了。

PS：二维数组的题目即地图型

N小于20的，适用DFS。 
而一般 N<= 200，N<=1000这种 
一定不可能用DFS去做 
而且并不只是整个题目不能用DFS，其中的每一步也不能使用DFS



### BFS和DFS对比



- DFS多用于连通性问题因为其运行思想与人脑的思维很相似，故解决连通性问题更自然。 
- BFS多用于解决最短路问题，其运行过程中需要储存每一层的信息，所以其运行时需要储存的信息量较大，如果人脑也可储存大量信息的话，理论上人脑也可运行BFS。



多数情况运行BFS所需的内存会大于DFS需要的内存(DFS一次访问一条路，BFS一次访问多条路)。





















