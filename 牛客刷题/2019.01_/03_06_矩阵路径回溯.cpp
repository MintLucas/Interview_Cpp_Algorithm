#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool hasPath(char* matrix, int rows, int cols, char* str)
    {
        if(matrix == NULL || str == NULL || rows < 1 || cols <1)
            return false;
        int depth = 0;
        bool *visit = new bool[cols*rows];
        memset(visit, 0, rows*cols);
        
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++){
                if(hasPathCore(matrix, i, j, rows, cols, str, depth, visit)){
                    delete[] visit;
                    return true;
                }
            }
        delete[] visit;
        return false;
    }
    bool hasPathCore(char* matrix, int row, int col, int rows, int cols, char* str, int depth, bool* visit){
        //if(row >= rows || col >= cols || depth > len(str))
        if(str[depth] == '\0')
            return true;
        
        bool tag = false;
        
        if(row < rows && col < cols && row >= 0 && col >= 0 && str[depth] == matrix[row*cols + col] && !visit[row*cols + col]){
            visit[row*cols + col] = true;
            tag = (hasPathCore(matrix, row, col-1, rows, cols, str, depth+1, visit) || 
                  hasPathCore(matrix, row, col+1, rows, cols, str, depth+1, visit) || 
                  hasPathCore(matrix, row-1, col, rows, cols, str, depth+1, visit) || 
                  hasPathCore(matrix, row+1, col, rows, cols, str, depth+1, visit));
            if(!tag){
                visit[row*cols + col] = false;
            }
        
        }
        return tag;
    }


};

int bitSum(int number){
    int count = 0;
    while(number){
        count += number % 10;
        number = number / 10;
    }
    return count;
}

int main(){
    cout << 11 << bitSum(12345);
}