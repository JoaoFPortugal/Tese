//
// Created by francisco on 03/11/20.
//


/*
 * original

5.0 10.0 20000
0
7.0 1.0 20000
1
0 2.0 5.5 3.0
0 3.0 1.5 2

 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Waypoint{
    double latitude;
    double longitude;
    double altitude;
    double distance_to_startingpoint;

}Waypoint;


typedef struct LineSegment{
    double X[2];
    double Y[2];
    double Z[2];
}LineSegment;



typedef struct Restriction{
    int type;
    struct Sphere *sphere;
    struct Restriction *next;

}Restriction;

typedef struct Sphere{
    double radius;
    double xCenter;
    double yCenter;
    double zCenter;

}Sphere;


int restrictionSphereCollision(LineSegment *ls, Sphere *sphere){

    double R = 6371;

    double xA = R * cos(ls->X[0]) * cos(ls->Y[0]);
    double yA = R * cos(ls->X[0]) * sin(ls->Y[0]);
    double zA = (R+ ls->Z[0] * 0.0003048) * sin(ls->X[0]);

    double xB = R * cos(ls->X[1]) * cos(ls->Y[1]);
    double yB = R * cos(ls->X[1]) * sin(ls->Y[1]);
    double zB = (R+ ls->Z[1] * 0.0003048) * sin(ls->X[1]);

    double xC = R * cos(sphere->xCenter) * cos(sphere->yCenter);
    double yC = R * cos(sphere->xCenter) * sin(sphere->yCenter);
    double zC = (R + sphere->zCenter * 0.0003048) * sin(sphere->xCenter);


    double NA = sqrt(pow(xA,2) + pow(yA,2) + pow(zA,2));
    double NB = sqrt(pow(xB,2) + pow(yB,2) + pow(zB,2));


    double crossproductX = yA*zB - zA * yB;
    double crossproductY = zA*xB - xA*zB;
    double crossproductZ = xA*yB - yA*xB;


    double normalX = crossproductX / (NA*NB);
    double normalY = crossproductY / (NA*NB);
    double normalZ = crossproductZ / (NA*NB);

    double distance = normalX * xC + normalY * yC + normalZ * zC;

    printf("distance is %f\n", distance);
    if(distance > sphere->radius){
        return 0;
    }

    return 1;
}



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

            if(res == NULL){
                res = malloc(sizeof(struct Restriction));
                res->type = 0;
                res->sphere =  malloc(sizeof(struct Sphere));
                scanf("%lf %lf %lf %lf",&res->sphere->xCenter,&res->sphere->yCenter,&res->sphere->zCenter,&res->sphere->radius);
                res->next = NULL;
            }
            else{

                Restriction *tmp = malloc(sizeof(struct Restriction));
                tmp->type = 0;
                tmp->sphere = malloc(sizeof(struct Sphere));
                scanf("%lf %lf %lf %lf",&tmp->sphere->xCenter,&tmp->sphere->yCenter,&tmp->sphere->zCenter,&tmp->sphere->radius);
                res->next = tmp;
                res = res->next;
            }
        }
        i++;
    }

    printf("I reach here\n");

    LineSegment *segment = malloc(sizeof(struct LineSegment));

    segment->X[0] = start->latitude;
    segment->X[1] = destination->latitude;

    segment->Y[0] = start->longitude;
    segment->Y[1] = destination->longitude;

    segment->Z[0] = start->altitude;
    segment->Z[1] = destination->altitude;
    int result = restrictionSphereCollision(segment,res->sphere);

    printf("res is %d\n", result);
    free(start);
    free(destination);
}