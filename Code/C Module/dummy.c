//
// Created by Jo�o Portugal on 07/05/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define True 1
#define False 0




typdef struct PossibleSolution {

    int *v;
    struct PossibleSolution *next;

}PossibleSolution;

    /**
     * The method for finding the subsets that sum to a target.
     *
     * @param input  The input array to be processed for subset with particular sum
     * @param target The target sum we are looking for
     * @param ramp   The Temporary String to be beefed up during recursive iterations(By default value an empty String)
     * @param index  The index used to traverse the array during recursive calls
     */

    void findTargetSumSubsets(int *input, int target, int * _ramp, int index, int size,
                              PossibleSolution ** _ps, int originalsize) {

        int *ramp = _ramp;

        PossibleSolution *ps = * _ps;

        if(index > (originalsize - 1)) {

            if(getSum(ramp) == target) {

                PossibleSolution *tmp = malloc(sizeof(struct PossibleSolution));
                tmp->v = malloc(size * sizeof(int));
                memcpy(tmp->v,ramp,size*sizeof(int));

                free(ramp);

                if(ps == NULL){
                    ps = tmp;
                }
                else{
                    ps->next = tmp;
                    ps = ps->next;
                }
            }
            return;
        }

        int newsize = size+1;
        int *newramp =  malloc(newsize * sizeof(int));
        memcpy(newramp,ramp,sizeof(int)*size);
        newramp[newsize-1]=input[index];


        findTargetSumSubsets(input, target, newramp, index + 1,size+1, &ps,originalsize);
        findTargetSumSubsets(input, target, ramp, index + 1,size,&ps, originalsize);
    }


    int getSum(int *v, int size) {
        int i;
        int sum = 0;
        for (i = 0; i < size; i++) {
            sum+=v[i];
        }
        return sum;
    }

    public static void main(String[] args) {
        int [] n = {24, 1, 15, 3, 4, 15, 3};
        int counter = 1;

        findTargetSumSubsets(n, 25, "", 0);

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
    int *finalarray = (int*)malloc(size * sizeof(int));

    for(i=0;i<size;i++){
      firstobjective[i] = v[i][0];
      secondobjective[i] = v[i][1];
      finalarray[i] = 0;
    }



   int found = isSubsetSum(firstobjective,size,result[1],&finalarray);

   printVector(finalarray,5);




  return 1;

}


