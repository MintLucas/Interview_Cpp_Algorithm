/*
atoi() 的功能:
    将字符串（C风格）转换成整型；
    atoi() 会跳过前面的空格字符，直到遇上数字或正负号才开始做转换，
    而再遇到 非数字 或 结束符('\0') 时结束转化，并将结果返回（返回转换后的整型数）
    如果发生溢出，则输出 INT_MAX 或 INT_MIN;
    *内置 atoi 不会处理 NULL 指针
    
    合法样例：
        "123"           -> 123
        "+123"          -> 123
        "-123"          -> -123
        "123abc"        -> 123
        "   123abc"     -> 123
        "a123"          -> 0

OJ:
    把字符串转换成整数 https://www.nowcoder.com/practice/1277c681251b4372bdef344468e4f26e?tpId=13&tqId=11202&rp=2&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
    题目来源：剑指Offer

核心代码：
    while (*p >= '0' && *p <= '9') {
        ret = ret * 10 + (*p - '0');
        p++;
    }

    溢出处理

*/
#pragma once
#include "../all.h"

int atoi(const char* str) {
    if (str == NULL) return 0;

    int res = 0, flag = 1;
    auto *p = str;  // str 为常指针

    // 跳过前面的空格
    while (isspace(*p)) p++;

    // 判断正负
    if (*p == '-') flag = -1;
    if (*p == '-' || *p == '+') p++;

    // 首个非空字符不是数字，注意与判断正负的顺序
    // if (*p < '0' && *p > '9') return 0;       // 不需要

    // 循环转换整数（核心代码）加入溢出判断
    while (*p >= '0' && *p <= '9') {
        int new_res = res * 10 + (*p - '0');
        if (new_res / 10 != res) {
            return flag > 0 ? INT_MAX : INT_MIN;
        }
        res = new_res;
        p++;
    }
    // 无溢出判断
    /*while (*p >= '0' && *p <= '9') {
        res = res * 10 + (*p - '0');
        p++;
    }*/
    return res * flag;
}

void solve() {
    print(atoi_my("123"));
    print(atoi_my("+123"));
    print(atoi_my("-123"));
    print(atoi_my("   123abc"));
    print(atoi_my("   +123abc"));
    print(atoi_my("   -123abc"));
    print(atoi_my("   123abc   "));
    print(atoi_my("   +123abc   "));
    print(atoi_my("   -123abc   "));
    print();
    print(atoi_my("a123"));
    print(atoi_my("+a123"));
    print(atoi_my("-a123"));
    print(atoi_my("a123   "));
    print(atoi_my("+a123   "));
    print(atoi_my("-a123   "));
    print(atoi_my("   a123"));
    print(atoi_my("   +a123"));
    print(atoi_my("   -a123"));
    print(atoi_my("   a123   "));
    print(atoi_my("   +a123   "));
    print(atoi_my("   -a123   "));
    print(atoi_my("   a+123   "));
    print(atoi_my("   a-123   "));
    print(atoi_my("222222222222222222222222"));
    print(atoi_my("-222222222222222222222222"));
    print();
    const char p[] = "   123abc";
    print(atoi_my(p));
    print(p);
    print();
    print(atoi_my(NULL));
}

注意两题区别，传入string类用整数下标，传入char*用常指针指向传入值。
leetcode不支持newres检查会报错，换一种检查方法。

/*
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
        while (isdigit(str[i])) {
            res = res*10 + (str[i] - '0');
            if(flag*res > INT_MAX) return INT_MAX;
            if(flag*res < INT_MIN) return INT_MIN;
            ++i;
            //if(i > 9)第一次想法是这样判断溢出
            //    break;但用位数无法判断"  0000000000012345678"
        }
    }
    else
        return 0;
    return flag*res;
}
*/