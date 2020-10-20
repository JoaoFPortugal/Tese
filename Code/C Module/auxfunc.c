//
// Created by João Portugal on 05/08/2020.
//
#include <math.h>
#include "auxfunc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "auxlabel.h"



int dominated(int *dominated, Label  *dominatorlabel, int size){



    if(dominatorlabel == NULL){
      return 0;
    }

    int *dominator = dominatorlabel->value;

    int i;
    int x1;
    int x2;
    for(i=0;i<size;i++){
        x1 = dominated[i];
        x2 = dominator[i];

        if(x1>x2){
            return 0; //label 1 is non dominated
        }
    }
    return 1; //label 1 is dominated;
}







//init label in S[1]^0 to {0,...,0}
//init label in S[1]^w1 to {-v1,...,-vr}




//aux functions


int *neg(int* src, int size){
  int i;
  int * p = malloc(size * sizeof(int));
  for(i=0;i<size;i++){
    p[i]= -src[i];
  }
  return p;
}


int lexmin(int *label1, int *label2, int size){
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



int *labelsum(int  *src1, int  *src2, int len){

    int *v = (int*)malloc(sizeof(int)*len);
    int i;

    for(i=0;i<len;i++){
        int negv = -src2[i];
       v[i] = src1[i] + negv;
    }

    return v;
}


void printVector(int *T,int numberofelements){
  if(T==NULL){
    printf("Empty\n");
    return;
  }
  int i;

  for(i=0;i<numberofelements;i++){
    printf("%d ",T[i]);
  }
  printf("\n");
  return;
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


int * addV(int *V, int a, int elements)
{
  int *p;

  if (V == NULL)
    {
      p = (int *) malloc (sizeof (int));
      p[0] = a;
      return p;
    }

  else
    {
      int * p = (int*) malloc((elements+1)*sizeof(int));
      memcpy(p,V,elements*sizeof(int));
      p[elements]=a;
      free(V);
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



void freeItemLabels(ItemLabels **res, int numberofitems){

  int i;
  for(i=0;i<numberofitems;i++){
    printf("freeing node i: %d \n\n",i);
    freeItemLabel(res[i]);
  }
  free(res);
}

void freeItemLabel(ItemLabels *item){
  ItemLabels *freed = item;
  ItemLabels *prev;
  Label *label;

  while(freed!=NULL){
    label = freed->label;
    printf("With tag: %d\n\n",freed->tag);
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
      printf("With label: ");
      printVector(freed->value,2);
      printf("\n\n");
      free (freed->value);
      prev = freed;
      freed = freed->next;
      free (prev);
    }
}


void freeValue(int **v, int r){
  int i;
  for(i=0;i<r;i++){
    free(v[i]);
  }
  free(v);
}




double distance(double lat1, double lon1, double lat2, double lon2, char unit) {
    double theta, dist;
    if ((lat1 == lat2) && (lon1 == lon2)) {
        return 0;
    }
    else {
        theta = lon1 - lon2;
        dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
        dist = acos(dist);
        dist = rad2deg(dist);
        dist = dist * 60 * 1.1515;
        switch(unit) {
            case 'M':
                break;
            case 'K':
                dist = dist * 1.609344;
                break;
            case 'N':
                dist = dist * 0.8684;
                break;
        }
        return (dist);
    }
}


double deg2rad(double deg) {
    return (deg * pi / 180);
}


double rad2deg(double rad) {
    return (rad * 180 / pi);
}



ItemLabels *addNode(ItemLabels *S, int tag){
    ItemLabels *tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = tag;
    tmp->label = NULL;
    tmp->next = S->next;
    S->next  = tmp;
    return tmp;
}




int inBoundary(NoFlyZone *nf, Point *p){
    if(p == NULL || nf == NULL){
        return 0;
    }

    int x = p->xCoords;
    int y = p->yCoords;

    if(x>=(nf->xBoundaries[0]) && x<=(nf->xBoundaries[1]) && y >= (nf->yBoundaries[0]) && y <= (nf->yBoundaries[1])){
        return 1;
    }

    return 0 ;
}



int segmentCollision(LineSegment *ls, Circle *circle){
    double cx = circle->xCenter;
    double cy = circle->YCenter;

    double dx = ls->X[1]-ls->X[0];
    double dy = ls->Y[1]-ls->Y[0];

    double A = dx * dx + dy * dy;
    double B = 2 * (dx * (ls->X[0]-cx) + dy * (ls->Y[0]-cy));
    double C = (ls->X[0] - cx) * (ls->X[0] - cx) + (ls->Y[0] - cy) * (ls->Y[0] - cy) - (circle->radius * circle->radius);
    double det = B * B - 4 * A * C;

    if(A<=EPS || det < 0){
        return 0;
    }

    return 1;

}


double max(double a, double b){
    if(a>=b){
        return a;
    }

    else{
        return b;
    }
}


double min(double a, double b){
    if(a<=b){
        return a;
    }
    else{
        return b;
    }
}

double time(double distance, double speed) {             //speed in kts, distance in km
    double time = distance * 3600 / (speed * 1.852);
    return time;
}


double shortestDistance(Point *point, LineSegment *ls){
    double A = point->xCoords - ls->X[0];
    double B = point->yCoords - ls->Y[0];
    double C = ls->X[1] - ls->X[0];
    double D = ls->Y[1] - ls->Y[0];

    double dot = A * C + B*D;
    double len_sq = C*C + D*D;
    double param = -1;
    if(len_sq != 0){
        param = dot / len_sq;
    }

    double xx, yy;

    if(param < 0){
        xx = ls->X[0];
        yy = ls->Y[0];
    }
    else if(param > 1){
        xx = ls->X[1];
        yy = ls->Y[1];
    }

    else{
        xx = ls->X[0] + param * C;
        yy = ls->Y[0] + param*D;
    }

    double dx = point->xCoords - xx;
    double dy = point->yCoords - yy;

    double result = sqrt(dx * dx + dy * dy);

    return result;
}


double turntime(int currentHeading, int futureHeading, double speed, int maxBankAngle){
    double rateofturn = (1.091 * tan(maxBankAngle))/speed;

    int turnangle;
    int diff;

    if(currentHeading>futureHeading){
        diff = currentHeading - futureHeading;
    }
    else{
        diff = futureHeading - currentHeading;
    }

    if(diff < 180){
        turnangle = abs(currentHeading-futureHeading);
    }

    else{
        if(currentHeading > futureHeading){
            turnangle = (360-currentHeading) + futureHeading;
        }
        else{
            turnangle = (360 -futureHeading) + currentHeading;
        }
    }

    double time = turnangle / rateofturn;

    return time;
    
}

