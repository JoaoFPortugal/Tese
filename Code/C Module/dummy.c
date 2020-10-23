//
// Created by Jo�o Portugal on 07/05/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define True 1
#define False 0




typedef struct PossibleSolution {

    int *v;
    int size;
    int *indexarray;
    struct PossibleSolution *next;

}PossibleSolution;

int getSum(int *v, int size) {
        int i;
        int sum = 0;
        for (i = 0; i < size; i++) {
            sum+=v[i];
        }
        return sum;
    }



void findTargetSumSubsets(int *input, int target, int * _ramp, int index, int size,
                              PossibleSolution ** _ps, int originalsize, int * arrayofindexes) {

        int *ramp = _ramp;

        PossibleSolution *ps = * _ps;
        PossibleSolution *head = *_ps;

        if(index > (originalsize - 1)) {

            if(getSum(ramp,size) == target) {
                arrayofindexes[index] = 1;

                PossibleSolution *tmp = malloc(sizeof(struct PossibleSolution));
                tmp->v = malloc(size * sizeof(int));
                tmp->indexarray = malloc(originalsize * sizeof(int));
                memcpy(tmp->indexarray,arrayofindexes,originalsize * sizeof(int));
                memcpy(tmp->v,ramp,size*sizeof(int));
                tmp->size = size;
                tmp->next = NULL;

                free(ramp);

                while(head->next!=NULL){
                  head = head->next;
                }

                head->next = tmp;
            }
            return;
        }

        int newsize = size+1;
        int *newramp =  malloc(newsize * sizeof(int));
        memcpy(newramp,ramp,sizeof(int)*size);
        newramp[newsize-1]=input[index];

        arrayofindexes[index] = 1;
        findTargetSumSubsets(input, target, newramp, index + 1,size+1, &ps,originalsize, arrayofindexes);
        arrayofindexes[index] = 0;

        findTargetSumSubsets(input, target, ramp, index + 1,size,&ps, originalsize,arrayofindexes);
    }




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

void printPS(PossibleSolution *ps){


  int i = 1;
  while(ps!=NULL){


    printf("Solution %d is ", i);


    printVector(ps->v,ps->size);

    printf("and its indexes are: ");
    printVector(ps->indexarray,5);
    i++;
    ps = ps->next;
  }
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


    int result[2];
    result[0] = 16;
    result[1] = 25;

    int size = 5;

    int *firstobjective = (int*)malloc(size * sizeof(int));
    int *secondobjective = (int*)malloc(size * sizeof(int));
    int *arrayindexes = malloc(size * sizeof(int));


    for(i=0;i<size;i++){
      firstobjective[i] = v[i][0];
      secondobjective[i] = v[i][1];
      arrayindexes[i] = 0;
    }


    PossibleSolution *ps = malloc(sizeof(struct PossibleSolution));



  findTargetSumSubsets(secondobjective,25, NULL,0, 0,
   &ps, size,arrayindexes);



  PossibleSolution *prev = ps;
  ps = ps->next;
  free(prev);
  printPS(ps);


  return 1;

}


