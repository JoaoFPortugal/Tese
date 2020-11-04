//
// Created by francisco on 03/11/20.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Waypoint{
    double latitude;
    double longitude;
    double altitude;
    double distance_to_startingpoint;

}Waypoint;


int main(int argc, char **argv) {

    char var;
    int type;
    double latitude,longitude,altitude;
    double radius;

    scanf("%lf %lf %lf",&latitude,&longitude,&altitude);

    Waypoint *start = malloc(sizeof(struct Waypoint));
    Waypoint *destination = malloc(sizeof(struct Waypoint));

    start->latitude = latitude;
    start->longitude = longitude;
    start->altitude = altitude;

    printf("%f %f %f\n",start->latitude,start->longitude,start->altitude);

    int numberofwaypoints;
    scanf("%d",&numberofwaypoints);
    int i = 0;

    while(i!=numberofwaypoints){
        printf("hello\n");
        i++;
    }

    scanf("%lf %lf %lf\n",&destination->latitude,&destination->longitude,&destination->altitude);

    printf("%f %f %f\n",destination->latitude,destination->longitude,destination->altitude);

    int numberofrestrictions;
    scanf("%d",&numberofrestrictions);


    Restriction *res = NULL;
    i=0;
    while(i!= numberofrestrictions){
        scanf("%d",&type);
        if(type == 0){
            Sphere *sphere = malloc(sizeof(struct Sphere));
            scanf("%lf %lf %lf",sphere->xCenter,sphere->yCenter,sphere->zCenter,sphere->radius);
            if(res == NULL){
                res = malloc(sizeof(struct Restriction));
                res->type = 0;
                res->sphere = sphere;
                res->next = NULL;
            }
            else{
                tmp = malloc(sizeof(struct Restriction));
                tmp->type = 0;
                tmp->sphere = sphere;
                res->next = tmp;
                res = res->next;
            }
        }
        i++;
    }

    free(start);
    free(destination);
}