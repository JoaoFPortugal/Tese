//
// Created by João Portugal on 07/05/2020.
//

#ifndef C_MODULE_QUADTREE_H
#define C_MODULE_QUADTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "quadTree.h"

#define QUADTREE_NOT_ALONE (-1.f)

#define QUADTREE_EMPTY (-2.f)

typedef struct coords{
    double mLon;
    double mLat;
}hs_coords;

struct qt {
    /*@null@ *//*@dependent@ */ struct qt *fhg;
    /*@null@ *//*@dependent@ */ struct qt *fhd;
    /*@null@ *//*@dependent@ */ struct qt *fbg;
    /*@null@ *//*@dependent@ */ struct qt *fbd;
    double value;
    double weight;
    size_t size;
    hs_coords coords;
};



typedef struct stock{
    double lat;
    double lon;
    double pot;
} Stock;

typedef struct qt *QuadT;

double is_alone(const QuadT tree, const Stock * stocks,
                size_t stocks_size, double *lat, double *lon);

QuadT create_quadtree();

#define STACK_SIZE 65536
#define STACK_HEIGHT 1024

QuadT qstack[STACK_HEIGHT];
int qstack_curr = (-1);
size_t qstack_index = STACK_SIZE;


#endif //C_MODULE_QUADTREE_H
