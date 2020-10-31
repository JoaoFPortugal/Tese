//
// Created by João Portugal on 20/10/2020.
//

#include "auxlabel.h"
#include "auxfunc.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mathfunctions.h"

Items *initItems(Items *_S, double *valor, int size, Waypoint *start, Waypoint *destination, Airplane *plane){

    Items *S = _S;
    Items *ptr = S;
    int i;
    Label *header;

    header = (struct Label *) malloc(sizeof(struct Label));
    header->next = NULL;
    header->value = malloc(size * sizeof(double));

    for(i=0;i<size;i++){
        header->value[i]=0;
    }

    S->lastitem = -1;

    S->label = header;
    Items *prev;

    int w = round(fuelconsumption(start,destination,plane)*10);


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

    ptr->lastitem = 1;

    Label *new = (struct Label *) malloc(sizeof(struct Label));

    new->value = malloc(size * sizeof(double));
    new->next = NULL;

    valor[1] = fuelconsumption(start,destination,plane);

    double *negativevalue = neg(valor,size);

    memcpy(new->value,negativevalue,size*sizeof(double));
    free(negativevalue);
    ptr->label = new;
    ptr->lastitem = 1;

    return S;
}



Items *addLabels(Items *S, double * _v, Items *S_2, int a, int wj, int size, int j){

    Items *header = S;
    Items *sndHeader = S_2;
    Items *toadd = S_2;
    Items *prev;

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

    header->lastitem = j;


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


Items * compareLabels(Items *_result, Items *Sj_1, Items *Sj_aw, double * _v, int size){

    Items *result = _result;

    double *v = _v;

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
            tmp->value = malloc(size * sizeof(double));

            memcpy(tmp->value,start1->value,size*sizeof(double));

            int v_dominated = dominated(tmp->value, head, size);

            if (v_dominated != 1) {

                if(head == NULL){
                    result->label = tmp;
                    head = result->label;
                }

                else{
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

            double *sum;
            sum = labelsum(start2->value, v, size);

            Label *tmp = (struct Label *) malloc(sizeof(struct Label));
            tmp->next = NULL;
            tmp->value = malloc(size * sizeof(double));
            memcpy(tmp->value,sum,size*sizeof(double));
            free(sum);


            int v_dominated = dominated(tmp->value, head, size);

            if (v_dominated != 1) {

                if(head == NULL){
                    result->label = tmp;
                    head = result->label;
                }

                else{
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
            double *sum;
            sum = labelsum(start2->value, v, size);

            res = lexmin(start1->value, sum,size);



            if (res == 1) {
                free(sum);
                Label *tmp = (struct Label *) malloc(sizeof(struct Label));
                tmp->next = NULL;
                tmp->value = malloc(size * sizeof(double));

                memcpy(tmp->value,start1->value,size*sizeof(double));



                int v_dominated = dominated(tmp->value, head, size);

                if (v_dominated != 1) {

                    if(head == NULL){
                        result->label = tmp;
                        head = result->label;
                    }

                    else{
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
                tmp->value = malloc(size * sizeof(double));

                memcpy(tmp->value,sum,size*sizeof(double));
                free(sum);


                int v_dominated = dominated(tmp->value, head, size);

                if (v_dominated != 1) {

                    if(head == NULL){
                        result->label = tmp;
                        head = result->label;
                    }

                    else{
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




Items* copyItems(Items *_S, Items *S_2,int a, int size){



    Items *S = _S;
    Items *header = S;
    Items *sndHeader = S_2;
    Items *prev;

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



    header->lastitem = sndHeader->lastitem;


    Label *tocopy = sndHeader->label;
    Label *newlabel = header->label;

    // Copy labels in S[j-1]^a to S[j]

        while(tocopy!=NULL){

            Label *tmp = (struct Label *) malloc(sizeof(struct Label));
            tmp->next = NULL;
            tmp->value = malloc(size * sizeof(double));
            memcpy(tmp->value,tocopy->value,size*sizeof(double));

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


Items *sumItems(Items * _S , Items * source, double *v, int a, int a_wj, int size, int jindex){

    Items *S = _S;

    Items * header = S;

    Items * src = source;
    Items *prev;

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

    header->lastitem = jindex;

    //scan for S[j-1]^a-wj

    while(src!=NULL){
        if(src->tag == a_wj){
            break;
        }
        src = src->next;
    }




    Label *origin = src->label;
    Label *result = header -> label;

    //while there are labels in S[j-1]^a-wj sum these to v and add them to S[j]^a


    //copy label S[j-1]^a + v[j]

    while(origin!=NULL){

        Label *tmp = (struct Label *) malloc(sizeof(struct Label));
        tmp->next = NULL;
        tmp->value = malloc(size * sizeof(double));


        for(j=0;j<size;j++){
            tmp->value[j] = (-v[j]) + origin->value[j];
        }



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



Items *addResult(Items **res){

    Items *finalitem = res[6];

    Items *valuestoadd = res[5];

    Label *currentfinalist = NULL;


    while(valuestoadd !=NULL) {

        currentfinalist = iterateLabels(valuestoadd,currentfinalist);
        valuestoadd = valuestoadd ->next;

    }

    finalitem->label = currentfinalist;
    return res[6];
}


Label *iterateLabels(Items *current, Label *_currentFinalList){

    Label *toAdd = current->label;
    Label *currentFinalList = _currentFinalList;


    while(toAdd!=NULL){
          currentFinalList = iterateValues (toAdd,currentFinalList);
          toAdd = toAdd->next;
    }

    return currentFinalList;
}


Label *iterateValues(Label *_newValue, Label *_currentFinalList){

  Label *newList = NULL;
  Label *currentFinalList = _currentFinalList;
  Label *newValue = _newValue;
  Label *head;
  Label *prev = currentFinalList;

  int neverdominated = 1;

  while(currentFinalList != NULL){

    double *negv = neg(newValue->value,2);

    double *negf = neg(currentFinalList->value,2);

    int dominate = dominatedNeg(negf,negv,2);

    free(negf);
    free(negv);

    if(dominate == 0){


        Label *tmp = (struct Label *) malloc(sizeof(struct Label));
        tmp->next = NULL;
        tmp->value = malloc(2 * sizeof(double));
        memcpy(tmp->value,currentFinalList->value,2*sizeof(double));

        if(newList == NULL){
            newList = tmp;
            head = newList;

        }
        else{

            newList->next = tmp;
            newList = newList->next;

        }

    }


    double *v = neg(newValue->value,2);
    double *neggg = neg(currentFinalList->value,2);
    Label *negff = (struct Label *) malloc(sizeof(struct Label));
    negff->next = NULL;
    negff->value = malloc(2 * sizeof(double));
    memcpy(negff->value,neggg,2*sizeof(double));

    dominate = dominated(v,negff,2);

    free(v);
    free(neggg);
    free(negff->value);
    free(negff);

    if(dominate == 1){
      neverdominated = 0;
    }
    currentFinalList = currentFinalList->next;

  }

  if(neverdominated != 0){

        Label *tmp = (struct Label *) malloc(sizeof(struct Label));
        tmp->next = NULL;
        tmp->value = malloc(2 * sizeof(double));
        memcpy(tmp->value,newValue->value,2*sizeof(double));


        if(newList == NULL){
            newList = tmp;
            head=newList;

        }
        else{

            newList->next = tmp;

        }

  }


  freeLabels(prev);



  return head;
}


void findTargetSumSubsets(double *input, double target, double * _ramp, int index, int size,
                              PossibleSolution ** _ps, int originalsize, int * arrayofindexes) {

        double *ramp = _ramp;

        PossibleSolution *ps = * _ps;
        PossibleSolution *head = *_ps;

        if(index > (originalsize - 1)) {


            if(fabs(getSum(ramp,size)-target)<EPS) {

                PossibleSolution *tmp = malloc(sizeof(struct PossibleSolution));
                tmp->v = malloc(size * sizeof(double));
                tmp->indexarray = malloc(originalsize * sizeof(int));
                memcpy(tmp->indexarray,arrayofindexes,originalsize * sizeof(int));
                memcpy(tmp->v,ramp,size*sizeof(double));
                tmp->size = size;
                tmp->next = NULL;


                while(head->next!=NULL){
                  head = head->next;
                }

                head->next = tmp;
            }
            free(_ramp);
            return;
        }

        int newsize = size+1;
        double *newramp =  malloc(newsize * sizeof(double));
        memcpy(newramp,ramp,sizeof(double)*size);
        newramp[newsize-1]=input[index];

        arrayofindexes[index] = 1;
        findTargetSumSubsets(input, target, newramp, index + 1,size+1, &ps,originalsize, arrayofindexes);
        arrayofindexes[index] = 0;
        findTargetSumSubsets(input, target, ramp, index + 1,size,&ps, originalsize,arrayofindexes);

}



int checkRestrictions(Waypoint *newItem, Items *S, int a, Restriction *_list, Waypoint **listofWaypoints, Waypoint *start){
    Items *header = S;
    while(header!=NULL){
        if(header->tag ==a){
            break;
        }
        header = header->next;
    }
    if(header == NULL){
        return -1;
    }

    int lastWaypoint = header->lastitem;
    int flag;
    if(lastWaypoint == -1){
        flag = verifyRestrictions(start,newItem,_list);
    }

    else{
        Waypoint *b = listofWaypoints[lastWaypoint-1];
        flag = verifyRestrictions(b,newItem,_list);
    }

    return flag;

}

int verifyRestrictions(Waypoint *a, Waypoint *b, Restriction *_list){
    int flag = 0;
    Restriction *list = _list;

    while(list!=NULL){
        if(list->type == 0){
            flag = intersectsRestriction(a,b,list);
        }
        else{
            flag = breaksRestriction(a,b,list);
        }

        if(flag == 1){
            return -1;
        }
        list = list->next;
    }

    return 0;
}

int intersectsRestriction(Waypoint *a, Waypoint *b, Restriction *res){
    LineSegment *ls = malloc(sizeof(struct LineSegment));
    ls->X[0] = a->latitude;
    ls->Y[0] = a->longitude;
    ls->X[1] = b->latitude;
    ls->Y[1] = b->longitude;

    Circle *circle = res->cirle;
    int flag = restrictionCircleCollision(ls,circle);
    free(ls);
    return flag;
}


int breaksRestriction(Waypoint *a,Waypoint *b, Restriction *res){
    return 0;
}




SecondObjective *secondobjective(PossibleSolution *ps, int numberofitems,Waypoint **list, Waypoint *start,Airplane *plane){
    int prev = -1;
    SecondObjective *secondObj = NULL;
    SecondObjective *header = NULL;
    Waypoint *prevWaypoint;
    int i;

    while(ps != NULL){

        int *indexarray = ps->indexarray;

        double *arrayofvalues = malloc(sizeof(double)*numberofitems);

        for(i=0;i<numberofitems;i++){
            if(prev == -1){
                prevWaypoint = start;
                prev = 0;
            }

            if(indexarray[i] == 1){
                arrayofvalues[i] = -fuelconsumption(prevWaypoint,list[i],plane);
                prevWaypoint = list[i];
            }
            else{
                arrayofvalues[i] = 0;
            }
        }
        prev = -1;

        if(secondObj == NULL){

            header = malloc(sizeof(struct SecondObjective));
            header->objetivevalue = malloc(sizeof(double)*numberofitems);
            header->next = NULL;
            memcpy(header->objetivevalue,arrayofvalues,sizeof(double)*numberofitems);
            secondObj = header;

        }

        else{

            SecondObjective *tmp = malloc(sizeof(struct SecondObjective));
            tmp->objetivevalue = malloc(sizeof(double)*numberofitems);
            memcpy(tmp->objetivevalue,arrayofvalues,sizeof(double)*numberofitems);
            header->next = tmp;
            header = header->next;
        }

        ps = ps->next;

    }

    return secondObj;
}



