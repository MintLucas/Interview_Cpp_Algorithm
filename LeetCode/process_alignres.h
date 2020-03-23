//
//  process_alignres.h
//  LeetCode
//
//  Created by 李志鹏 on 2020/2/28.
//  Copyright © 2020 李志鹏. All rights reserved.
//

#ifndef process_alignres_h
#define process_alignres_h

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct align_node
{
    char *start;
    char *end;
    char *uid;
    char *word;
    char *punc;
    struct align_node* next;
    //    char *vad;
}align_node_t;
int align_node_clear(align_node_t* head);
align_node_t * align_node_init();
align_node_t * load_node(char *input, char* delimiter);
static align_node_t* read_align(char *align);
int write_sentence(align_node_t* head, char* outfile);
int to_alignres(align_node_t* head, char* outfile);
int write_sentence_withpunc(align_node_t* head, align_node_t* end, char* outfile);
int to_awkres(align_node_t* head, char* outfile);
#endif /* process_alignres_h */
