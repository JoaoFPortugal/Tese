//
// Created by João Portugal on 04/06/2020.
//
#include "auxfunc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "auxlabel.h"



Items **run(Items **_S, int *_W, int **_v, int _numberofitems,int _capacity, int _size){

    Items (**S) = _S;
    int (*W) = _W;
    int (**v) = _v;
    int *V = NULL;
    int *T = NULL;
    int n = _numberofitems;
    int capacity = _capacity;
    int a,j;
    int w_j;
    int VCounter = 0;
    int TCounter = 2;
    int size = _size;

    S[1] = initItems(S[1],W[0],v[0],size); // error checks


    T = (int *) malloc(2*sizeof(int));
    T[0]=0;
    T[1]=W[0];


    for(j=2;j<n+1;j++) {

      int realj = j-1;
      w_j = W[realj];

        for (a = 0; a < capacity+1; a++) {

            if (insideArray(T, a, TCounter) == 1) {

                V = addV(V, a, VCounter);
                VCounter++;



                if (insideArray(T, (a - w_j),TCounter)) {


                    S[j] = addLabels(S[j],v[realj],S[j-1],a,a-w_j,size); //error checks

                } else {

                    S[j] = copyVector(S[j],S[j-1],a,size); //error checks

                }
            } else {

                if (insideArray(T, (a - w_j),TCounter)) {

                    S[j] = sumVectors(S[j], S[j-1], v[realj], a ,(a-w_j),size); //error checks
                    V = addV(V, a, VCounter);
                    VCounter++;
                }
            }

          }
        free(T);
        T = cpVec(V, VCounter);
        TCounter = VCounter;
        VCounter = 0;
        V = NULL;
    }

    free(T);
    free(V);
    return S;

}





