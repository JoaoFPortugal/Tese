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

static uint32_t *
hdelete(uint32_t *ht, uint32_t *htsz, uint32_t *htn, struct edge *elst,
        uint32_t li) {

    uint64_t tmp;
    tmp = elst[li].x;
    tmp <<= 32;
    tmp |= elst[li].y;
    uint32_t i = hash6432shift(tmp) % (*htsz);

    while (li != ht[i])
        i = (i+1) % (*htsz);

    ht[i] = 0xffffffff;
    i = (i+1) % (*htsz);

    while (ht[i] != 0xffffffff) {
        li = ht[i];
        ht[i] = 0xffffffff;
        ht = hinsert(ht, htsz, htn, elst, li);
        i = (i+1) % (*htsz);
    }

    (*htn) --;

    return ht;
}


int main(int argc, char ** argv){
    FILE *fp;
    readFile(fp);
}


