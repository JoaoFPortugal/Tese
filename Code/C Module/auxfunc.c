//
// Created by João Portugal on 05/08/2020.
//
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "auxfunc.h"
#include "auxlabel.h"
#include "structs.h"
#include "mathfunctions.h"



Items ** initS(int numberofitems){

    int i;
    Items **S = malloc(sizeof(struct Items*)*(numberofitems+2));

    for(i=0;i<numberofitems+2;i++){
        S[i] = (struct Items *) malloc(sizeof(struct Items));
        S[i]->tag = 0;
        S[i]->lastitem = -1;
        S[i]->label = NULL;
        S[i]->next = NULL;
    }
    return S;
}

Waypoint **initWaypoints(int numberofitems, Waypoint *start, Waypoint *destination){

    int i;

    Waypoint **list = malloc(sizeof(struct Waypoint*)*(numberofitems));

    for (i=0; i<numberofitems; i++) {
        list[i] = malloc(sizeof(struct Waypoint));

    }

    list[0]->latitude = 6;
    list[0]->longitude = 10;
    list[0]->distance_to_startingpoint = distance(start->latitude,start->longitude,list[0]->latitude,list[0]->longitude,'K');

    list[1]->latitude = 8;
    list[1]->longitude = 10;
    list[1]->distance_to_startingpoint = distance(start->latitude,start->longitude,list[1]->latitude,list[1]->longitude,'K');

    list[2]->latitude = 8;
    list[2]->longitude = 5;
    list[2]->distance_to_startingpoint = distance(start->latitude,start->longitude,list[2]->latitude,list[2]->longitude,'K');

    list[3]->latitude = 8;
    list[3]->longitude = 2;
    list[3]->distance_to_startingpoint = distance(start->latitude,start->longitude,list[3]->latitude,list[3]->longitude,'K');


    list[4]->latitude = 5;
    list[4]->longitude = 5;
    list[4]->distance_to_startingpoint = distance(start->latitude,start->longitude,list[4]->latitude,list[4]->longitude,'K');

    list[5]->latitude = destination->latitude;
    list[5]->longitude = destination->longitude;

    return list;
}








int dominated(double *dominated, Label  *dominatorlabel, int size){



    if(dominatorlabel == NULL){
      return 0;
    }

    double *dominator = dominatorlabel->value;

    int i;
    double x1;
    double x2;
    for(i=0;i<size;i++){
        x1 = dominated[i];
        x2 = dominator[i];

        if(x1>x2){
            return 0; //label 1 is non dominated
        }
    }
    return 1; //label 1 is dominated;
}


double *neg(double* src, int size){
  int i;
  double * p = malloc(size * sizeof(double));
  for(i=0;i<size;i++){
    p[i]= -src[i];
  }
  return p;
}


int lexmin(double *label1, double *label2, int size){
    int i;

    for(i=0;i<size;i++){
        if(label1[i]<label2[i]){
            return 1;
        }
        else if(label2[i]<label1[i]){
          return 0;
        }
    }
    return 0;
}



double *labelsum(double  *src1, double  *src2, int len){

    double *v = (double*)malloc(sizeof(double)*len);
    int i;

    for(i=0;i<len;i++){
        double negv = -src2[i];
       v[i] = src1[i] + negv;
    }

    return v;
}


int *cpVec(int* V,int elements){
  if(V == NULL){
    return NULL;

  }

  int *vec;
  vec = (int*)malloc(sizeof(int)*elements);
  memcpy(vec, V,elements*sizeof(int));
  free(V);
  return vec;
}


int * addV(int *V, int a, int *_elements)
{

    int elements = *_elements;
  int *p;

  if (V == NULL)
    {
      p = (int *) malloc (sizeof (int));
      p[0] = a;
      *_elements = 1;
      return p;
    }

  else
    {

        if(insideArray(V,a,elements)){
            return V;
        }

        int * p = (int*) malloc((elements+1)*sizeof(int));
        memcpy(p,V,elements*sizeof(int));
        p[elements]=a;
        free(V);
        ++*_elements;

        return p;
    }

}



int insideArray(int *T, int a, int size){
    int i=0;
    while(i!=size){
        if(T[i]==a){
            return 1;
        }
        i++;
    }
    return 0;
}


Items *addNode(Items *S, int tag){
    Items *tmp = (struct Items *) malloc(sizeof(struct Items));
    tmp->tag = tag;
    tmp->label = NULL;
    tmp->next = S->next;
    S->next  = tmp;
    return tmp;
}




int dominatedNeg(double *dominated, double *v, int size){

    double *dominator = v;

    int i;
    double x1;
    double x2;
    for(i=0;i<size;i++){
        x1 = dominated[i];
        x2 = dominator[i];

        if(x1>x2){
            return 0; //label 1 is non dominated
        }
    }
    return 1; //label 1 is dominated;
}



double setSum(double *v){

  double sum = 0.5*(-v[0]) + 0.5*(-v[1]);
  return sum;

}


double *pickBestLabel(Label *label){
  double *v = NULL;
  double currentSum;
  double newsum = 0;
  Label *head = label;
  double *copy;

  while(head != NULL){
    copy = head->value;

    if(v == NULL){
      v = copy;
      currentSum = setSum(v);
    }
    else{
      newsum = setSum(copy);
      if(newsum > currentSum){
        v = copy;
      }
      else if (newsum == currentSum){
        if(copy[1]>v[1]){
          v = copy;
        }
      }
    }

    head = head->next;

  }

  return v;
}


double getSum(double *v, int size) {
        int i;
        double sum = 0;
        for (i = 0; i < size; i++) {
            sum+=v[i];
        }
        return sum;
}

double calculateValue(Waypoint *waypoint, Waypoint *start, Waypoint *destination){

    LineSegment *lineSegment = malloc(sizeof(struct LineSegment));
    lineSegment->X[0] = start->latitude;
    lineSegment->X[1] = destination->latitude;
    lineSegment->Y[0] = start ->longitude;
    lineSegment->Y[1] = destination -> longitude;


    double distance = distancePointToSegment(waypoint, lineSegment) * 100;

    free(lineSegment);
    return -distance;

}


int *findSecondSolution(PossibleSolution *ps, SecondObjective *secondobjective, double target, int size){

  int *indexofarrays;

  SecondObjective *header = secondobjective;

  double sum=0;
  double *secondobjectivevalue;
  int i;

  while(ps!=NULL){

    indexofarrays = ps->indexarray;

    while(header!=NULL){
        secondobjectivevalue = header->objetivevalue;

        for(i=0;i<size;i++){
            sum = sum + indexofarrays[i]*secondobjectivevalue[i];
        }

        printf("Sum is %f and target is %f\n",sum,target);


        if(fabs(sum-target) < EPS ){
            return indexofarrays;
        }
        sum = 0;
        header = header->next;
    }

    header = secondobjective;
    ps = ps->next;
  }


  printf("Returning null\n");
  return 0;
}



void merge(Waypoint ***_arr, int l, int m, int r) {

    Waypoint **arr = *_arr;

    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */

    Waypoint **L = malloc(sizeof(struct Waypoint *) * n1);
    Waypoint **R = malloc(sizeof(struct Waypoint *) * n2);


    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++){
        L[i] = malloc(sizeof(struct Waypoint));
        L[i]->distance_to_startingpoint = arr[l + i]->distance_to_startingpoint;
    }


    for (j = 0; j < n2; j++) {
        R[j] = malloc(sizeof(struct Waypoint));
        R[j]->distance_to_startingpoint = arr[m + 1 + j]->distance_to_startingpoint;
    }

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray

    while (i < n1 && j < n2) {

        if (L[i]->distance_to_startingpoint <= R[j]->distance_to_startingpoint) {
            arr[k]->distance_to_startingpoint = L[i]->distance_to_startingpoint;
            i++;
        }

        else {
            arr[k]->distance_to_startingpoint = R[j]->distance_to_startingpoint;
            j++;
        }

        k++;
    }

    /* Copy the remaining elements of L[], if there
    are any */

    while (i < n1) {
        arr[k]->distance_to_startingpoint = L[i]->distance_to_startingpoint;
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {

        arr[k]->distance_to_startingpoint = R[j]->distance_to_startingpoint;
        j++;
        k++;
    }

    for(i=0;i<n1;i++){
        free(L[i]);
    }
    for(i=0;i<n2;i++){
        free(R[i]);
    }

    free(L);
    free(R);

}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */

void mergeSort(Waypoint ***_arr, int l, int r){

    Waypoint **arr = *_arr;

    if (l < r) {
// Same as (l+r)/2, but avoids overflow for
// large l and h
        int m = (l + r) / 2;


// Sort first and second halves
        mergeSort(&arr, l, m);
        mergeSort(&arr, m + 1, r);

        merge(&arr, l, m, r);
    }
}


int calculateHeading(Waypoint *start, Waypoint *destination){
    double x1 = start->latitude;
    double y1 = start->longitude;
    double x2 = destination->latitude;
    double y2 = destination->longitude;

    double down = x2-x1;
    double up = y2-y1;
    double result = up / down;
    double theta = atan(result);
    int res = round(theta);
    return abs((res%360));
}


double calculateWeightValue(Waypoint *destination, Items *S,int a_w_j,Waypoint **listOfWaypoints, Waypoint *start, Airplane *plane){
    Items *header = S;
    while(header!=NULL){
        if(header->tag == a_w_j ){
            break;
        }
        header = header->next;
    }
    int lastwaypoint = header->lastitem;
    Waypoint *origin;

    if(lastwaypoint == -1){
        origin = start;
    }
    else{
        origin = listOfWaypoints[lastwaypoint-1];
    }

    double newvalue = fuelconsumption(origin,destination,plane);

    return -newvalue;
}


int* calculateWeightRestriction(Waypoint *destination, Items *S,Waypoint **listOfWaypoints, Waypoint *start, Airplane *plane, int *_arrayweightsize){

    int arrayweightsize = 0;
    int *newarrayofweights = NULL;

    Items *header = S;
    while(header!=NULL) {

        int lastwaypoint = header->lastitem;

        Waypoint *origin;

        if (lastwaypoint == -1) {
            origin = start;

        } else {

            origin = listOfWaypoints[lastwaypoint - 1];
        }

        double newvalue = fuelconsumption(origin, destination, plane);

        int finalvalue = round(newvalue * 10);

        if (newarrayofweights == NULL) {
            newarrayofweights = malloc(sizeof(int));
            arrayweightsize = 1;
            newarrayofweights[arrayweightsize - 1] = finalvalue;

        } else {
            if (!(insideArray(newarrayofweights, finalvalue,arrayweightsize))) {
                arrayweightsize++;
                newarrayofweights =  realloc(newarrayofweights,sizeof(int) * arrayweightsize);
                newarrayofweights[arrayweightsize - 1] = finalvalue;
            }
        }
        header = header->next;
    }

    *_arrayweightsize = arrayweightsize;

    return newarrayofweights;
}

void freeItems(Items **res, int numberofitems){
    int i;
    for(i=0;i<numberofitems;i++){
        freeItemLabel(res[i]);
    }
    free(res);
}

void freeItemLabel(Items *item){
    Items *freed = item;
    Items *prev;
    Label *label;

    while(freed!=NULL){
        label = freed->label;
        freeLabels(label);
        prev = freed;
        freed = freed->next;
        free(prev);
    }
}


void freeLabels(Label *label){
    Label *freed = label;
    Label *prev;

    while (freed != NULL)
    {
        free (freed->value);
        prev = freed;
        freed = freed->next;
        free (prev);
    }
}


void freeValue(double **v, int r){
    int i;
    for(i=0;i<r;i++){
        free(v[i]);
    }
    free(v);
}

void freePS(PossibleSolution *ps){
    PossibleSolution *prev;
    while(ps != NULL){
        free(ps->indexarray);
        free(ps->v);
        prev = ps;
        ps = ps->next;
        free(prev);

    }
}

void freeWaypoints(Waypoint ** list, int numberofitems){

    int i;

    for(i=0;i<numberofitems;i++){
        free(list[i]);
    }

    free(list);
}


void printVector(double *T,int numberofelements){
    if(T==NULL){
        printf("Empty\n");
        return;
    }
    int i;

    for(i=0;i<numberofelements;i++){
        printf("%f ",T[i]);
    }
    printf("\n");
    return;
}

void printPS(PossibleSolution *ps){


    int i = 1;
    while(ps!=NULL){


        printf("Solution %d is ", i);

        printVector(ps->v,ps->size);

        printf("and its indexes are: ");
        printIntVector(ps->indexarray,5);
        i++;
        ps = ps->next;
    }
}


void printWaypoints(Waypoint **list,int numberofitems){
    int i;
    for(i=0;i<numberofitems;i++){
        printf("Waypoint %f %f with distance %f to start\n\n", list[i]->latitude,list[i]->longitude, list[i]->distance_to_startingpoint);
    }
}


void printIntVector(int *v, int size){

    if(v==NULL){
        printf("Empty\n");
        return;
    }
    int i;

    for(i=0;i<size;i++){
        printf("%d ",v[i]);
    }
    printf("\n");
    return;
}

void printLabels(Label *label){

    while(label != NULL){
        printVector(label->value,2);
        label = label->next;
    }
}


void printItems(Items *S){
    while(S!=NULL){
        printf("Item labels with tag %d are: \n",S->tag);
        printLabels(S->label);
        S = S->next;
    }
}




