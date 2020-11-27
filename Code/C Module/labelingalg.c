//
// Created by João Portugal on 04/06/2020.
//
#include "auxfunc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "auxlabel.h"
#include "mathfunctions.h"


Items **run(Items **_S, float **_v, int _numberofitems,int _capacity, int _size, Waypoint **_list, Restriction *_res, Waypoint *_start, Airplane *_plane, uint32_t *htsize, uint32_t *currentsize){


    Items (**S) = _S;
    float (**v) = _v;
    int *V = NULL;
    int *T = NULL;
    int n = _numberofitems;
    int capacity = _capacity;
    int a;
    int j;
    int w_j;
    int VCounter = 0;
    int TCounter = 2;
    int size = _size;
    int av;
    int arrayofweightssize = 0;
    int *arrayofweights = NULL;
    Waypoint **listOfWaypoints = _list;
    Waypoint *start = _start;
    Restriction *listOfRestrictions = _res;
    Airplane *plane = _plane;

    S = initItems(S,v[0],size,start,listOfWaypoints[0],plane,htsize,currentsize); // error checks


    T = (int *) malloc(2*sizeof(int));
    T[0]=0;
    T[1]=round(fuelconsumption(start,listOfWaypoints[0],plane)*10);


    for(j=2;j<n+1;j++) {

        int realj = j-1;

            arrayofweights = calculateWeightRestriction(listOfWaypoints[realj],S,listOfWaypoints,start,plane,j-1,capacity,&arrayofweightssize,htsize);

            for (a = 0; a < capacity + 1; a++) {

                for(av = 0; av<arrayofweightssize;av++) {

                    w_j = arrayofweights[av];

                    if (insideArray(T, a, TCounter) == 1 && insideArray(V,a,VCounter) == 0) {



                        if (insideArray(T, (a - w_j), TCounter)) {

                            int flag1 = checkRestrictions(listOfWaypoints[realj], S, a, j-1, listOfRestrictions,
                                                      listOfWaypoints, start,htsize,plane);

                            int flag2 = checkRestrictions(listOfWaypoints[realj], S, a - w_j, j-1, listOfRestrictions,
                                                      listOfWaypoints, start,htsize,plane);



                            if (flag1 == 0 && flag2 == 0) {


                            V = addV(V, a, &VCounter);



                            v[realj][1] = calculateWeightValue(listOfWaypoints[realj], S, a - w_j, j-1,
                                                               listOfWaypoints, start, plane,htsize);



                            S = addLabels(S, v[realj], a, a - w_j, size, j,htsize,currentsize);

                        } else if (flag1 == 0 && flag2 == -1) {

                            V = addV(V, a, &VCounter);


                            S = copyItems(S,j, a, size,htsize,currentsize); //error checks


                            } else if (flag1 == -1 && flag2 == 0) {



                            v[realj][1] = calculateWeightValue(listOfWaypoints[realj], S, a - w_j, j-1,
                                                               listOfWaypoints, start, plane,htsize);



                            S = sumItems(S, v[realj], a, (a - w_j), size, j,htsize,currentsize); //error checks

                            V = addV(V, a, &VCounter);

                        }


                    } else {
                        V = addV(V, a, &VCounter);

                        S = copyItems(S, j, a, size, htsize, currentsize); //error checks

                    }
                } else {

                    if (insideArray(T, (a - w_j), TCounter) && insideArray(V,a,VCounter) == 0) {


                        int flag = checkRestrictions(listOfWaypoints[realj], S, a - w_j, j-1,listOfRestrictions,
                                                     listOfWaypoints, start,htsize,plane);



                        if (flag == 0) {

                            v[realj][1] = calculateWeightValue(listOfWaypoints[realj], S, a - w_j, j-1, listOfWaypoints,
                                                               start, plane, htsize);


                            S = sumItems(S, v[realj], a, (a - w_j), size, j,htsize,currentsize); //error checks
                            V = addV(V, a, &VCounter);

                        }

                    }
                }

            }

        }




        arrayofweightssize = 0;
        free(arrayofweights);
        free(T);
        T = copyArray(V, VCounter);
        TCounter = VCounter;
        VCounter = 0;
        V = NULL;

    }

    free(T);
    free(V);
    return S;

}


