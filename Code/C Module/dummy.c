//
// Created by Jo�o Portugal on 07/05/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define True 1
#define False 0


typedef struct Items{
    int a;
    int j;
    int lastitem;
    struct Label *label;
}Items;


typedef struct Label{
    float *value;
    int *lastitem;

    struct Label *next;
}Label;


void freeLabels(Label *label){
    Label *freed = label;
    Label *prev;

    while (freed != NULL)
    {
        free (freed->value);
        prev = freed;
        freed = freed->next;
        free (prev);
    }
}

void freeItemLabel(Items *item) {
    Items *freed = item;
    Label *label;
    label = freed->label;
    freeLabels(label);

}


uint32_t hash6432shift(uint64_t key) {

    key = (~key) + (key << 18);
    key = key ^ (key >> 31);
    key = (key + (key << 2)) + (key << 4);
    key = key ^ (key >> 11);
    key = key + (key << 6);
    key = key ^ (key >> 22);

    return (uint32_t) key;
}


Items ** hinsert(Items **ht, uint32_t *htsz, uint32_t *htn, int j,int a, Label *label) {

    //concatenation


    uint64_t tmp;
    tmp = j;
    tmp <<= 32;
    tmp |= a;


    if (*htn > ((*htsz) >> 1)) {

        (*htsz) <<= 1; // multiplicar por 2

        Items** ht_old = ht;

        ht = malloc(sizeof(Items*) * (*htsz));
        memset(ht,0,sizeof(Items*)*(*htsz));

        *htn = 0;

        uint32_t k;
        for (k = 0; k < ((*htsz) >> 1); k++)
            if (ht_old[k] != NULL) {
                ht = hinsert(ht, htsz, htn, ht_old[k]->j, ht_old[k]->a,ht_old[k]->label);
                free(ht_old[k]);
            }


        free(ht_old);
    }


    uint32_t i = hash6432shift(tmp) % (*htsz);

    while (ht[i] != NULL) {
        i = (i + 1) % (*htsz);
    }


    ht[i] = malloc(sizeof(Items));
    ht[i]->j = j;
    ht[i]->a = a;
    ht[i]->lastitem = -1;
    ht[i]->label = label;

    (*htn) ++;

    return ht;
}



Items * hfind(Items **ht, uint32_t *htsz, uint32_t j, uint32_t a) {

    uint64_t tmp;
    tmp = j;
    tmp <<= 32;
    tmp |= a;

    uint32_t i = hash6432shift(tmp) % (*htsz);

    while (ht[i] != NULL) {

        if (j == ht[i]->j && a == ht[i]->a) {
            printf("Found %d %d\n",j,a);
            return ht[i];
        } else {
            i = (i + 1) % (*htsz);
        }
    }

    return NULL;
}


Items ** hdelete(Items **ht, uint32_t *htsz, uint32_t *htn, int j, int a) {

    uint64_t tmp;
    tmp = j;
    tmp <<= 32;
    tmp |= a;
    uint32_t i = hash6432shift(tmp) % (*htsz);

    while(ht[i]!=NULL){
        if(ht[i]->j == j && ht[i]->a == a){
            break;
        }
        i = (i+1) % (*htsz);
    }

    freeItemLabel(ht[i]);
    free(ht[i]);
    ht[i] = NULL;
    i = (i+1) % (*htsz);

    while (ht[i] != NULL) {
        Items *li = ht[i];
        free(ht[i]);
        ht[i] = NULL;
        ht = hinsert(ht, htsz, htn, li->j,li->a,li->label);
        i = (i+1) % (*htsz);
    }

    (*htn) --;

    return ht;
}




int main(int argc, char ** argv){

    uint32_t htsize = 5;
    uint32_t htn = 0;
    Items **S = malloc(sizeof(Items*)*htsize);
    memset(S,0,sizeof(S)*htsize);
    S = hinsert(S,&htsize,&htn,1,5,NULL);
    S = hinsert(S,&htsize,&htn,2,5,NULL);
    Items *item = hfind(S,&htsize,1,5);
    if(item!=NULL){
        printf("Found item!\n");
    }
    S = hdelete(S,&htsize,&htn,1,5);
    item = hfind(S,&htsize,1,5);
    if(item == NULL){
        printf("Did not find item\n");
    }
    S = hdelete(S,&htsize,&htn,2,5);
    free(S);
    return 1;

}


