//
//  process_alignres.c
//  LeetCode
//
//  Created by 李志鹏 on 2020/2/28.
//  Copyright © 2020 李志鹏. All rights reserved.
//

#include "process_alignres.h"

int align_node_clear(align_node_t* head){
    if(head == NULL) return 0;
    if (head->next == NULL) {
        free(head->start);
        free(head->end);
        free(head->uid);
        free(head->word);
        //        free(head->vad);
        free(head);
        return 0;
    }
    align_node_t* p = head, *aft = head->next;
    while (aft) {
        free(p->start);
        p->start = NULL;
        free(p->end);
        p->end = NULL;
        free(p->uid);
        p->uid = NULL;
        free(p->word);
        p->word = NULL;
        //        p->next = NULL;
        free(p);
        p = aft;
        aft = aft->next;
    }
    free(p->start);
    p->start = NULL;
    free(p->end);
    p->end = NULL;
    free(p->uid);
    p->uid = NULL;
    free(p->word);
    p->word = NULL;
    if (p->punc) {
        free(p->punc);
    }
    free(p);
    return 0;
}
align_node_t * align_node_init(){
    align_node_t * tmp = NULL;
    tmp = (align_node_t*)malloc(sizeof(align_node_t));
    tmp->start = NULL;
    tmp->end = NULL;
    tmp->uid = NULL;
    tmp->word = NULL;
    tmp->next = NULL;
    tmp->punc = NULL;
    //    tmp->vad = 0;
    return tmp;
}
align_node_t * load_node(char *input, char* delimiter){
    char *tmp_str = NULL;
    int i = 0;
    //带字符串结尾
    int len = strlen(input)+1;
    char* strCopy = NULL;
    strCopy = (char*)malloc(len*sizeof(char));
    strcpy(strCopy, input);
    int vec_len = 0;
    int index = 0;
    //    char *tmp1, *tmp2, *tmp3, *tmp4;
    char *tmp[5] = {0};
    align_node_t *res = NULL;
    res = align_node_init();
    
    for (i = 0; i < len; ++i) {
        if(strCopy[i] == delimiter[0] || strCopy[i] == delimiter[1] || strCopy[i] == '\n'){
            
            tmp_str = (char*)malloc((i-index) * sizeof(char));
            
            //            strCopy[i] = '\0';
            //            strcpy(tmp_str, &strCopy[index]);
            
            strncat(tmp_str, input+index, (i-index));
            //            printf("tmp_str地址%p\n",tmp_str);
            //tmp_str出问题经常乱指在这调Bug
            tmp[vec_len++] = tmp_str;
            index = i+1;
            tmp_str = NULL;
            //带上punc最多分为5部分
            if(vec_len >= 5) break;
        }
    }
    res->start = tmp[0];
    res->end = tmp[1];
    res->uid = tmp[2];
    res->word = tmp[3];
    if(vec_len == 5)
        res->punc = tmp[4];
    //    res->vad = 0;
    free(strCopy);
    return res;
    //    res->vad = "0";
    //    char **res = (char **)malloc(len * sizeof(char *))
}


static align_node_t* read_align(char *align){
    FILE* fa = 0, *fs = 0, *fo = 0;
    int line_num = 512;
    char readbuf[512] = {0};
    align_node_t* list_head = NULL, *rear = NULL, *p = NULL;
    int ls_id = 0, count = 0;
    fa = fopen(align, "r");
    if(fa == NULL) {
        printf("failed to open %s\n", align);
        goto end;
    }
    while (fgets(readbuf, sizeof(readbuf)-1, fa)) {
        count++;
        if (strstr(readbuf, "\n")==0) {
            strcat(readbuf, "\n");
        }
        if(count == 1){
            list_head = load_node(readbuf, " ~");
            rear = list_head;
        }
        else{
            align_node_t *tmp_node = load_node(readbuf, " ~");
            rear->next = tmp_node;
            rear = rear->next;
            memset(readbuf, 0, sizeof(line_num-1));
        }
    }
    if (fa != NULL) {
        fclose(fa);
    }
    p = list_head;
    while (p->next) {
        printf("%s", p->word);
        p = p->next;
    }
end:
    return list_head;
}

int write_sentence(align_node_t* head, char* outfile){
    if(head == NULL) return 0;
    align_node_t* p = head;
    FILE* fo = fopen(outfile, "a");
    if (fo==NULL) {
        printf("create output file failed");
    }
    char time[40960] = {0};
    char uid[40960] = {0};
    char word[40960] = {0};
    char vad[40960] = {0};
    char tmp[1024] = {0};
    while (p->next) {
        strcat(time, p->start);
        strcat(time, "~");
        strcat(time, p->end);
        strcat(time, "|");
        
        strcat(uid, p->uid);
        strcat(uid, "~");
        
        strcat(word, p->word);
        strcat(word, "~");
        
        strcat(vad, "0~");
        p = p->next;
    }
    strcat(time, p->start);
    strcat(time, "~");
    strcat(time, p->end);
    strcat(time, "|");
    
    strcat(uid, p->uid);
    
    strcat(word, p->word);
    
    strcat(vad, "0");
    fprintf(fo, "%s+%s+%s+%s\n",time,uid,word,vad);
    
    if (fo) {
        fclose(fo);
    }
    align_node_clear(head);
    return 0;
}

int to_alignres(align_node_t* head, char* outfile){
    if(head == NULL || head->next == NULL)
        return 0;
    align_node_t* aft = head->next, *sent_head = head, *p = head;
    long uid1 = atol(head->uid), nstart = atol(aft->start), end = atol(head->end);
    
    while (aft) {
        while (atol(aft->uid) == atol(p->uid) && atol(aft->start) - atol(p->end) < 3000) {
            p = aft;
            if(aft->next)
                aft = aft->next;
            else{
                write_sentence(sent_head, outfile);
                goto end;
            }
        }
        //p当前工作节点 在aft之后
        p->next = NULL;
        write_sentence(sent_head, outfile);
        sent_head = aft;
        //重新开始串一句话
        p = aft;
        if(aft->next)
            aft = aft->next;
        else{
            write_sentence(sent_head, outfile);
            break;
        }
    }
end:
    return 0;
}

int write_sentence_withpunc(align_node_t* head, align_node_t* end, char* outfile){
    if(head == NULL) return 0;
    align_node_t* p = head;
    FILE* fo = fopen(outfile, "a");
    if (fo==NULL) {
        printf("create output file failed");
    }
    
    char word[40960] = {0};
    int puncidx = 0;
    //    size_t edwordlen = sizeof(end->word)-sizeof("，");
    while (p->next) {
        strcat(word, p->word);
        p = p->next;
    }
    
    strcat(word, p->word);
    
    fprintf(fo, "%s~%s %s %s\n",head->start,end->end, head->uid, word);
    fprintf(fo, "%s~%s %s %s\n",end->end,end->end, end->uid, end->punc);
    
    if (fo) {
        fclose(fo);
    }
    align_node_clear(head);
    return 0;
}

int to_awkres(align_node_t* head, char* outfile){
    if(head == NULL || head->next == NULL)
        return 0;
    
    align_node_t* aft = head->next, *sent_head = head, *p = head;
    char* punc[4] = {"，", "。", "？", "！"};
    
    while (aft) {
        //有标点要分句
        if (p->punc) {
            p->next = NULL;
            write_sentence_withpunc(sent_head, p, outfile);
            sent_head = aft;
        }
        p = aft;
        if(aft->next)
            aft = aft->next;
        else{
            write_sentence_withpunc(sent_head, p, outfile);
            break;
        }
        
    }
end:
    return 0;
}
