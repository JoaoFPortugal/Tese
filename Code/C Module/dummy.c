//
// Created by Jo�o Portugal on 07/05/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define True 1
#define False 0



void readFile(FILE *fp){
    float latitude,longitude,altitude;
    int numberofwaypoints;
    int i;

    fp = fopen("waypoints.txt","r");

    fscanf(fp,"%d",&numberofwaypoints);

    for(i=0;i<numberofwaypoints;i++){
        fscanf(fp,"%f %f %f",&latitude,&longitude,&altitude);
        printf("%f %f %f\n",latitude,longitude,altitude);
    }
}



int main(int argc, char ** argv){
    FILE *fp;
    readFile(fp);
}


