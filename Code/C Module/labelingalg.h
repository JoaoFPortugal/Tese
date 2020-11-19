#ifndef LABELINGALG_H_INCLUDED
#define LABELINGALG_H_INCLUDED

#include "auxfunc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "auxlabel.h"
#include "mathfunctions.h"

Items **run(Items **_S, float **_v, int _numberofitems,int _capacity, int _size, Waypoint **_list, Restriction *_res, Waypoint *_start, Airplane *_plane, uint32_t *htsize, uint32_t *currentsize);


#endif // LABELINGALG_H_INCLUDED
