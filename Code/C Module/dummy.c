//
// Created by Jo�o Portugal on 07/05/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ItemLabels{
    int tag;
    struct Label *label;
    struct ItemLabels *next;
}ItemLabels;


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

ItemLabels *changeValue(ItemLabels *S, int a){
  ItemLabels *test  = S->next;

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

ItemLabels *changeHeader(ItemLabels *_S){

  ItemLabels *S = _S;

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


ItemLabels *tryValue(ItemLabels *S){
  ItemLabels *header = S;

  header = changeHeader(header);

  return S;
}



int main(int argc, char ** argv){

  ItemLabels **S = (struct ItemLabels **) malloc(sizeof(struct ItemLabels *) * 6);
  S[0] = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  S[1] = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  S[2] = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  S[3] = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  S[4] = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  S[5] = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));






  int i;


  ItemLabels *result = S[1];
  ItemLabels *tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 3;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;


  //S[2]

  result = S[2];
  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 2;
  tmp->label = NULL;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 3;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 5;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;


  //S[3]

  result = S[3];
  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 2;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 3;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 4;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag =5;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 7;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;


  //S[4]


  result = S[4];
  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 2;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 3;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 4;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag =5;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 6;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 7;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 8;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 9;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  //S[5]

  result = S[5];
  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 2;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 3;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 4;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag =5;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 6;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 7;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 8;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;

  tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
  tmp->tag = 9;
  tmp->next = NULL;
  result->next = tmp;
  result = result->next;


  ItemLabels *res = tryValue(S[1]);
  printf("S[1] is:\n\n");
  printVector(res->label->value,2);
  return 1;

}



