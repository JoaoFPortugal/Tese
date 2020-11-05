//
// Created by Jo�o Portugal on 07/05/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define True 1
#define False 0




uint32_t hash6432shift(uint64_t key) {

    key = (~key) + (key << 18);
    key = key ^ (key >> 31);
    key = (key + (key << 2)) + (key << 4);
    key = key ^ (key >> 11);
    key = key + (key << 6);
    key = key ^ (key >> 22);

    return (uint32_t) key;
}


 Items ** hinsert(Items **ht, uint32_t *htsz, uint32_t *htn, int j,int a) {

    //concatenation


     uint64_t tmp;
     tmp = j;
     tmp <<= 32;
     tmp |= a;


     if (*htn > ((*htsz) >> 1)) {

        (*htsz) <<= 1; // multiplicar por 2

        Items** ht_old = ht;

        ht = malloc(sizeof(Items*) * (*htsz));

        *htn = 0;

        uint32_t k;
        for (k = 0; k < ((*htsz) >> 1); k++)
            if (ht_old[k] != NULL)
                ht = hinsert(ht, htsz, htn, ht_old[k]->j, ht_old[k]->a);

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
    ht[i]->label = NULL;

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
        return ht[i];
    } else {
        i = (i + 1) % (*htsz);
    }
}

    return NULL;
}





int main(int argc, char ** argv){

    int capacity = 500;
    int numberofitems = 10;

    uint32_t size = capacity * numberofitems;
    uint32_t currentsize = 0;

    Items **hashtable = malloc(sizeof(Items*)*size);

    int a = 5;
    int j = 6;

    hashtable = hinsert(hashtable,&size,&currentsize,j,a);

    Items *Sja = hfind(hashtable,&size,j,a);


    printf("Found item and j a is %d %d\n", Sja->j,Sja->a);

    return 1;

}


