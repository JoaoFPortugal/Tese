//
// Created by João Portugal on 20/10/2020.
//

#ifndef C_MODULE_AUXLABEL_H
#define C_MODULE_AUXLABEL_H

#include "auxlabel.h"
#include "auxfunc.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "mathfunctions.h"


Items *initItems(Items *_S, double *valor, int size, Waypoint *start, Waypoint *destination, Airplane *plane);
Items * addLabels(Items *S, double * _v, Items *S_2, int a, int wj, int size, int j);
Items *compareLabels(Items *result, Items *Sj_1, Items *Sj_aw, double * v, int size);
Items * copyItems(Items *S, Items *S_2,int a,int size);
Items * sumItems(Items *header , Items * source, double *v, int a, int a_wj, int size, int j);
Items *addResult(Items **res);
Label *iterateLabels(Items *current, Label *_currentList);
Label *iterateValues(Label *_newValue, Label *_currentFinalList);
void findTargetSumSubsets(double *input, double target, double * _ramp, int index, int size, PossibleSolution ** _ps, int originalsize, int * arrayofindexes);
int checkRestrictions(Waypoint *newItem, Items *S, int a, Restriction *_list, Waypoint **listofWaypoints, Waypoint *start);
int verifyRestrictions(Waypoint *a, Waypoint *b, Restriction *_list);
int intersectsRestriction(Waypoint *a, Waypoint *b, Restriction *res);
int breaksRestriction(Waypoint *a,Waypoint *b, Restriction *res);
SecondObjective *secondobjective(PossibleSolution *ps, int numberofitems,Waypoint **list, Waypoint *start,Airplane *plane);

#endif //C_MODULE_AUXLABEL_H
