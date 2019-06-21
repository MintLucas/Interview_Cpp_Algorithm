
https://leetcode.com/problems/valid-sudoku/

1. 直观想法

```cpp
bool isUniqueVector(vector<char> v){
    vector<int> visit(10);
    
    for(auto i : v){
        if(i == '.')
            visit[0]++;
        else if(visit[i-'0'])//重复
            //优化if(visit[i-'0']++)
            return false;
        else
            visit[i-'0']++;
    }
    
    //判断没有数字的情况
    //if(visit[0] == 9)
      //  return false;
    return true;
}

bool isValidSudoku(vector<vector<char>>& board) {
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
```

2. 注意到都需要for两遍遍历只是下标在变化，用三个数组分别记录封装到一个for循环
int rowNum[9][9] = {0};//按行分为9行
int colNum[9][9] = {0};//按列分为9列
int blockNum[3][3][9] = {0};//按块分(二维3*3)为9块

注意分块时block[0][0]为row:0-2 col:0-2此块
block[0][1]为row:0-2 col:3-5此块
...依次类推

```cpp
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
```