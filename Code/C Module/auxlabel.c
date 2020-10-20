//
// Created by João Portugal on 20/10/2020.
//


#include <math.h>
#include "auxlabel.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "auxfunc.h"


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


