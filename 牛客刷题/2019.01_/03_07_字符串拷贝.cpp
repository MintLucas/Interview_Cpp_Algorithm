#include <bits/stdc++.h>
# include <stdlib.h>
using namespace std;

//https://blog.csdn.net/zzuchengming/article/details/51815675
char* strcpy(char* des, const char* src){
    //传入的*src不能更改
    if(src == NULL || des == NULL) return NULL;
    char* add = des;
    while((*des++ = *src++) != '\0')
    ;
    return add;
}

char* itostring(int num, char* str){
    if(num <= 0) return 0;
    int res;
    char* add = str;
    while(num){
        *str = num % 10 + '0';//int+0x30 ='0'转化为字符 41=a 61 = A
        str++;
        num = num / 10;
    }
    return str;
}

int main(){
    //char* a = "test22 string";
    char b[] = {'1','2','3','a','A'};
    char* a = "test22 string";
    //a = itostring(48, b);
    //数组名b对应着一块内存不是指向，在栈里分配高到低上面的在右侧内存覆盖
    //不能左值数组元素可变
    //strcpy(b, a);//往数组里拷贝，先分配不会被覆盖
    int num=123;
    char str[256];
    //itoa(num,str,10);编译器问题
    //b[1] = a[1];
    int a[];
    cout << str << endl;
    cout << b << endl;
}