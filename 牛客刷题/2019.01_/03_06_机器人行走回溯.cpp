#include <bits/stdc++.h>
using namespace std;

public class Solution {
 
    /**算法本质：
    * DFS||BFS 寻找连通分量
    *
     * 题目分析：
     * 机器人在一个矩阵上的m*n个格子上移动，可进入的格子的集合可抽象为以下点集：
     * { (row, col) | (i%10+i/10+j%10+j/10) <= threshold }。且路径节点可重复，无步数限制。
     * 问：机器人能到达多少个格子？
     *
     * 题目抽象：
     * 倘若我们把矩阵的每一个“格子”抽象成一个“结点”，把“格子相邻”抽象为“结点连通”（结点之间存在无向边），
     * 把“无法进入的格子”抽象成“与所有普通结点都不连通（不存在无向边）的孤点”，则整个问题可以抽象为：
     * 从某个结点出发，寻找无向图的连通分量的节点个数。很显然，可以使用DFS或者BFS进行实现
     *
     * 算法实现：
     * 这里选择DFS进行实现。
     * 设置两个辅助boolean矩阵：visited与isWall。前者是DFS中的典型辅助矩阵，记录每个节点是否已访问过。
     * 后者用来表示每个节点是否是不能进入的“孤点”。
     * 设置静态变量nodeCnt，用于在DFS的过程中记录访问过的结点数
     * DFS递归函数的出口条件设置为：  
     * (outOfBoundary(rows, cols, row, col) || visited[row][col] || isWall[row][col] )
     * 即：“若超过边界（到矩阵之外）”或“访问过”或“是无法进入的结点” 则 return
     * 然后进行DFS。
     * */
 
    int nodeCnt = 0;
    boolean[][] visited;
    boolean[][] isWall;
    int threshold;
    int rows;
    int cols;
 
    public int movingCount(int threshold, int rows, int cols){
        if (threshold<0 || rows<=0 || cols<=0) //robust
            return 0;//牛客示例是0
 
        //init
        this.nodeCnt = 0;
        this.threshold = threshold;
        this.rows = rows;
        this.cols = cols;
        this.visited = new boolean[rows][cols];
        this.isWall = new boolean[rows][cols];
        for (int i=0;i<rows;i++){
            for (int j=0;j<cols;j++){
                this.visited[i][j]=false;
                if ( (i%10+i/10+j%10+j/10) > threshold )
                    this.isWall[i][j]=true;
                else
                    this.isWall[i][j]=false;
            }
        }
 
        //body
        DFS(0,0);
        return this.nodeCnt;
    }
 
    public void DFS(int row, int col){
        if (   outOfBoundary(rows, cols, row, col)
            || visited[row][col]
            || isWall[row][col] )
            return;
 
        //visit
        visited[row][col]=true;
        nodeCnt++;
 
        //DFS
        DFS(row+1, col);
        DFS(row-1, col);
        DFS(row, col+1);
        DFS(row, col-1);
    }
 
    public boolean outOfBoundary(int rows, int cols, int row, int col){
        return ( row<0 || row>=rows || col<0 || col>=cols );
    }
 
}


class Solution {
public:
    int movingCount(int threshold, int rows, int cols)
    {
        if(threshold < 1 || rows < 1 || cols < 1)
            return 0;
        bool* visit = new bool[rows*cols];
        memset(visit, 0, rows*cols);
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++){
                movingCountCore(threshold, i, j, rows, cols, visit);
            }
        int count = countBoolArray(visit, rows, cols);
        delete[] visit;
        return count;
        
    }
    void movingCountCore(int k, int row, int col, int rows, int cols, bool* visit){
        if(row >= rows || col >= cols) return;
        if(row >= 0 && col >=0 && (bitSum(row) + bitSum(col)) <= k && !visit[cols*row + col]){
            visit[cols*row + col] = true;
            movingCountCore(k, row, col-1, rows, cols, visit);
            movingCountCore(k, row, col+1, rows, cols, visit);
            movingCountCore(k, row-1, col, rows, cols, visit);
            movingCountCore(k, row+1, col, rows, cols, visit);
        }
        return;
    }
    
    int bitSum(int number){
        int count = 0;
        while(number){
            count += number % 10;
            number = number / 10;
        }
        return count;
    }
    int countBoolArray(bool* visit, int rows, int cols){
        int count = 0;
        for(int i = 0; i < rows*cols; i++)
            if(visit[i])
                count++;
        return count;
        
    }
};

