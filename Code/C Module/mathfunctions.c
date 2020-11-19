//
// Created by francisco on 28/10/20.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "mathfunctions.h"
#include "auxfunc.h"
#include "auxlabel.h"
#include "structs.h"



float fuelconsumption(Waypoint *a, Waypoint *b, Airplane *plane){
    float dist = distance(a->latitude,a->longitude,b->latitude,b->longitude,'K');

    float dz = fabs(a->altitude-b->altitude);
    float finaldist = sqrt(pow(dist,2)+pow(dz,2));
    float time = finaldist / (plane->speed*1.852);
    float fuelconsump = plane->consumptionRate;
    return time*fuelconsump;
}



float deg2rad(float deg) {
    return (deg * pi / 180);
}


float rad2deg(float rad) {
    return (rad * 180 / pi);
}

float distance(float lat1, float lon1, float lat2, float lon2, char unit) {

    float theta, dist;
    if ((fabs(lat1-lat2)<EPS) && (fabs(lon1-lon2)<EPS)) {
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



float distanceinRads(float latitudeA, float longitudeA, float latitudeB, float longitudeB){
    float R = 6371000;
    float d = acos(sin(latitudeA)*sin(latitudeB) + cos(latitudeA)*cos(latitudeB)*cos(longitudeB-longitudeA))*R;
    return d;
}


float bear(float latitudeA, float longitudeA, float latitudeB, float longitudeB){
    float b = atan2(sin(longitudeB-longitudeA)*cos(latitudeB),cos(latitudeA)*sin(latitudeB) - sin(latitudeA)*cos(latitudeB)*cos(longitudeB-longitudeA));
    return b;
}


int inBoundary(NoFlyZone *nf, Waypoint *p){
    if(p == NULL || nf == NULL){
        return 0;
    }

    float x = p->latitude;
    float y = p->longitude;

    if(x>=(nf->xBoundaries[0]) && x<=(nf->xBoundaries[1]) && y >= (nf->yBoundaries[0]) && y <= (nf->yBoundaries[1])){
        return 1;
    }

    return 0 ;
}


//Ponto 1 = A = X[0] Y[0] Z[0]

//Ponto 2 = B = X[1] Y[1] Z[1]

//Ponto 3 = C = circleX circleY


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



    //float NA = R + ls->Z[0]*0.0003048
    //float NB = sqrt(pow(xB,2) + pow(yB,2) + pow(zB,2));


    float crossproductX = yA*zB - zA * yB;
    float crossproductY = zA*xB - xA*zB;
    float crossproductZ = xA*yB - yA*xB;

    float N = sqrt(pow(crossproductX,2) + pow(crossproductY,2) + pow(crossproductZ,2));


    float normalX = crossproductX / N;
    float normalY = crossproductY / N;
    float normalZ = crossproductZ / N;



    float distance = normalX * xC + normalY * yC + normalZ * zC;

    if(fabs(distance) > sphere->radius){
        return 0;
    }

    return 1;
}


float max(float a, float b){
    if(a>=b){
        return a;
    }

    else{
        return b;
    }
}


float min(float a, float b){
    if(a<=b){
        return a;
    }
    else{
        return b;
    }
}

float time(float distance, float speed) {             //speed in kts, distance in km
    float time = distance * 3600 / (speed * 1.852);
    return time;
}


float distancePointToSegment(Waypoint *point, LineSegment *ls){
    float R = 6371;

    float lat1 = deg2rad(ls->X[0]);
    float lat2 = deg2rad(ls->X[1]);
    float lat3 = deg2rad(point->latitude);
    float lon1 = deg2rad(ls->Y[0]);
    float lon2 = deg2rad(ls->Y[1]);
    float lon3 = deg2rad(point->longitude);


    float bear12 = bear(lat1,lon1,lat2,lon2);
    float bear13 = bear(lat1,lon1,lat3,lon3);

    float dis13 = distanceinRads(lat1,lon1,lat3,lon3);
    float diff = fabs(bear13-bear12);

    float result;


    if(diff > M_PI){
        diff = 2*pi - diff;
    }
    if(diff>(M_PI_2)){
        result = dis13;
    }
    else{
        float dxt = asin(sin(dis13/R)*sin(bear13-bear12))*R;
        float dis12 = distanceinRads(lat1,lon1,lat2,lon2);
        float dis14 = acos(cos(dis13/R) / cos(dxt/R)) * R;
        if(dis14/dis12){
            result = distanceinRads(lat2,lon2,lat3,lon3);
        }
        else{
            result = fabs(dxt);
        }
    }

    float dz = fabs(ls->Z[0]-ls->Z[1]);
    float finalresult;

    if(dz < EPS){

        float ddz = fabs(ls->Z[0]-point->altitude);
        finalresult = sqrt(pow(result,2)+pow(ddz*0.0003048,2));

    }
    else{
        float ddz = (ls->Z[0]+ls->Z[1])/2;
        finalresult = sqrt(pow(result,2)+pow(ddz*0.0003048,2));
    }
    return finalresult;

}



float turntime(int currentHeading, int futureHeading, float speed, int maxBankAngle){
    float rateofturn = (1.091 * tan(maxBankAngle))/speed;

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

    float time = turnangle / rateofturn;

    return time;

}


int changeAltitudeFeasibility(Waypoint *a, Waypoint *b, float speed, float maximumrate){
    float dist = distance(a->latitude,a->longitude,b->latitude,b->longitude,'K');

    float altdiff = fabs(a->altitude-b->altitude);

    float time = dist / (speed*1.852); //in seconds

    time = time / 60; //in minutes

    float timetochangealt = altdiff / maximumrate; //in minutes

    if(timetochangealt > time){
        return 1;
    }
    return 0;
}