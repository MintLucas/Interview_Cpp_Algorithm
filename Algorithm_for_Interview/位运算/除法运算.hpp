
原题：https://leetcode.com/problems/divide-two-integers/submissions/

参考网上别人代码，将因子不断乘以2（可以通过移位实现，同时结果也从1开始不断移位加倍），然后和被除数比较，等到大于被除数一半了，就从被除数中减去，将因子个数叠加入结果中。然后在剩下的被除数中采用同样的方法减去小于其一半的因子和，循环往复。​

参考链接：https://www.cnblogs.com/grandyang/p/4431949.html

/*
int divide(int dividend, int divisor) {
    if(dividend == INT_MIN && divisor == -1) return INT_MAX;
    //m被除数n除数 m/n = res商
    long long m = abs((long long)dividend), n = abs((long long)divisor), res = 0;
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
*/