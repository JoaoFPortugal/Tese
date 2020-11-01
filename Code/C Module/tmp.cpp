//
// Created by francisco on 01/11/20.
//

printf("Hello!\n");
printf("Current value of final list is:\n");
printVector(currentFinalList->value,2);
printf("bye!\n");

double *negv = neg(newValue->value,2);

double *negf = neg(currentFinalList->value,2);

int dominate = dominatedNeg(negf,negv,2);

free(negf);
free(negv);

printf("Dominate is %d\n", dominate);

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

printf("neverdominate is %d\n",neverdominated);

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
