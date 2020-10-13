//
// Created by João Portugal on 05/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "labelingalg.h"
#include "auxfunc.h"





int main(int argc, char **argv){

    int numberofitems = 5;
    int capacity = 9;
    int size = 2;

    int *W = (int*) malloc(5*sizeof(int));
    W[0]=3;
    W[1]=2;
    W[2]=2;
    W[3]=4;
    W[4]=3;


    int r = 5, c = 2, i, j, count;

    int **v = (int **)malloc(r * sizeof(int *));

    for (i=0; i<r; i++) {
        v[i] = (int *) malloc(c * sizeof(int));
    }

    count = 0;
    for (i = 0; i <  r; i++) {
        for (j = 0; j < c; j++) {
            v[i][j] = ++count;
        }
    }

    v[0][0]=8;
    v[0][1]=3;
    v[1][0]=9;
    v[1][1]=2;
    v[2][0]=3;
    v[2][1]=10;
    v[3][0]=7;
    v[3][1]=6;
    v[4][0]=6;
    v[4][1]=9;


    ItemLabels **S = malloc(sizeof(struct ItemLabels*)*(numberofitems+1));
    S[0] = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    S[1] = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    S[2] = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    S[3] = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    S[4] = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    S[5] = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));


    S[0]->tag = 0;
    S[0]->label = NULL;
    S[0]->next = NULL;
    S[1]->tag = 0;
    S[1]->label = NULL;
    S[2]->tag = 0;
    S[2]->label = NULL;
    S[3]->tag = 0;
    S[3]->label = NULL;
    S[4]->tag = 0;
    S[4]->label = NULL;
    S[5]->tag = 0;
    S[5]->label = NULL;


  //S[1]


    ItemLabels *result = S[1];
    ItemLabels *tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 3;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result ->next;

    //S[2]

    result = S[2];
    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 2;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 3;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 5;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result ->next;


  //S[3]

    result = S[3];
    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 2;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 3;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 4;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag =5;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 7;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result ->next;


    //S[4]


    result = S[4];
    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 2;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 3;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 4;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag =5;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 6;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 7;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 8;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 9;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;

    //S[5]

    result = S[5];
    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 2;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 3;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 4;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag =5;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 6;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 7;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 8;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result->next;

    tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = 9;
    tmp->label = NULL;
    tmp->next = NULL;
    result->next = tmp;
    result = result ->next;

  ItemLabels **res = run(S,W, v,numberofitems,capacity,size);


  freeItemLabels(res,numberofitems+1);
  free(W);
  freeValue(v,r);
}



