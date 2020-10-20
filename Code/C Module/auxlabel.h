//
// Created by João Portugal on 20/10/2020.
//

#ifndef C_MODULE_AUXLABEL_H
#define C_MODULE_AUXLABEL_H

#include <math.h>
#include "auxlabel.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct ItemLabels{
    double latitude;
    double longitude;
    int tag;
    struct Label *label;
    struct ItemLabels *next;
}ItemLabels;


typedef struct Label{
    int *value;
    struct Label *next;
}Label;


ItemLabels *initItems(ItemLabels *S, int w, int *v, int size);
ItemLabels * addLabels(ItemLabels *S, int * _v, ItemLabels *S_2, int a, int wj, int size);
ItemLabels *compareLabels(ItemLabels *result, ItemLabels *Sj_1, ItemLabels *Sj_aw, int * v, int size);
ItemLabels * copyVector(ItemLabels *S, ItemLabels *S_2,int a,int size);
ItemLabels * sumVectors(ItemLabels *header , ItemLabels * source, int *v, int a, int a_wj, int size);



#endif //C_MODULE_AUXLABEL_H
