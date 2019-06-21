//
//  Array.hpp
//  LeetCode
//
//  Created by 李志鹏 on 2019/3/18.
//  Copyright © 2019 李志鹏. All rights reserved.
//

#ifndef Array_hpp
#define Array_hpp

#include <stdio.h>
#include <vector>
using namespace std;

//int mainElement(vector<int> vec);
int continuousMaxSum(vector<int> vec);
vector<int> getLeastKnumber(vector<int> vec, int k);
int numOfone(int n);
bool cmp(int a, int b);
string printMinNum(vector<int> numbers);

bool isUglyNum(int num);
int getKuglyNum(int K);

void reverseArray(vector<int> &array, int left, int right, size_t size);
void rotateArray(vector<int> &array, int left, int mid, int right);
void deleteX(vector<int> &array, int x);
void deleteDuplication(vector<int> &array);
void vecdeleteDuplication(vector<int> &array);

void mergeSort(vector<int> &array, int low, int high);
void merge(vector<int> &array, int low, int mid, int high);
void quickSort(vector<int> &array, int low, int high);
int partitionArray(vector<int> &array, int low, int high);
void selectSort(vector<int> &array);

void insertSort(vector<int> &array);
void bubbleSort(vector<int> &array);
int binarySearch(vector<int> array, int x);


#endif /* Array_hpp */
