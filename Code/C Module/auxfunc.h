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
#include <limits.h>
#include "auxfunc.h"
#include "structs.h"
#include "auxlabel.h"
#include "mathfunctions.h"


/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  Function prototypes                                           :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
Items ** initS();
Waypoint **initWaypoints(int numberofitems, Waypoint *start, Waypoint *destination);
int insideArray(int *T, int a, int size);
int lexmin(double *label1, double *label2, int size);
double *labelsum(double  *src1, double  *src2, int len);
int dominated(double *label1, Label  *label2, int size);
double *neg(double* src, int size);
int *cpVec(int* V,int elements);
int * addV(int *V, int a, int *elements);
double setSum(double *v);
void freeValue(double **v, int r);
Items *addNode(Items *S, int tag);
int dominatedNeg(double *dominated, double *v, int size);
double *pickBestLabel(Label *label);
double getSum(double *v, int size);
int *findSecondSolution(struct PossibleSolution *ps, SecondObjective *secondobjective, double target, int size);
double calculateValue(Waypoint *waypoint, Waypoint *start, Waypoint *destination);
double calculateWeightValue(Waypoint *destination, Items *S,int a_w_j,Waypoint **listOfWaypoints, Waypoint *start, Airplane *plane);
int* calculateWeightRestriction(Waypoint *destination, Items *S,Waypoint **listOfWaypoints, Waypoint *start, Airplane *plane, int *_arrayweightsize);
void printItems(Items *S);
void printLabels(Label *label);
void printVector(double *T, int elements);
void printPS(PossibleSolution *ps);
void printWaypoints(Waypoint **list,int numberofitems);
void printIntVector(int *v, int size);
void freePS(PossibleSolution *ps);
void freeItems(Items **res, int numberofitems);
void freeItemLabel(Items *item);
void freeLabels(Label *label);
void freeWaypoints(Waypoint ** list, int numberofitems);
void mergeSort(Waypoint ***_arr, int l, int r);
void merge(Waypoint ***_arr, int l, int m, int r);

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
#endif //C_MODULE_AUXFUNC_H
