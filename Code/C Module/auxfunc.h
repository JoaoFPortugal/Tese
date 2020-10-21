//
// Created by João Portugal on 05/08/2020.
//

#ifndef C_MODULE_AUXFUNC_H
#define C_MODULE_AUXFUNC_H
#define pi 3.14159265358979323846
#define EPS 0.000001

#include <math.h>
#include "auxfunc.h"
#include "auxlabel.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



/*::  Structure definitions                                         :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/



typedef struct NoFlyZone{
    double xBoundaries[2];
    double yBoundaries[2];
}NoFlyZone;


typedef struct Point{
    double xCoords;
    double yCoords;
}Point;


typedef struct LineSegment{
    double X[2];
    double Y[2];
}LineSegment;


typedef struct Circle{
    double radius;
    double xCenter;
    double YCenter;

}Circle;



/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  Function prototypes                                           :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double deg2rad(double);
double rad2deg(double);
double distance(double lat1, double lon1, double lat2, double lon2, char unit);
int insideArray(int *T, int a, int size);
int lexmin(int *label1, int *label2, int size);
int *labelsum(int  *src1, int  *src2, int len);
int dominated(int *label1, Label  *label2, int size);
int *neg(int* src, int size);
void printVector(int *T, int elements);
int *cpVec(int* V,int elements);
int * addV(int *V, int a, int elements);
void freeItems(Items **res, int numberofitems);
void freeItemLabel(Items *item);
void freeLabels(Label *label);
int *setSum(int *v, int size);
void freeValue(int **v, int r);
Items *addNode(Items *S, int tag);
int inBoundary(NoFlyZone *nf, Point *p);
int segmentCollision(LineSegment *ls, Circle *circle );
double max(double a, double b);
double min(double a, double b);
int dominatedNeg(int *dominated, int *v, int size);
void printLabels(Label *label);


/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
#endif //C_MODULE_AUXFUNC_H
