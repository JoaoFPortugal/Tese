//
// Created by Jo�o Portugal on 07/05/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Items{
    int tag;
    struct Label *label;
    struct Items *next;
}Items;


typedef struct Label{
    int *value;
    struct Label *next;
}Label;




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

Items *changeValue(Items *S, int a){
  Items *test  = S->next;

  test->tag = 1;


  Label *newlabel = (struct Label *) malloc(sizeof(struct Label));
  newlabel->value = malloc(2 * sizeof(int));

  int start1[2];
  start1[0] = a;
  start1[1] = 3;

  memcpy(newlabel->value,start1,2*sizeof(int));

  test->label = newlabel;
  
  return S;

}

Items *changeHeader(Items *_S){

  Items *S = _S;

        int i[2];
        i[0]=2;
        i[1]=88;

        Label *tmp = (struct Label *) malloc(sizeof(struct Label));
        tmp->next = NULL;
        tmp->value = malloc(2 * sizeof(int));
        memcpy(tmp->value,i,2*sizeof(int));
        S->label = tmp;
        return S;
}


Items *tryValue(Items *S){
  Items *header = S;

  header = changeHeader(header);

  return S;
}



int main(int argc, char ** argv){

  Items **S = (struct Items **) malloc(sizeof(struct Items *) * 6);
  S[0] = (struct Items *) malloc(sizeof(struct Items));
  S[1] = (struct Items *) malloc(sizeof(struct Items));
  S[2] = (struct Items *) malloc(sizeof(struct Items));
  S[3] = (struct Items *) malloc(sizeof(struct Items));
  S[4] = (struct Items *) malloc(sizeof(struct Items));
  S[5] = (struct Items *) malloc(sizeof(struct Items));






  int i;


  Items *result = S[1];
  Items *tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 3;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;


  //S[2]

  result = S[2];
  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 2;
  tmp->label = NULL;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 3;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 5;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;


  //S[3]

  result = S[3];
  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 2;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 3;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 4;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag =5;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 7;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;


  //S[4]


  result = S[4];
  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 2;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 3;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 4;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag =5;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 6;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 7;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 8;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 9;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  //S[5]

  result = S[5];
  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 2;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 3;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 4;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag =5;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 6;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 7;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 8;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct Items *) malloc(sizeof(struct Items));
  tmp->tag = 9;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;


  Items *res = tryValue(S[1]);
  printf("S[1] is:\n\n");
  printVector(res->label->value,2);
  return 1;

}



