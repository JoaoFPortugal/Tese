//
// Created by Jo�o Portugal on 07/05/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define True 1
#define False 0


typedef struct Items{
    int a;
    int j;
    int lastitem;
    struct Label *label;
}Items;


uint32_t hash6432shift(uint64_t key) {

    key = (~key) + (key << 18);
    key = key ^ (key >> 31);
    key = (key + (key << 2)) + (key << 4);
    key = key ^ (key >> 11);
    key = key + (key << 6);
    key = key ^ (key >> 22);

    return (uint32_t) key;
}


 Items ** hinsert(Item **ht, uint32_t *htsz, uint32_t *htn, int x,int y) {

    //concatenation

     uint64_t tmp;
     tmp = x;
     tmp <<= 32;
     tmp |= y;


     if (*htn > ((*htsz) >> 1)) {

        (*htsz) <<= 1; // multiplicar por 2

        Items** *ht_old = ht;

        ht = malloc(sizeof(Items*) * (*htsz));

        *htn = 0;

        uint32_t k;
        for (k = 0; k < ((*htsz) >> 1); k++)
            if (ht_old[k] != NULL)
                ht = hinsert(ht, htsz, htn, ht_old[k]->a, ht_old[k]->j);

        free(ht_old);
    }


uint32_t i = hash6432shift(tmp) % (*htsz);

while (ht[i] != NULL)
i = (i+1) % (*htsz);


ht[i] = malloc(sizeof(Items));
ht[i]->a = x;
ht[i]->j = y;

(*htn) ++;

return ht;
}




//x = j, y = a;



Items * hfind(Items **ht, uint32_t *htsz, uint32_t x, uint32_t y) {

    uint64_t tmp;
    tmp = x;
    tmp <<= 32;
    tmp |= y;

    uint32_t i = hash6432shift(tmp) % (*htsz);


    while (ht[i] != NULL)
        if (x == ht[i]->a && y == ht[i]->j)
            return ht[i];
        else
            i = (i+1) % (*htsz);

    return NULL;
}





int main(int argc, char ** argv){

    int capacity = 500;
    int numberofitems = 10;

    int size = capacity * numberofitems;
    int currentsize = 0;

    Items **hashtable = malloc(sizeof(Items*)*size);



   hfind(uint32_t *ht, uint32_t *htsz, struct edge * elst,
                   uint32_t x, uint32_t y)

    int a = 5;
    int j = 6;

    hashtable = hinsert(hashtable,&size,&currentsize,a,j);

    Items *Sja = hfind(hashtable,size,a,j);


    return 1;

}


