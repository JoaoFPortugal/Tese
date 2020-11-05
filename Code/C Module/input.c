//
// Created by francisco on 03/11/20.
//


/*
 * original

5.0 10.0 20000
0
7.0 1.0 20000
1
0 2.0 5.5 3.0
0 3.0 1.5 2

 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>



static uint32_t *
hinsert(uint32_t *ht, uint32_t *htsz, uint32_t *htn, struct edge *elst, uint32_t li) {

    //concatenation

    uint64_t tmp;
    tmp = elst[li].x;
    tmp <<= 32;
    tmp |= elst[li].y;


    if (*htn > ((*htsz) >> 1)) {

        (*htsz) <<= 1; // multiplicar por 2

        uint32_t *ht_old = ht;
        ht = malloc(sizeof(uint32_t) * (*htsz));
        memset(ht, 0xff, sizeof(uint32_t) * (*htsz));
        *htn = 0;

        uint32_t k;
        for (k = 0; k < ((*htsz) >> 1); k++)
            if (ht_old[k] != 0xffffffff)
                ht = hinsert(ht, htsz, htn, elst, ht_old[k]);

        free(ht_old);
    }

    uint32_t i = hash6432shift(tmp) % (*htsz);
    while (ht[i] != 0xffffffff)
        i = (i+1) % (*htsz);

    ht[i] = li;
    (*htn) ++;

    return ht;
}


static uint32_t
hfind(uint32_t *ht, uint32_t *htsz, struct edge * elst,
      uint32_t x, uint32_t y) {

    uint64_t tmp;
    tmp = x;
    tmp <<= 32;
    tmp |= y;
    uint32_t i = hash6432shift(tmp) % (*htsz);

    while (ht[i] != 0xffffffff)
        if (x == elst[ht[i]].x && y == elst[ht[i]].y)
            return ht[i];
        else
            i = (i+1) % (*htsz);

    return 0xffffffff;
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




int main(int argc, char **argv) {

}