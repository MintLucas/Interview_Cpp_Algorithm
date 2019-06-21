---
title: cppDFS��BFS
categories:
  - �㷨
tags: c++
date: 2019-04-19 09:11:44

---

### DFS���Ĵ��룺

�ο���<https://blog.csdn.net/qq_40763929/article/details/81629800>

����dfs�������⣬**ʲô�ڱ仯���Ͱ�ʲô���óɲ���**��

- ���Ҫ��������п��ܵĽ⣬��������Ҫ���������������
- �����Ҫ���ҳ����ŵĽ⣬���߽����������������ʹ�ö�̬�滮��

```cpp
void dfs()//����������ʾ״̬  

    if(�����յ�״̬)  

    {  

        ...//�����������  

        return;  

    }  

    if(Խ������ǲ��Ϸ�״̬)  

        return;  

    if(����״̬)//��֦

        return ;

    for(��չ��ʽ)  

    {  

        if(��չ��ʽ���ﵽ״̬�Ϸ�)  

        {  

            �޸�ȫ�ֱ���;//�������������  

            visit��ǣ�  

            dfs������

            �ָ�ȫ�ֱ���//���ݲ���

            (��ԭ���)��  

            //�Ƿ�ԭ��Ǹ�������

            //������ϣ���ԭ��ǣ����� ���ݷ� 

        }  
 }
```



### ȫ��������



�ȸ�һ�������� ( 1 < = n < = 10 ) 

����n��3���������,���Ұ��ֵ�������� 

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

    if(dep == len + 1)//�����յ�״̬

    {

        res.push_back(cur);

        return ;

    }

    

    for(int i = 1; i <= len; ++i){

        if(vis[i] == false)//��չ��ʽ���ﵽ״̬�Ϸ�(���ɷ���

        //if(vis[i]==false&& i>cur[dep])��֦��һ�������Ҫ�ȵ�ǰ�Ĵ�

        {

            vis[i] = true;

            cur.push_back(i);//��ǰ������ĳ��,���������ؼǵ��˻�

            combineDfs(dep+1, cur, res, len, vis);

            //һ�����ѽ���,��ԭ����´λ�����������

            cur.pop_back();

            vis[i] = false;//����Ƿ���ظ�ʹ��

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

### �������

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
    
    //�ؼ�Ҫ
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



### �����ַ����ָ�����



����ȫ���У�����for 1:lenչ������



```cpp
bool isPalindrome(string s){

    return s == string(s.rbegin(), s.rend());

}


void palindromeDfs(string s, vector<string> &cur, vector<vector<string>> &res){

    if(s == ""){

        res.push_back(cur);

        return ;

    }
    
    //չ����ʽ,ÿ�δ�0��ʼȡi����λ���Ӵ�

    for (int i = 1; i <= s.size(); ++i) {

        string sub = s.substr(0, i);

        if (isPalindrome(sub)) {

            cur.push_back(sub);

            //��ǰ�ǻ���,��i��ʼ��ȡlen-i���Ӵ�

            palindromeDfs(s.substr(i, s.size() - i), cur, res);

            cur.pop_back();

        }

    }
    
        
    //LPS���⣺չ����ʽ,ÿ�δ�j��ʼȡi����λ���Ӵ�
    for (int i = 1; i < n; ++i)
    {
        tmp = 0;
        //�������������ĳ���Ϊi+1���Ӵ���str[j....j+i]
        for (int j = 0; j + i < n; j++)
        {
            //�����β��ͬ
            if (str[j] == str[j + i])
                tmp = dp[j + 1][j + i - 1] + 2;
            //�����β��ͬ
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



### N�ʺ����⣺

��Ŀ���ӣ�<http://codeup.cn/problem.php?cid=100000608&pid=3>

```cpp
bool canPut(int rows, int cols, vector<string> cur, int n){
    bool tag = true;
    //�����
    for (int i = 0; i < rows; ++i) {
        if(cur[i][cols] == 'Q')
            tag = false;
    }
    
    //�����,ÿ�з�һ���ɲ����
    for(int i = 0; i < cols; ++i)
        if(cur[rows][i] == 'Q')
            tag = false;
    
    //���Ͻ�б
    for(int i = rows-1,j = cols-1; i>=0 && j>=0; j--, i-- )
        if(cur[i][j] == 'Q')
            tag = false;
    
    //���Ͻ���б
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
    
    //ÿ��һ�����õݽ�����������,��չ���ж��Ƿ��ܷ�
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
    // ��ʼ�����̣����е�λ�ö�û�аڷŻʺ�
    vector<string> cur(n, string(n, '.'));
    NQueensDfs(0, cur, res, n);
    return res;
}
```



### LeetCode:surrounded-regions

��Ŀ���ӣ�<https://leetcode.com/problems/surrounded-regions/

**˼·��**

- �����������ϵ�O������ȱ�������������O������ЩO��תΪ1

- 1����û����Χ���ٽ���Щ1����ΪO

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



### BFS��

![��??��??????????????��?��](https://ws2.sinaimg.cn/large/006tNc79gy1g27odhyt8vj30cq07fdgf.jpg)

### ����͵�ģ��������Ĳ��������

```cpp
void levelOrder(TreeNode* root){
    if(root == NULL) return;
    queue<TreeNode*> que;//��ʼ������Q
  
    TreeNode* cur = NULL;
  
    que.push(root);//Q=���
  
    while (!que.empty()) {
        cur = que.front();//ȡ����Ԫ�س���
        que.pop();
      
        cout << cur->val << " ";
      
        if(cur->left) que.push(cur->left);//����Ŀ��״̬
        if(cur->right) que.push(cur->right);
    }
    return;
}
```







### �����е�·�����⣺

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



### ���ѻ����ѿɷ�Ϊ���������ͣ�

1 . **��ͼ��**���������ͽ���ͼ���룬Ҫ�����һ����������Ϊ��ͼ�Ĵ��ڡ�ʹ������������󻯣�������������˼·��

2 . **������**����������û�и�����ͼ��һ����һ�����ֻ���ĸ��Ҫ����һ����������⡣����ڵ�ͼ�ͣ��������ͽ�Ϊ������Ҫ�������н����������������������ʽ�洢����ôֻҪ������Ҳ����һ��ͼ�����������Ϳ����ˡ�

PS����ά�������Ŀ����ͼ��

NС��20�ģ�����DFS�� 
��һ�� N<= 200��N<=1000���� 
һ����������DFSȥ�� 
���Ҳ���ֻ��������Ŀ������DFS�����е�ÿһ��Ҳ����ʹ��DFS



### BFS��DFS�Ա�



- DFS��������ͨ��������Ϊ������˼�������Ե�˼ά�����ƣ��ʽ����ͨ���������Ȼ�� 
- BFS�����ڽ�����·���⣬�����й�������Ҫ����ÿһ�����Ϣ������������ʱ��Ҫ�������Ϣ���ϴ��������Ҳ�ɴ��������Ϣ�Ļ�������������Ҳ������BFS��



�����������BFS������ڴ�����DFS��Ҫ���ڴ�(DFSһ�η���һ��·��BFSһ�η��ʶ���·)��





















