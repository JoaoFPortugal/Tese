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





    FILE *fp;
    fp = fopen("waypoints.txt","r");
    int numberofitems;
    fscanf(fp,"%d",&numberofitems);
    numberofitems = numberofitems+1;
    int size = 2;
    int i;
    float latitude,longitude,altitude;
    float *firstobjective = (float*)malloc(numberofitems * sizeof(float));
    int *indexarray = (int*)malloc(numberofitems *sizeof(int));
    int numberofwaypoints;




    Waypoint *start = malloc(sizeof(struct Waypoint));
    Waypoint *destination = malloc(sizeof(struct Waypoint));


    scanf("%f %f %f",&latitude,&longitude,&altitude);
    digestline();
    start->latitude = latitude;
    start->longitude = longitude;
    start->altitude = altitude;


    scanf("%d",&numberofwaypoints);

    i=0;

    scanf("%f %f %f\n",&destination->latitude,&destination->longitude,&destination->altitude);

    int numberofrestrictions;
    scanf("%d",&numberofrestrictions);


    Restriction *listofRestrictions = NULL;
    Restriction *headOfRestrictions = NULL;

    i=0;
    int type = 0;


    while(i<numberofrestrictions){

        scanf("%d",&type);

        if(type == 0){

            if(listofRestrictions == NULL){
                listofRestrictions = malloc(sizeof(struct Restriction));
                listofRestrictions->type = 0;
                listofRestrictions->sphere =  malloc(sizeof(struct Sphere));
                scanf("%f %f %f %f",&listofRestrictions->sphere->xCenter,&listofRestrictions->sphere->yCenter,
                      &listofRestrictions->sphere->zCenter,&listofRestrictions->sphere->radius);
                listofRestrictions->next = NULL;
                headOfRestrictions = listofRestrictions;
            }
            else{
                Restriction *tmp = malloc(sizeof(struct Restriction));
                tmp->type = 0;
                tmp->sphere = malloc(sizeof(struct Sphere));
                tmp->next = NULL;
                scanf("%f %f %f %f",&tmp->sphere->xCenter,&tmp->sphere->yCenter,&tmp->sphere->zCenter,&tmp->sphere->radius);
                listofRestrictions->next = tmp;
                listofRestrictions = listofRestrictions->next;
            }
        }

        i++;
    }

    Airplane *plane = malloc(sizeof(struct Airplane));

    scanf("%d",&plane->fuelQuantity);
    scanf("%d",&plane->speed);
    scanf("%f",&plane->consumptionRate);
    scanf("%f",&plane->weight);


    int capacity = plane->fuelQuantity;
    
    uint32_t sizeOfHashtable = numberofitems * numberofitems * 2;
    uint32_t currentSizeOfHashtable = 0;


    Items **S = initS(numberofitems,&sizeOfHashtable,&currentSizeOfHashtable);


    PossibleSolution *ps = (struct PossibleSolution*) malloc(sizeof (struct PossibleSolution));
    ps->next = NULL;

    Waypoint **list = initWaypoints(numberofitems,start,destination,fp);


    mergeSort(&list,0,numberofitems-2);

    free(list[numberofitems-1]);
    list[numberofitems-1] = malloc(sizeof(struct Waypoint));
    list[numberofitems-1]->latitude = destination->latitude;
    list[numberofitems-1]->longitude = destination->longitude;
    list[numberofitems-1]->altitude = destination->altitude;

    float **v = (float **)malloc(numberofitems * sizeof(float *));

    for (i=0; i<numberofitems; i++) {
        v[i] = (float *) malloc(2 * sizeof(float));

    }


    for(i=0;i<numberofitems;i++){
        v[i][0] = calculateValue(list[i],start,destination);
    }




    S = run(S,v,numberofitems,capacity,size,list,headOfRestrictions,start,plane,&sizeOfHashtable,&currentSizeOfHashtable);

    S = hinsert(S,&sizeOfHashtable,&currentSizeOfHashtable,numberofitems+1,0,NULL,-1);


    //Items *finalItem = addResult(S,numberofitems,capacity,&sizeOfHashtable);

    Items *finalItem = NULL;
   if(finalItem == NULL){
       printf("Empty Solution\n");
       fclose(fp);
       free(indexarray);
       free(firstobjective);
       freeItems(S,&sizeOfHashtable);
       free(start);
       free(destination);
       freeValue(v,numberofitems);
       freeWaypoints(list, numberofitems);
       free(ps);
       free(plane);
       freeRestrictions(headOfRestrictions);
       return 1;
   }



    float *bestlabel = malloc(sizeof(float)*2);
    memcpy(bestlabel,finalItem->label->value,sizeof(float)*2);

    freeItems(S,&sizeOfHashtable);

    for(i=0;i<numberofitems;i++){
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

    free(bestlabel);

    Waypoint **head = list;

    printf("%f %f %f\n", start->latitude,start->longitude,start->altitude);
    if(finalSolution == NULL){
        printf("Final Solution is NULL\n");
        return 1;
    }

    for(i=0;i<numberofitems;i++){
        if(finalSolution[i] == 1){
          printf("%f %f %f\n", head[i]->latitude,head[i]->longitude,head[i]->altitude);
      }
  }

  fclose(fp);
  free(indexarray);
  free(firstobjective);
  free(start);
  free(destination);
  freeValue(v,numberofitems);
  freeWaypoints(list, numberofitems);
  freePS(ps);
  free(plane);
  freeRestrictions(headOfRestrictions);
  freeSecondObjective(secondObjective);

}





