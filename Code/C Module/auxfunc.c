//
// Created by João Portugal on 05/08/2020.
//
#include <math.h>
#include "auxfunc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


ItemLabels *sumVectors(ItemLabels * _S , ItemLabels * source, int *v, int a, int a_wj, int size){

  ItemLabels *S = _S;

  ItemLabels * header = S;

  ItemLabels * src = source;
  ItemLabels *prev;

  int j;


  //scan for S[j]^a

    while(header!=NULL){
        if(header->tag == a){
            break;
        }
        if(header->tag > a){
          header = addNode(prev,a);
          break;
        }

        prev = header;
        header = header->next;
    }

    if(header == NULL){
        header = addNode(prev,a);
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


    //copy label S[j-1]^a + v[j]

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
    ItemLabels *prev;

    //scan for S[j]^a
    while(header!=NULL){
        if(header->tag == a){
            break;
        }

        if(header->tag > a){
          header = addNode(prev,a);
          break;
        }
        prev = header;
        header = header->next;
    }

    if(header == NULL){
       header = addNode(prev,a);
    }

    //scan for S[j-1]^a

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

    // Copy labels in S[j-1]^a to S[j]

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
    ItemLabels *prev;

    //scan for S[j]^a

    while(header!=NULL){
        if(header->tag == a){
            break;
        }
        if(header->tag > a){
          header = addNode(prev,a);
          break;
        }

        prev = header;
        header = header->next;
    }

    if(header == NULL){
       header = addNode(prev,a);
    }

    //scan for S[j-1]^a

    while(sndHeader!=NULL){
        if(sndHeader->tag == a){
            break;
        }
        sndHeader = sndHeader->next;
    }

    //scan for S[j-1]^(a-wj)

    while(toadd!=NULL){
        if(toadd->tag == wj){
            break;
        }
        toadd = toadd->next;
    }

    //compare labels between S[j-1]^a e S[j-1]^a-wj + v[j] to add to S[j]

    header = compareLabels(header,sndHeader,toadd,_v,size);

  return S;

}


ItemLabels * compareLabels(ItemLabels *_result, ItemLabels *Sj_1, ItemLabels *Sj_aw, int * _v, int size){

    ItemLabels *result = _result;

    int *v = _v;

    Label *start1 = Sj_1->label;
    Label *start2 = Sj_aw->label;

    int res;

    Label *head = result->label;


    while(1) {

        //if both labels are null, there's nothing to add to S[j]

        if (start1 == NULL && start2 == NULL){
            break;
        }

        //S[j-1]^a-wj is empty, so scan in S[j-1]^a for the remaining labels to add to S[j]
        // if they are non dominated

        else if (start2 == NULL) {

            Label *tmp = (struct Label *) malloc(sizeof(struct Label));
            tmp->next = NULL;
            tmp->value = malloc(size * sizeof(int));

            memcpy(tmp->value,start1->value,size*sizeof(int));

            int v_dominated = dominated(tmp->value, head, size);

            if (v_dominated != 1) {

                 if(head == NULL){
                     printf("\nAdding vector to result\n");
                       printVector(tmp->value,2);
                       printf("\n");
                      result->label = tmp;
                      head = result->label;
                  }

                  else{
                      printf("\nAdding vector to result\n");
                       printVector(tmp->value,2);
                       printf("\n");
                      head->next = tmp;
                      head = head->next;
                  }
            }

            else{
                free(tmp);
            }

            //FALTA REMOVER O ELEMENTO

            start1 = start1->next;
        }

        // S[j-1]^a is empty, so scan in S[j-1]^a-wj for the remaining labels add v[j] to them
        // and add to S[j] if they are non dominated

        else if (start1 == NULL) {

            int *sum;
            sum = labelsum(start2->value, v, size);

            Label *tmp = (struct Label *) malloc(sizeof(struct Label));
            tmp->next = NULL;
            tmp->value = malloc(size * sizeof(int));
            memcpy(tmp->value,sum,size*sizeof(int));
            free(sum);


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

            else{
                free(tmp);
            }

            //FALTA REMOVER O ELEMENTO

            start2 = start2->next;
        }

        //Compare label in S[j-1]^a and v[j] + S[j-1]^a-wj, get the lexicographic minimum
        //and if it is non dominated comparing to the last label added to S[j] then add it to S[j]
        //if label came from S[j-1]^a we can advance forward to the next label in S[j-1]^a and compare it
        // to the label in S[j-1]^a-wj. Likewise process for the label inside S[j-1]^a-wj


        else{
            int *sum;
            sum = labelsum(start2->value, v, size);

            res = lexmin(start1->value, sum,size);



            if (res == 1) {
                free(sum);
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
                else{
                    free(tmp);
                }

                start1 = start1->next;

            }

                //FALTA REMOVER O ELEMENTO

            else {
                  Label *tmp = (struct Label *) malloc(sizeof(struct Label));
                  tmp->next = NULL;
                  tmp->value = malloc(size * sizeof(int));

                  memcpy(tmp->value,sum,size*sizeof(int));
                  free(sum);


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

                  else{
                      free(tmp);
                  }

                start2 = start2->next;

                //FALTA REMOVER O ELEMENTO
            }
        }
    }
    return result;
}


//init label in S[1]^0 to {0,...,0}
//init label in S[1]^w1 to {-v1,...,-vr}

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


    ItemLabels *prev;

    while(ptr!=NULL){
        if(ptr->tag == w){
            break;
        }

        else if(ptr->tag > w){
          ptr = addNode(prev,w);
          break;
        }

          prev = ptr;
        ptr = ptr->next;

    }

    if(ptr == NULL){
       ptr = addNode(prev,w);
    }

    Label *new = (struct Label *) malloc(sizeof(struct Label));

    new->value = malloc(size * sizeof(int));
    new->next = NULL;

    int *negativevalue = neg(valor,size);

    memcpy(new->value,negativevalue,size*sizeof(int));
    free(negativevalue);
    ptr->label = new;

    return S;
}



//aux functions


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
    int i;

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
  free(V);
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
      free(V);
      return p;
    }

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



void freeItemLabels(ItemLabels **res, int numberofitems){

  int i;
  for(i=0;i<numberofitems;i++){
    printf("freeing node i: %d \n\n",i);
    freeItemLabel(res[i]);
  }
  free(res);
}

void freeItemLabel(ItemLabels *item){
  ItemLabels *freed = item;
  ItemLabels *prev;
  Label *label;

  while(freed!=NULL){
    label = freed->label;
    printf("With tag: %d\n\n",freed->tag);
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
      printf("With label: ");
      printVector(freed->value,2);
      printf("\n\n");
      free (freed->value);
      prev = freed;
      freed = freed->next;
      free (prev);
    }
}


void freeValue(int **v, int r){
  int i;
  for(i=0;i<r;i++){
    free(v[i]);
  }
  free(v);
}




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


double deg2rad(double deg) {
    return (deg * pi / 180);
}


double rad2deg(double rad) {
    return (rad * 180 / pi);
}



ItemLabels *addNode(ItemLabels *S, int tag){
    ItemLabels *tmp = (struct ItemLabels *) malloc(sizeof(struct ItemLabels));
    tmp->tag = tag;
    tmp->label = NULL;
    tmp->next = S->next;
    S->next  = tmp;
    return tmp;
}




int inBoundary(NoFlyZone *nf, Point *p){
    if(p == NULL || nf == NULL){
        return 0;
    }

    int x = p->xCoords;
    int y = p->yCoords;

    if(x>=(nf->xBoundaries[0]) && x<=(nf->xBoundaries[1]) && y >= (nf->yBoundaries[0]) && y <= (nf->yBoundaries[1])){
        return 1;
    }

    return 0 ;
}



int segmentCollision(LineSegment *ls, Circle *circle){
    double cx = circle->xCenter;
    double cy = circle->YCenter;

    double dx = ls->X[1]-ls->X[0];
    double dy = ls->Y[1]-ls->Y[0];

    A = dx * dx + dy * dy;
    B = 2 * (dx * (ls->X[0]-cx) + dy * (ls->Y[0]-cy));
    C = (ls->X[0] - cx) * (ls->X[0] - cx) + (ls->Y[0] - cy) * (ls->Y[0] - cy) - (circle->radius * circle->radius);
    double det = B * B - 4 * A * C;

    if(A<=EPS || det < 0){
        return 0;
    }

    else{
        return 1;
    }
}


double max(double a, double b){
    if(a>=b){
        return a;
    }

    else{
        return b;
    }
}


double min(double a, double b){
    if(a<=b){
        return a;
    }
    else{
        return b;
    }
}

double time(double distance, double speed) {             //speed in kts, distance in km
    double time = distance * 3600 / (speed * 1.852);
    return time;
}


double shortestDistance(Point *point, LineSegment *ls){
    double A = point->xCoords - ls->X[0];
    double B = point->YCoords - ls->Y[0];
    double C = ls->X[1] - ls->X[0];
    double D = ls->Y[1] - ls->Y[0];

    double dot = A * C + B*D;
    double len_sq = C*C + D*D;
    double param = -1;
    if(len_sq != 0){
        param = dot / len_sq;
    }

    double xx, yy;

    if(param < 0){
        xx = ls->X[0];
        yy = ls->Y[0];
    }
    else if(param > 1){
        xx = ls->X[1];
        yy = ls->Y[1];
    }

    else{
        xx = ls->X[0] + param * C;
        yy = y1 + param*D;
    }

    double dx = x - xx;
    double dy = y - yy;

    double result = sqrt(dx * dx + dy * dy);

    return result;
}


double turntime(int currentHeading, int futureHeading, double speed, int maxBankAngle){
    double rateofturn = (1,091 * tan(maxBankAngle))/speed;

    int turnangle;
    int diff;

    if(currentHeading>futureHeading){
        diff = currentHeading - futureHeading;
    }
    else{
        diff = futureHeading - currentHeading;
    }

    if(diff < 180){
        turnangle = abs(currentHeading-futureHeading);
    }

    else{
        if(currentHeading > futureHeading){
            turnangle = (360-currentHeading) + futureHeading;
        }
        else{
            turnangle = (360 -futureHeading) + currentHeading;
        }
    }

    double time = turnangle / rateofturn;

    return time;
    
}


