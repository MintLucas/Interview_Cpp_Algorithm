#include "LeetCode_Sum20191212.hpp"
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include "process_alignres.h"
using namespace std;

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

int binarySearch(vector<int> vec, int n){
    if (vec.size() < 1) {
        return -1;
    }
    int lo = -1, hi = vec.size(), mid = 0;
    while (hi - lo > 1) {
        mid = lo + (hi - lo)/2;
        if (vec[mid] < n) {
            lo = mid;
        }
        else{
            hi = mid;
        }
    }
    return vec[lo + 1] == n ? lo + 1 : -1;
}


int main(){
    
    
    char *input = "320 510 0 去";
    int tt = strlen(input);
//    align_node_t *out = load_node(input, " ");
//   align_node_t* align_node_list_ip = read_align("/Users/zhipeng/win10/OneDrive/Interview_Cpp_Algorithm/LeetCode/01_align.res");
    align_node_t* align_node_list_ip = read_align("/Users/zhipeng/jupyter/tmp/01_align.res");
//    to_alignres(align_node_list_ip, "/Users/zhipeng/jupyter/tmp/cres");
    
    align_node_t* align_node_list_op = read_align("/Users/zhipeng/jupyter/tmp/txtres");
    to_awkres(align_node_list_op, "/Users/zhipeng/jupyter/tmp/awkres");
    
    
    
    
    
    
//    align_node_t *re_out = (align_node_t*)realloc(out, 2*sizeof(align_node_t*));
//    align_node_t *t = re_out+sizeof(align_node_t*);
    if(3 >= 2 == 1)
        cout << "yes" << endl;
    int *a[2];
    int b[1]={33};
    char dat[3];
    char *aa = "hello";
    memcpy(dat, aa, strlen(aa)+1);
    vector<int> vec = {0};
    
    return 0;
    
}




char *Trim(char *str,char c)
{

    //strlen不带最后的结束符
    int len = strlen(str) + 1;
    int i = 0;
    int count = 0;
    
    if(0 == len)
    {
        return str;
    }
    
    for (i = 0; i < len; ++i) {
        if(str[i] == c){
            count++;
            continue;
        }
        else{
            str[i - count] = str[i];
        }
    }
//    if(str[len-count - 2] == '\n')
//        str[len - count - 2] = '\0';
    
        
    int len2 = strlen(str);
//    str[len - count] = '\0';
    int len3 = strlen(str);
    return str;
    
}

int removeElement(vector<int>& nums, int val) {
    int count = 0;
    for(int i = 0; i < nums.size(); ++i){
        if(nums[i] == val){
            count++;
            continue;
        }
        else{
            nums[i - count] = nums[i];
        }
    }
    nums.erase(nums.end()-count,nums.end());
    return nums.size() - count;
}

int removeDuplicatesA(vector<int>& nums) {
    int i = 1, j = 1, count = 1;
    for(; i < nums.size(); ++i){
        if(nums[i] == nums[i - 1]){
            count++;
            if(count < 3)
                nums[j++] = nums[i];
        }
        else{
            count = 1;
            nums[j++] = nums[i];
        }
    }
    return j;
}
long int vector_to_num(vector<int> &vec){
    int len = vec.size();
    long int sum = 0;
    for (int i = 0; i < len; ++i) {
        sum = sum * 10 + vec[i];
    }
    return sum;
}
vector<int> num_to_vec(vector<int> &vec,long int num){
    int len = vec.size();
    int i = 0;
    while (num != 0) {
        if(len == 0){
            vec.insert(vec.begin(), num%10);
            break;
        }
        vec[--len] = num%10;
        num /= 10;
    }
    return vec;
}

vector<int> plusOneA(vector<int>& digits) {
    int len = digits.size();
    if(len < 1) return digits;
    long int num = vector_to_num(digits);
    digits = num_to_vec(digits, num+1);
    return digits;
}

vector<int> plusOneB(vector<int>& digits){
    int len = digits.size();
    if(len < 1) return digits;
    if(digits[--len] != 9)
        digits[len]++;
    else{
        while (len >= 0 && digits[len] == 9) {
            digits[len--] = 0;
        }
        if(len == -1)
            digits.insert(digits.begin(), 1);
        else
            digits[len]++;
    }
    return digits;
}

vector<int> plusOne(vector<int>& digits){
    int len = digits.size();
    if(len < 1) return digits;
    int sum = 0;
    int one = 1;
    for (int i = len-1; i >= 0; --i) {
        //个位 也可以溢出比如加4 one = sum/10还是进一位
        sum = one + digits[i];
        //是否进位标志，如果进位下一次循环加上即可
        one = sum/10;
        //个位取余 或者总数值取余一样的
        digits[i] = sum%10;
    }
    if(one > 0)
        digits.insert(digits.begin(), 1);
    return digits;
}

void tess(int *a){
    cout << "1 " <<endl;
}


