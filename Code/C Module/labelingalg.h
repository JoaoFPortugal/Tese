#ifndef LABELINGALG_H_INCLUDED
#define LABELINGALG_H_INCLUDED

#include "auxfunc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "auxlabel.h"
#include "mathfunctions.h"

Items **run(Items **_S, double **_v, int _numberofitems,int capacity,int size, Waypoint **list, Restriction *_res, Waypoint *start, Airplane *plane);


#endif // LABELINGALG_H_INCLUDED
