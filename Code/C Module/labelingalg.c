//
// Created by João Portugal on 04/06/2020.
//
#include "auxfunc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "auxlabel.h"
#include "mathfunctions.h"


Items **run(Items **_S, double **_v, int _numberofitems,int _capacity, int _size, Waypoint **_list, Restriction *_res, Waypoint *_start, Airplane *_plane){

    Items (**S) = _S;
    double (**v) = _v;
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
    Waypoint **listOfWaypoints = _list;
    Waypoint *start = _start;
    Restriction *listOfRestrictions = _res;
    Airplane *plane = _plane;


    S[1] = initItems(S[1],v[0],size,start,listOfWaypoints[0],plane); // error checks


    T = (int *) malloc(2*sizeof(int));
    T[0]=0;
    T[1]=round(fuelconsumption(start,listOfWaypoints[0],plane)*10);

    printf("Lets begin, T is:\n");
    printIntVector(T,TCounter);


    for(j=2;j<n+1;j++) {

        int realj = j-1;
        printf("Beggining case j: %d\n\n",j);


        int arrayofweightssize;
        int *arrayofweights = calculateWeightRestriction(listOfWaypoints[realj],S[j-1],listOfWaypoints,start,plane,&arrayofweightssize);


        for (a = 0; a < capacity+1; a++) {


            printf("a is %d\n",a);
            printf("And T is: \n");
            printIntVector(T,TCounter);

            if(w_j == INT_MAX){
                continue;
            }

            printf("And w_j is %d\n", w_j);

            if (insideArray(T, a, TCounter) == 1) {

                printf("Entering first condition and adding V\n");
                printIntVector(V,VCounter);
                V = addV(V, a, VCounter);
                VCounter++;
                printIntVector(V,VCounter);

                if (insideArray(T, (a - w_j),TCounter)) {


                    int flag1 = checkRestrictions(listOfWaypoints[realj], S[j-1], a, listOfRestrictions,listOfWaypoints,start);
                    int flag2 = checkRestrictions(listOfWaypoints[realj], S[j-1], a-w_j, listOfRestrictions,listOfWaypoints,start);
                    if(flag1 == 0 && flag2 == 0){

                        v[realj][1] = calculateWeightValue(listOfWaypoints[realj],S[j-1],a-w_j,listOfWaypoints,start,plane);
                        S[j] = addLabels(S[j],v[realj],S[j-1],a,a-w_j,size,j);

                    }

                    else if(flag1 == 0 && flag2 == -1){
                        S[j] = copyVector(S[j],S[j-1],a,size); //error checks
                    }

                    else if(flag1 == -1 && flag2 == 0){
                        v[realj][1] = calculateWeightValue(listOfWaypoints[j-1],S[j-1],a-w_j,listOfWaypoints,start,plane);
                        S[j] = sumVectors(S[j], S[j-1], v[realj], a ,(a-w_j),size, j); //error checks
                    }


                } else {

                    S[j] = copyVector(S[j],S[j-1],a,size); //error checks

                }
            } else {

                if (insideArray(T, (a - w_j),TCounter)) {

                    printf("Entering 3rd condition\n");

                    int flag = checkRestrictions(listOfWaypoints[j], S[j-1], a-w_j, listOfRestrictions,listOfWaypoints,start);

                    if(flag == 0){
                        printf("Adding V");

                        v[realj][1] = calculateWeightValue(listOfWaypoints[j],S[j-1],a-w_j,listOfWaypoints,start,plane);
                        S[j] = sumVectors(S[j], S[j-1], v[realj], a ,(a-w_j),size, j); //error checks
                        V = addV(V, a, VCounter);
                        VCounter++;

                    }

                }
            }

          }

        printf("T was:\n");
        printIntVector(T,TCounter);
        free(T);
        T = cpVec(V, VCounter);
        printf("now T is\n");
        printIntVector(T,VCounter);
        TCounter = VCounter;
        VCounter = 0;
        V = NULL;
    }

    free(T);
    free(V);
    return S;

}





