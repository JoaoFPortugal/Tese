//
// Created by João Portugal on 05/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "labelingalg.h"
#include "auxfunc.h"
#include "auxlabel.h"






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


  
    Items **S = malloc(sizeof(struct Items*)*(numberofitems+1));

    for(i=0;i<numberofitems+1;i++){
        S[i] = (struct Items *) malloc(sizeof(struct Items));
        S[i]->tag = 0;
        S[i]->label = NULL;
        S[i]->next = NULL;
    }


    int r = 5, c = 2, i, j, count;

    int **v = (int **)malloc(r * sizeof(int *));

    for (i=0; i<r; i++) {
        v[i] = (int *) malloc(c * sizeof(int));
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


    int **v = calculateValue(S)

  Items **res = run(S,W, v,numberofitems,capacity,size);


  freeItems(res,numberofitems+1);
  free(W);
  freeValue(v,r);
}



