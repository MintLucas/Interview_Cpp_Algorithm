#include <bits/stdc++.h>
//#include <iostream>
//#include <vector>
//#include "stdafx.h"

using namespace std;

typedef struct List {
	int data;
	struct List *next;
}List;//定义一个结构体  保存链表  数据+指针
List* creat() {//创建链表
	List *p ,*head;
	head = new List;//声明头节点
	p = head;//声明移动指针  最开始指向头结点
	int x, cycle = 1;
	while (cycle)
	{
		cout << "Please input the data for single linker : ";
		cin >> x;
 
		if (x != 0)
		{
			List *s = new List;//声明List对象来保存数据  这就是一个链表的节点
			s->data = x;//将数据保存到此节点
			cout << "Input data : " << x << endl;
			p->next = s;//将此节点与头节点连接
			p = s;//向后移动指针,以便下一次链接   p一直指向链表最后的一个节点
		}
		else
		{
			cycle = 0;
			cout << "Input done! " << endl;
		}
	}
	head = head->next;
	p->next = NULL;
	return head;
}
void print(List *head) {//打印输出链表
	List *p = head;
	while (p != NULL) {
		cout << p->data;
		p = p->next;
	}
}

int main(){
    vector<int> v;
    for(int i=0; i<10; i++){
        v.push_back(i);
    }
	cout << v.size() << endl;
    vector<int>::iterator p;
    for(p=v.begin(); p != v.end(); p++){
        cout << *p << endl;
    }
    int a=3, b=4;
    cout << v[0] <<b;
	
    //List *head = creat();//引用创建链表
	//print(head);//引用打印
	//free(head);
	return 0;
}

