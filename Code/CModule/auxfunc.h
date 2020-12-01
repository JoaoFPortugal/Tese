//
// Created by João Portugal on 05/08/2020.
//

#ifndef C_MODULE_AUXFUNC_H
#define C_MODULE_AUXFUNC_H
#define pi 3.14159265358979323846
#define EPS 0.000001

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include "auxfunc.h"
#include "structs.h"
#include "auxlabel.h"
#include "mathfunctions.h"


/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  Function prototypes                                           :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/


Waypoint **initWaypoints(int numberofitems, Waypoint *start, Waypoint *destination, FILE *fp);
Restriction *createRestrictions();
float calculateValue(Waypoint *waypoint, Waypoint *start, Waypoint *destination);
float calculateWeightValue(Waypoint *destination, Items **S,int a_w_j,int j, Waypoint **listOfWaypoints, Waypoint *start, Airplane *plane, uint32_t *htsize);
int* calculateWeightRestriction(Waypoint *destination, Items **S,Waypoint **listOfWaypoints, Waypoint *start, Airplane *plane, int j, int *T, int TCounter, int *_arrayweightsize, uint32_t *htsize);
float *pickBestLabel(Label *label);
int *findSecondSolution(struct PossibleSolution *ps, SecondObjective *secondobjective, float target, int size);
void mergeSort(Waypoint ***_arr, int l, int r);
void merge(Waypoint ***_arr, int l, int m, int r);
int *copyArray(int* V,int elements);
int * addV(int *V, int a, int *elements);
int insideArray(int *T, int a, int size);
int dominated(float *label1, Label  *label2, int size);
float *labelsum(float  *src1, float  *src2, int len);
int dominatedNeg(float *dominated, float *v, int size);
float setSum(float *v);
float getSum(float *v, int size);
int calculateHeading(Waypoint *start, Waypoint *destination);
float *neg(float* src, int size);
int lexmin(float *label1, float *label2, int size);
void freeValue(float **v, int r);
void printItems(Items *S);
void printLabels(Label *label);
void printVector(float *T, int elements);
void printPS(PossibleSolution *ps,int numberofitems);
void printWaypoints(Waypoint **list,int numberofitems);
void printIntVector(int *v, int size);
void printS(Items **S,uint32_t *htsize);
void freePS(PossibleSolution *ps);
void freeItems(Items **res, uint32_t *sizeOfHashTable);
Items ** freeItem(Items **ht, uint32_t *htsz, uint32_t *htn, int j, int a);
Items ** deleteItems(Items **ht, uint32_t *tsz, uint32_t *htn, int j, int *itemstodelete, int counter);
void freeItemLabel(Items *item);
void freeLabels(Label *label);
void freeWaypoints(Waypoint ** list, int numberofitems);
void freeRestrictions(Restriction *res);
void freeSecondObjective(SecondObjective *secondObjective);


/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
#endif //C_MODULE_AUXFUNC_H
