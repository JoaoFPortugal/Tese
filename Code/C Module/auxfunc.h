//
// Created by João Portugal on 05/08/2020.
//

#ifndef C_MODULE_AUXFUNC_H
#define C_MODULE_AUXFUNC_H
#define pi 3.14159265358979323846
#include <math.h>
#include "auxfunc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



/*::  Structure definitions                                         :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

typedef struct ItemLabels{
    int tag;
    struct Label *label;
    struct ItemLabels *next;
}ItemLabels;


typedef struct Label{
    int *value;
    struct Label *next;
}Label;



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  Function prototypes                                           :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double deg2rad(double);
double rad2deg(double);
double distance(double lat1, double lon1, double lat2, double lon2, char unit);
int insideArray(int *T, int a, int size);
ItemLabels * sumVectors(ItemLabels *header , ItemLabels * source, int *v, int a, int a_wj, int size);
ItemLabels * copyVector(ItemLabels *S, ItemLabels *S_2,int a,int size);
ItemLabels * addLabels(ItemLabels *S, int * _v, ItemLabels *S_2, int a, int wj, int size);
int lexmin(int *label1, int *label2, int size);
int *labelsum(int  *src1, int  *src2, int len);
int dominated(int *label1, Label  *label2, int size);
ItemLabels *compareLabels(ItemLabels *result, ItemLabels *Sj_1, ItemLabels *Sj_aw, int * v, int size);
ItemLabels *initItems(ItemLabels *S, int w, int *v, int size);
int *neg(int* src, int size);
void printVector(int *T, int elements);
int *cpVec(int* V,int elements);
int * addV(int *V, int a, int elements);
void freeItemLabels(ItemLabels **res, int numberofitems);
void freeItemLabel(ItemLabels *item);
void freeLabels(Label *label);
int *setSum(int *v, int size);
void freeValue(int **v, int r);
ItemLabels *addNode(ItemLabels *S, int tag);

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
#endif //C_MODULE_AUXFUNC_H
