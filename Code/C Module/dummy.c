//
// Created by Jo�o Portugal on 07/05/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define True 1
#define False 0



static uint32_t
hash6432shift(uint64_t key) {

    key = (~key) + (key << 18);
    key = key ^ (key >> 31);
    key = (key + (key << 2)) + (key << 4);
    key = key ^ (key >> 11);
    key = key + (key << 6);
    key = key ^ (key >> 22);

    return (uint32_t) key;
}











int main(int argc, char ** argv){




    return 1;

}


