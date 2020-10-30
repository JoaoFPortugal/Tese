//
// Created by Jo�o Portugal on 07/05/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define True 1
#define False 0



void printVector(int *T,int numberofelements){
  if(T==NULL){
    printf("Empty\n");
    return;
  }
  int i;

  for(i=0;i<numberofelements;i++){
    printf("%d ",T[i]);
  }
  printf("\n");
  return;
}


int main(int argc, char ** argv){

    int r = 5, c = 2, i;

    int **v = (int **)malloc(r * sizeof(int *));

    for (i=0; i<r; i++) {
        v[i] = (int *) malloc(c * sizeof(int));
    }


    v[0][0]=8;
    v[0][1]=3;
    v[1][0]=9;
    v[1][1]=2;
    v[2][0]=3;
    v[2][1]=10;
    v[3][0]=7;
    v[3][1]=6;
    v[4][0]=6;
    v[4][1]=9;







    return 1;

}


