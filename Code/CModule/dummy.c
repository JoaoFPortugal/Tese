//
// Created by Jo�o Portugal on 07/05/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#define True 1
#define False 0

typedef struct LineSegment{
    float X[2];
    float Y[2];
    float Z[2];
}LineSegment;

typedef struct Sphere{
    float radius;
    float xCenter;
    float yCenter;
    float zCenter;

}Sphere;

float deg2rad(float deg) {
    return (deg * M_PI / 180);
}


float rad2deg(float rad) {
    return (rad * 180 / M_PI);
}


int restrictionSphereCollision(LineSegment *ls, Sphere *sphere){

    float R = 6371;

    float xA = (R+ (ls->Z[0] * 0.0003048)) * cos(deg2rad(ls->X[0])) * cos(deg2rad(ls->Y[0]));
    float yA = (R+ (ls->Z[0] * 0.0003048))  * cos(deg2rad(ls->X[0])) * sin(deg2rad(ls->Y[0]));
    float zA = (R+ (ls->Z[0] * 0.0003048)) * sin(deg2rad(ls->X[0]));


    float xB = (R + (ls->Z[1] * 0.0003048))  * cos(deg2rad(ls->X[1])) * cos(deg2rad(ls->Y[1]));
    float yB = (R + (ls->Z[1] * 0.0003048))  * cos(deg2rad(ls->X[1])) * sin(deg2rad(ls->Y[1]));
    float zB = (R + (ls->Z[1] * 0.0003048)) * sin(deg2rad(ls->X[1]));



    float xC = (R + (sphere->zCenter * 0.0003048)) * cos(deg2rad(sphere->xCenter)) * cos(deg2rad(sphere->yCenter));
    float yC = (R + (sphere->zCenter * 0.0003048)) * cos(deg2rad(sphere->xCenter)) * sin(deg2rad(sphere->yCenter));
    float zC = (R + (sphere->zCenter * 0.0003048)) * sin(deg2rad(sphere->xCenter));



    float crossproductX = yA*zB - zA * yB;
    float crossproductY = zA*xB - xA*zB;
    float crossproductZ = xA*yB - yA*xB;

    float N = sqrt(pow(crossproductX,2) + pow(crossproductY,2) + pow(crossproductZ,2));


    float normalX = crossproductX / N;
    float normalY = crossproductY / N;
    float normalZ = crossproductZ / N;



    float distance = normalX * xC + normalY * yC + normalZ * zC;

    printf("%f %f %f",normalX,normalY,normalZ);
    printf("Distance is %f\n",distance);

    if(fabs(distance) > sphere->radius){
        return 0;
    }

    return 1;
}


int main(int argc, char ** argv){

    LineSegment *ls = malloc(sizeof(LineSegment));
    Sphere *sphere = malloc(sizeof(Sphere));

    ls->X[0] = 0.5;
    ls->X[1] = 3;
    ls->Y[0] = 3;
    ls->Y[1] = 3;
    ls->Z[0] = 9;
    ls->Z[1] = 9;

    sphere->xCenter = 90;
    sphere->yCenter = 130;
    sphere->zCenter = 0;
    sphere->radius = 5;

    restrictionSphereCollision(ls,sphere);
    return 1;

}


