//
// Created by João Portugal on 05/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "labelingalg.h"
#include "auxfunc.h"
#include "auxlabel.h"
#include "mathfunctions.h"





int main(int argc, char **argv){

    int numberofitems = 6;
    int capacity = 50;
    int size = 2;
    int i;

    double *firstobjective = (double*)malloc(numberofitems * sizeof(double));
    int *indexarray = (int*)malloc(numberofitems *sizeof(int));


    Airplane *plane = malloc(sizeof(struct Airplane));
    plane->consumptionRate = 2;
    plane->fuelQuantity = 500;
    plane->speed = 350;
    plane->weight = 9207;

    Restriction *listOfRestrictions = NULL;

    Items **S = initS(numberofitems);

    Waypoint *start = malloc(sizeof(struct Waypoint));
    Waypoint *destination = malloc(sizeof(struct Waypoint));

    start->latitude = 5;
    start->longitude = 10;

    destination->latitude = 7;
    destination->longitude = 1;


    PossibleSolution *ps = (struct PossibleSolution*) malloc(sizeof (struct PossibleSolution));
    ps->next = NULL;

    Waypoint **list = initWaypoints(numberofitems,start,destination);
    mergeSort(&list,0,numberofitems-2);

    list[numberofitems-1] = destination;

    double **v = (double **)malloc(numberofitems * sizeof(double *));

    for (i=0; i<numberofitems; i++) {
        v[i] = (double *) malloc(2 * sizeof(double));

    }


    for(i=0;i<numberofitems;i++){
        v[i][0] = calculateValue(list[i],start,destination);
    }




    Items **res = run(S,v,numberofitems,capacity,size,list,listOfRestrictions,start,plane);



   res[numberofitems+1] = addResult(res,numberofitems);


    double *bestlabel = res[numberofitems+1]->label->value;


    for(i=0;i<numberofitems;i++){
      //  printf("first objective is gonna be %f\n",v[i][0]);
        firstobjective[i] = v[i][0];
        indexarray[i] = 0;
    }






    findTargetSumSubsets(firstobjective, -bestlabel[0], NULL,0, 0,
        &ps, numberofitems,indexarray);




    PossibleSolution *prev = ps;
    ps = ps->next;
    free(prev);

    SecondObjective *secondObjective = secondobjective(ps,numberofitems,list,start,plane);

    int *finalSolution = findSecondSolution(ps,secondObjective,-bestlabel[1], numberofitems);


    Waypoint **head = list;

    printf("%f %f\n", start->latitude,start->longitude);

    for(i=0;i<numberofitems;i++){


        if(finalSolution[i] == 1){
          printf("%f %f\n", head[i]->latitude,head[i]->longitude);
      }
  }

  free(indexarray);
  free(firstobjective);
  free(start);
  freeItems(res,numberofitems+2);
  freeWaypoints(list, numberofitems);
  freeValue(v,numberofitems);
  freePS(ps);
  free(plane);

}





