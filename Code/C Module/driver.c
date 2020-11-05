//
// Created by João Portugal on 05/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "labelingalg.h"
#include "auxfunc.h"
#include "auxlabel.h"
#include "mathfunctions.h"


void digestline(){
    scanf("%*[^\n]");
    scanf("%*1[\n]");
}


int main(int argc, char **argv){

    int numberofitems = 6;
    int capacity = 50;
    int size = 2;
    int i;
    double latitude,longitude,altitude;
    double *firstobjective = (double*)malloc(numberofitems * sizeof(double));
    int *indexarray = (int*)malloc(numberofitems *sizeof(int));
    int numberofwaypoints;


    uint32_t sizeOfHashtable = numberofitems * capacity;
    uint32_t currentSizeOfHashtable = 0;




    Airplane *plane = malloc(sizeof(struct Airplane));
    plane->consumptionRate = 2;
    plane->fuelQuantity = 500;
    plane->speed = 350;
    plane->weight = 9207;



    Items **S = initS(numberofitems,&sizeOfHashtable,&currentSizeOfHashtable);



    Waypoint *start = malloc(sizeof(struct Waypoint));
    Waypoint *destination = malloc(sizeof(struct Waypoint));


    scanf("%lf %lf %lf",&latitude,&longitude,&altitude);
    digestline();
    start->latitude = latitude;
    start->longitude = longitude;
    start->altitude = altitude;

    start->latitude = 5;
    start->longitude = 10;


    scanf("%d",&numberofwaypoints);

    i=0;
    while(i!=numberofwaypoints){
        printf("hello\n");
        i++;
    }


    scanf("%lf %lf %lf\n",&destination->latitude,&destination->longitude,&destination->altitude);

    int numberofrestrictions;
    scanf("%d",&numberofrestrictions);


    Restriction *listofRestrictions = NULL;
    Restriction *headOfRestrictions = NULL;

    i=0;
    int type = 0;

    double xCenter, yCenter, zCenter, radius;

    while(i<numberofrestrictions){

        scanf("%d",&type);

        if(type == 0){
            if(listofRestrictions == NULL){
                listofRestrictions = malloc(sizeof(struct Restriction));
                listofRestrictions->type = 0;
                listofRestrictions->sphere =  malloc(sizeof(struct Sphere));
                scanf("%lf %lf %lf %lf",&xCenter,&yCenter,&zCenter,&radius);
                listofRestrictions->sphere->xCenter = xCenter;
                listofRestrictions->sphere->yCenter = yCenter;
                listofRestrictions->sphere->zCenter = zCenter;
                listofRestrictions->sphere->radius = radius;
                listofRestrictions->next = NULL;
                headOfRestrictions = listofRestrictions;
            }
            else{
                Restriction *tmp = malloc(sizeof(struct Restriction));
                tmp->type = 0;
                tmp->sphere = malloc(sizeof(struct Sphere));
                scanf("%lf %lf %lf %lf",&tmp->sphere->xCenter,&tmp->sphere->yCenter,&tmp->sphere->zCenter,&tmp->sphere->radius);
                listofRestrictions->next = tmp;
                listofRestrictions = listofRestrictions->next;
            }
        }

        i++;
    }


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




    Items **res = run(S,v,numberofitems,capacity,size,list,headOfRestrictions,start,plane,&sizeOfHashtable,&currentSizeOfHashtable);


/*

   res[numberofitems+1] = addResult(res,numberofitems);


   if(res[numberofitems+1]->label == NULL){
       printf("Empty Solution\n");
       return 1;
   }

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
  */
}





