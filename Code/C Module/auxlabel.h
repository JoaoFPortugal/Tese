//
// Created by João Portugal on 20/10/2020.
//

#ifndef C_MODULE_AUXLABEL_H
#define C_MODULE_AUXLABEL_H

#include "auxlabel.h"
#include "auxfunc.h"
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "mathfunctions.h"

Items * hfind(Items **ht, uint32_t *htsz, uint32_t j, uint32_t a);
Items ** hinsert(Items **ht, uint32_t *htsz, uint32_t *htn, int j,int a,Label *label, int lastitem);
uint32_t hash6432shift(uint64_t key);
Items ** initS(int numberofitems, uint32_t *sizeOfHashtable, uint32_t *currentSize);
Items **initItems(Items **_S, float *valor, int size, Waypoint *start, Waypoint *destination, Airplane *plane, uint32_t *htsize, uint32_t *currentsize);
Items **addLabels(Items **S, float * _v, int a, int wj, int size, int j, uint32_t *htsize, uint32_t *currentsize);
Items *compareLabels(Items *result, Items *Sj_1, Items *Sj_aw, float * v, int size);
Items **copyItems(Items **_S,int j,int a, int size, uint32_t *htsize, uint32_t *currentsize);
Items **sumItems(Items ** _S, float *v, int a, int a_wj, int size, int j,uint32_t *htsize, uint32_t *currentsize);
Items *addResult(Items **res, int numberofitems, int capacity, uint32_t *htsize);
Label *iterateLabels(Items *current, Label *_currentList);
Label *iterateValues(Label *_newValue, Label *_currentFinalList);
void findTargetSumSubsets(float *input, float target, float * _ramp, int index, int size, PossibleSolution ** _ps, int originalsize, int * arrayofindexes);
SecondObjective *secondobjective(PossibleSolution *ps, int numberofitems,Waypoint **list, Waypoint *start,Airplane *plane);
int checkRestrictions(Waypoint *newItem, Items **S, int a, int j, Restriction *_list, Waypoint **listofWaypoints, Waypoint *start, uint32_t *htsize, Airplane *plane);
int verifyRestrictions(Waypoint *a, Waypoint *b, Restriction *_list,Airplane *plane);
int intersectsRestriction(Waypoint *a, Waypoint *b, Restriction *res);
int breaksRestriction(Waypoint *a,Waypoint *b, Restriction *res);

#endif //C_MODULE_AUXLABEL_H
