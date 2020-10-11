//
// Created by João Portugal on 05/08/2020.
//
#include <math.h>
#include "auxfunc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


double distance(double lat1, double lon1, double lat2, double lon2, char unit) {
    double theta, dist;
    if ((lat1 == lat2) && (lon1 == lon2)) {
        return 0;
    }
    else {
        theta = lon1 - lon2;
        dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
        dist = acos(dist);
        dist = rad2deg(dist);
        dist = dist * 60 * 1.1515;
        switch(unit) {
            case 'M':
                break;
            case 'K':
                dist = dist * 1.609344;
                break;
            case 'N':
                dist = dist * 0.8684;
                break;
        }
        return (dist);
    }
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts decimal degrees to radians             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double deg2rad(double deg) {
    return (deg * pi / 180);
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts radians to decimal degrees             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double rad2deg(double rad) {
    return (rad * 180 / pi);
}

int insideArray(int *T, int a, int size){
    int i=0;
    while(i!=size){
        if(T[i]==a){
            return 1;
        }
        i++;
    }
    return 0;
}

ItemLabels *sumVectors(ItemLabels * _S , ItemLabels * source, int *v, int a, int a_wj, int size){

  ItemLabels *S = _S;

  ItemLabels * header = S;

  ItemLabels * src = source;

  int j;


  //scan for S[j]^a

    while(header!=NULL){
        if(header->tag == a){
            break;
        }
        header = header->next;
    }

    //scan for S[j-1]^a-wj

    while(src!=NULL){
        if(src->tag == a_wj){
            break;
        }
        src = src->next;
    }

    printf("\n");
    printf("Copying to label -> %d\n",header->tag);
    printf("from label -> %d\n", src->tag);

    Label *origin = src->label;
    Label *result = header -> label;

    //while there are labels in S[j-1]^a-wj sum these to v and add them to S[j]^a



    while(origin!=NULL){

      Label *tmp = (struct Label *) malloc(sizeof(struct Label));
      tmp->next = NULL;
      tmp->value = malloc(size * sizeof(int));


      for(j=0;j<size;j++){
            tmp->value[j] = (-v[j]) + origin->value[j];
        }


        printf("Copying Vector:\n");
        printVector(tmp->value,size);
        printf("\n");


      if(result == NULL){
          header->label = tmp;
          result = tmp;

      }
      else{

          result->next = tmp;
          result = result->next;

      }
      origin = origin->next;

    }

  return S;
}



ItemLabels* copyVector(ItemLabels *_S, ItemLabels *S_2,int a, int size){



    ItemLabels *S = _S;
    ItemLabels *header = S;
    ItemLabels *sndHeader = S_2;

    while(header!=NULL){
        if(header->tag == a){
            break;
        }
        header = header->next;
    }

    while(sndHeader!=NULL){
        if(sndHeader->tag == a){
            break;
        }
        sndHeader = sndHeader->next;
    }

    printf("\n");
    printf("Copying to label -> %d\n",header->tag);
    printf("from label -> %d\n", sndHeader->tag);


    Label *tocopy = sndHeader->label;
    Label *newlabel = header->label;

    while(tocopy!=NULL){

        Label *tmp = (struct Label *) malloc(sizeof(struct Label));
        tmp->next = NULL;
        tmp->value = malloc(size * sizeof(int));
        memcpy(tmp->value,tocopy->value,size*sizeof(int));

        printf("Copying Vector:\n");
        printVector(tmp->value,size);
        printf("\n");

        if(newlabel == NULL){
            header->label = tmp;
            newlabel = header->label;
        }

        else{
            newlabel->next = tmp;
            newlabel = newlabel->next;
        }

        tocopy = tocopy->next;
    }

  return _S;
}





int dominated(int *dominated, Label  *dominatorlabel, int size){



    if(dominatorlabel == NULL){
      return 0;
    }

    int *dominator = dominatorlabel->value;



    int i;
    int x1;
    int x2;
    for(i=0;i<size;i++){
        x1 = dominated[i];
        x2 = dominator[i];

        if(x1>x2){
            return 0; //label 1 is non dominated
        }
    }
    return 1; //label 1 is dominated;
}





ItemLabels *addLabels(ItemLabels *S, int * _v, ItemLabels *S_2, int a, int wj, int size){

    ItemLabels *header = S;
    ItemLabels *sndHeader = S_2;
    ItemLabels *toadd = S_2;



    while(header!=NULL){
        if(header->tag == a){
            break;
        }
        header = header->next;
    }

    while(sndHeader!=NULL){
        if(sndHeader->tag == a){
            break;
        }
        sndHeader = sndHeader->next;
    }

    while(toadd!=NULL){
        if(toadd->tag == wj){
            break;
        }
        toadd = toadd->next;
    }
    header = compareLabels(header,sndHeader,toadd,_v,size);

  return S;

}


ItemLabels * compareLabels(ItemLabels *_result, ItemLabels *Sj_1, ItemLabels *Sj_aw, int * _v, int size){

    ItemLabels *result = _result;

    int *v = _v;

    Label *start1 = Sj_1->label;
    Label *start2 = Sj_aw->label;

    printf("HELLO!\n");
    printVector(start2->value,2);


    int res;

    Label *head = result->label;


    while(1) {

        if (start1 == NULL && start2 == NULL){
            break;
        }

        else if (start2 == NULL) {

            Label *tmp = (struct Label *) malloc(sizeof(struct Label));
            tmp->next = NULL;
            tmp->value = malloc(size * sizeof(int));

            memcpy(tmp->value,start1->value,size*sizeof(int));

            int v_dominated = dominated(tmp->value, head, size);

            if (v_dominated != 1) {

                 if(head == NULL){
                     printf("\n Adding vector to result\n");
                       printVector(tmp->value,2);
                       printf("\n");
                      result->label = tmp;
                      head = result->label;
                  }

                  else{
                      printf("\n Adding vector to result\n");
                       printVector(tmp->value,2);
                       printf("\n");
                      head->next = tmp;
                      head = head->next;
                  }
            }

            //FALTA REMOVER O ELEMENTO

            start1 = start1->next;
        }

        else if (start1 == NULL) {

            int *sum;
            sum = labelsum(start2->value, v, size);

            Label *tmp = (struct Label *) malloc(sizeof(struct Label));
            tmp->next = NULL;
            tmp->value = malloc(size * sizeof(int));
            memcpy(tmp->value,sum,size*sizeof(int));


            int v_dominated = dominated(tmp->value, head, size);

            if (v_dominated != 1) {

                 if(head == NULL){
                     printf("\n Adding vector to result\n");
                       printVector(tmp->value,2);
                       printf("\n");
                      result->label = tmp;
                      head = result->label;
                  }

                  else{
                      printf("\n Adding vector to result\n");
                       printVector(tmp->value,2);
                       printf("\n");
                      head->next = tmp;
                      head = head->next;
                  }
            }

            //FALTA REMOVER O ELEMENTO

            start2 = start2->next;
        }

        else{
            int *sum;
            sum = labelsum(start2->value, v, size);

            res = lexmin(start1->value, sum,size);


            if (res == 1) {
                Label *tmp = (struct Label *) malloc(sizeof(struct Label));
                tmp->next = NULL;
                tmp->value = malloc(size * sizeof(int));

                memcpy(tmp->value,start1->value,size*sizeof(int));



                int v_dominated = dominated(tmp->value, head, size);

                if (v_dominated != 1) {

                     if(head == NULL){
                       printf("\n Adding vector to result\n");
                       printVector(tmp->value,2);
                       printf("\n");
                       result->label = tmp;
                       head = result->label;
                    }

                      else{
                        printf("\n Adding vector to result\n");
                        printVector(tmp->value,2);
                        printf("\n");
                        head->next = tmp;
                        head = head->next;
                  }
            }
                start1 = start1->next;

            }

                //FALTA REMOVER O ELEMENTO

            else {
                  Label *tmp = (struct Label *) malloc(sizeof(struct Label));
                  tmp->next = NULL;
                  tmp->value = malloc(size * sizeof(int));

                  memcpy(tmp->value,sum,size*sizeof(int));


                  int v_dominated = dominated(tmp->value, head, size);

                  if (v_dominated != 1) {

                      if(head == NULL){
                          printf("\n Adding vector to result\n");
                          printVector(tmp->value,2);
                          printf("\n");
                          result->label = tmp;
                          head = result->label;
                      }

                      else{
                        printf("\n Adding vector to result\n");
                       printVector(tmp->value,2);
                       printf("\n");
                          head->next = tmp;
                          head = head->next;
                     }
            }

                start2 = start2->next;

                //FALTA REMOVER O ELEMENTO
            }
        }
    }
    return result;
}

ItemLabels *initItems(ItemLabels *_S, int w, int *valor, int size){

    ItemLabels *S = _S;
    ItemLabels *ptr = S;
    int i;
    Label *header;

    header = (struct Label *) malloc(sizeof(struct Label));
    header->next = NULL;
    header->value = malloc(size * sizeof(int));

    for(i=0;i<size;i++){
        header->value[i]=0;
    }

    S->label = header;



    while(ptr!=NULL){
        if(ptr->tag == w){
            break;
        }
        ptr = ptr->next;
    }

    Label *new = (struct Label *) malloc(sizeof(struct Label));

    new->value = malloc(size * sizeof(int));
    new->next = NULL;

    int *negativevalue = neg(valor,size);

    memcpy(new->value,negativevalue,size*sizeof(int));
    ptr->label = new;

    return S;
}


int *neg(int* src, int size){
  int i;
  int * p = malloc(size * sizeof(int));
  for(i=0;i<size;i++){
    p[i]= -src[i];
  }
  return p;
}


int lexmin(int *label1, int *label2, int size){
    int i;

    for(i=0;i<size;i++){
        if(label1[i]<label2[i]){
            return 1;
        }
        else if(label2[i]<label1[i]){
          return 0;
        }
    }
    return 0;
}




int *labelsum(int  *src1, int  *src2, int len){

    int *v = (int*)malloc(sizeof(int)*len);
    int i = 0;

    for(i=0;i<len;i++){
        int negv = -src2[i];
       v[i] = src1[i] + negv;
    }

    return v;
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


int *cpVec(int* V,int elements){
  if(V == NULL){

    return NULL;

  }
  int *vec;
  vec = (int*)malloc(sizeof(int)*elements);
  memcpy(vec, V,elements*sizeof(int));
  return vec;
}


int * addV(int *V, int a, int elements)
{
  int *p;

  if (V == NULL)
    {
      p = (int *) malloc (sizeof (int));
      p[0] = a;
      return p;
    }

  else
    {
      int * p = (int*) malloc((elements+1)*sizeof(int));
      memcpy(p,V,elements*sizeof(int));
      p[elements]=a;
      return p;
    }

}




void freeItemLabels(ItemLabels **res, int numberofitems){

  int i;
  for(i=0;i<numberofitems;i++){
    freeItemLabel(res[i]);
    free(res[i]);
  }
}

void freeItemLabel(ItemLabels *item){
  ItemLabels *freed = item;
  ItemLabels *prev;
  Label *label;

  while(freed!=NULL){
    label = freed->label;
    freeLabels(label);
    prev = freed;
    freed = freed->next;
    free(prev);
  }
}


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
