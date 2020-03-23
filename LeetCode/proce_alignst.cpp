//
//  proce_alignst.cpp
//  LeetCode
//
//  Created by 李志鹏 on 2020/2/23.
//  Copyright © 2020 李志鹏. All rights reserved.
//
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>

//align_node_t * load_node_array(char *input, char* delimiter){
//    char *tmp_str = NULL;
//    int i = 0;
//    int len = strlen(input) + 1;
//    char* strCopy = NULL;
//    strCopy = (char*)malloc(len*sizeof(char));
//    strcpy(strCopy, input);
//    int vec_len = 0;
//    int index = 0;
//    //    char *tmp1, *tmp2, *tmp3, *tmp4;
//    char *tmp[4] = {0};
//    align_node_t *res = NULL;
//    res = align_node_init();
//    for (i = 0; i < len; ++i) {
//        if(strCopy[i] == *delimiter || i == len-1){
//            strCopy[i] = '\0';
//            tmp_str = (char*)malloc((i-index) * sizeof(char));
//            //            strncmp(tmp_str, strCopy+index, (i-index));
//            //            printf("tmp_str地址%p\n",tmp_str);
//            strcpy(tmp_str, &strCopy[index]);
//            tmp[vec_len++] = tmp_str;
//            index = i+1;
//        }
//    }
//    res->start = tmp[0];
//    printf("值ddd%s\n",res->start);
//    res->end = tmp[1];
//    res->uid = tmp[2];
//    res->word = tmp[3];
//    //    res->vad = 0;
//    free(strCopy);
//    return res;
//    //    res->vad = "0";
//    //    char **res = (char **)malloc(len * sizeof(char *))
//}
//#include "proce_alignst.hpp"
//typedef struct align_node
//{
//    char *start;
//    char *end;
//    char *uid;
//    char *word;
//    align_node* next;
//    int vad;
//}align_node_t;
//align_node_t * align_node_init(){
//    align_node_t * tmp = (align_node_t*)malloc(sizeof(align_node_t*));
//    tmp->start = NULL;
//    tmp->end = NULL;
//    tmp->uid = NULL;
//    tmp->word = NULL;
//    tmp->vad = 0;
//    return tmp;
//}
//align_node_t * load_node(char *input, char* delimiter){
//    char *tmp_str = NULL;
//    int i = 0;
//    int len = strlen(input) + 1;
//    char* strCopy = (char*)malloc(len*sizeof(char));
//    strcpy(strCopy, input);
//    int vec_len = 0;
//    int index = 0;
//    //    char *tmp1, *tmp2, *tmp3, *tmp4;
//    char *tmp[4] = {0};
//    align_node_t *res = align_node_init();
//    for (i = 0; i < len; ++i) {
//        if(strCopy[i] == *delimiter || i == len-1){
//            strCopy[i] = '\0';
//            tmp_str = (char*)malloc((i-index) * sizeof(char));
//            //            printf("tmp_str地址%p\n",tmp_str);
//            strcpy(tmp_str, &strCopy[index]);
//            tmp[vec_len++] = tmp_str;
//            index = i+1;
//        }
//    }
//    res->start = tmp[0];
//    //    printf("值%s\n",res->start);
//    res->end = tmp[1];
//    res->uid = tmp[2];
//    res->word = tmp[3];
//    res->vad = 0;
//    free(strCopy);
//    return res;
//    //    res->vad = "0";
//    //    char **res = (char **)malloc(len * sizeof(char *))
//}
//
//static align_node_t** read_align(char *align){
//    FILE* fa = 0, *fs = 0, *fo = 0;
//    int line_num = 512;
//    char readbuf[512] = {0};
//    align_node_t** align_node_list = (align_node_t**)malloc(line_num*sizeof(align_node_t*));
//    memset(align_node_list, 0, line_num);
//    int ls_id = 0;
//    
//    fa = fopen(align, "r");
//    if(fa == NULL) {
//        printf("failed to open %s\n", align);
//        goto end;
//    }
//    while (fgets(readbuf, sizeof(readbuf)-1, fa)) {
//        align_node_t *tmp_node = load_node(readbuf, " ");
//        align_node_list[ls_id++] = tmp_node;
//        //        printf("align_node_list地址%p\n",align_node_list[ls_id-1]->start);
//        printf("值%s\n",  (align_node_list[ls_id-1]->start));
//    }
//    if (fa != NULL) {
//        fclose(fa);
//    }
//end:
//    return align_node_list;
//}
//
//
//int main(){
//    
//    
//    //    char *input = "320 510 0 去";
//    //    align_node_t *out = load_node(input, " ");
//    align_node_t** align_node_list = read_align("/Users/zhipeng/jupyter/tmp/01_align.res");
//    return 0;
//}
