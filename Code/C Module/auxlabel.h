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

typedef struct Items{
    double latitude;
    double longitude;
    int tag;
    struct Label *label;
    struct Items *next;
}Items;


typedef struct Label{
    int *value;
    struct Label *next;
}Label;


Items *initItems(Items *S, int w, int *v, int size);
Items * addLabels(Items *S, int * _v, Items *S_2, int a, int wj, int size);
Items *compareLabels(Items *result, Items *Sj_1, Items *Sj_aw, int * v, int size);
Items * copyVector(Items *S, Items *S_2,int a,int size);
Items * sumVectors(Items *header , Items * source, int *v, int a, int a_wj, int size);
Items *addResult(Items **res);
Label *iterateLabels(Items *current, Label *_currentList);
Label *iterateValues(Label *_newValue, Label *_currentFinalList);

#endif //C_MODULE_AUXLABEL_H
