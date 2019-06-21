#include <bits/stdc++.h>
using namespace std;

//种类n,容量c,重量数组w,价值数组v,标记数组res
//假设5种物品,背包容量为10
//递推公式f[5][10] = max{f[4][10], (f[4][10-weight[a]+value[a]))}
//边界条件f[i][0]=0(1<=i<=5), f[1][j]=(j < weight[e])?0:value[e],(1<=j<=10)
int knapsack(int *W, int *V, int *res, int n, int C)
{
    int value = 0;
    int **f = new int*[n];

    //动态初始化二维数组
    for(int i = 0; i < n; i++)
    {
        f[i] = new int[C+1];
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; j <= C;j++)
            f[i][j] = 0;

    //边界条件赋值
    for(int i = 0; i < n; i++)
    {
        f[i][0] = 0;
    }
    for(int i = 1; i <= C; i++)
    {
        f[0][i] = (i < W[0])?0:V[0];
    }

    //自顶向下计算
    for(int i = 1; i < n; i++)
    {
        for(int y = 1; y <= C; y++)
        {
            if(y >= W[i])
            {
                f[i][y] = (f[i-1][y] > (f[i-1][y-W[i]] + V[i]))?f[i-1][y]:(f[i-1][y-W[i]] + V[i]);
            } else {
                f[i][y] = f[i-1][y];
            }
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < C+1;j++)
           cout << f[i][j] << " ";
        cout << endl;
    }

    //统计哪些种类需要
    value = f[n-1][C];
    int j = n-1;
    int y = C;
    while(j)
    {
        //种类j被选择
        if(f[j][y] == (f[j-1][y-W[j]] + V[j]))
        {
            res[j] = 1;
            y = y - W[j];
        }
        j--;
    }
    if(f[0][y])
    {
        res[0] = 1;
    }

    //删除动态分配new出的对象
    for(int i = 0; i < n;i++)
    {
        delete f[i];
        f[i] = 0;
    }
    delete [] f;
    f = 0;
    return value;
}

void test1()
{
    int n, C;
    while(cin >> n >> C)
    {
        int *W = new int[n];
        int *V = new int[n];
        int *res = new int[n];
        for(int i = 0; i < n; i++)
        {
            res[i] = 0;
        }
        int w = 0, v = 0, i = 0;
        while(i < n)
        {
            cin >> w >> v;
            W[i] = w;
            V[i] = v;
            i++;
        }
        int value = knapsack(W, V, res, n, C);
        cout << value << endl;
        for(int i = 0; i < n; i++)
            cout << res[i] << " ";
        cout << endl;
        delete W;
        delete V;
        delete res;
    }
}

int main()
{
    test1();
    return 0;
}
