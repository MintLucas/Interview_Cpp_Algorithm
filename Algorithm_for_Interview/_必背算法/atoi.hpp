/*
atoi() �Ĺ���:
    ���ַ�����C���ת�������ͣ�
    atoi() ������ǰ��Ŀո��ַ���ֱ���������ֻ������Ųſ�ʼ��ת����
    �������� ������ �� ������('\0') ʱ����ת��������������أ�����ת�������������
    ����������������� INT_MAX �� INT_MIN;
    *���� atoi ���ᴦ�� NULL ָ��
    
    �Ϸ�������
        "123"           -> 123
        "+123"          -> 123
        "-123"          -> -123
        "123abc"        -> 123
        "   123abc"     -> 123
        "a123"          -> 0

OJ:
    ���ַ���ת�������� https://www.nowcoder.com/practice/1277c681251b4372bdef344468e4f26e?tpId=13&tqId=11202&rp=2&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
    ��Ŀ��Դ����ָOffer

���Ĵ��룺
    while (*p >= '0' && *p <= '9') {
        ret = ret * 10 + (*p - '0');
        p++;
    }

    �������

*/
#pragma once
#include "../all.h"

int atoi(const char* str) {
    if (str == NULL) return 0;

    int res = 0, flag = 1;
    auto *p = str;  // str Ϊ��ָ��

    // ����ǰ��Ŀո�
    while (isspace(*p)) p++;

    // �ж�����
    if (*p == '-') flag = -1;
    if (*p == '-' || *p == '+') p++;

    // �׸��ǿ��ַ��������֣�ע�����ж�������˳��
    // if (*p < '0' && *p > '9') return 0;       // ����Ҫ

    // ѭ��ת�����������Ĵ��룩��������ж�
    while (*p >= '0' && *p <= '9') {
        int new_res = res * 10 + (*p - '0');
        if (new_res / 10 != res) {
            return flag > 0 ? INT_MAX : INT_MIN;
        }
        res = new_res;
        p++;
    }
    // ������ж�
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

ע���������𣬴���string���������±꣬����char*�ó�ָ��ָ����ֵ��
leetcode��֧��newres���ᱨ����һ�ּ�鷽����

/*
int myAtoi(string str) {
    if(str.size() < 1) return 0;
    int flag = 1, i = 0;
    //�ȹ��˿ո�
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
            //if(i > 9)��һ���뷨�������ж����
            //    break;����λ���޷��ж�"  0000000000012345678"
        }
    }
    else
        return 0;
    return flag*res;
}
*/