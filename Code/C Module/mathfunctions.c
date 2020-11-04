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



double fuelconsumption(Waypoint *a, Waypoint *b, Airplane *plane){
    double dist = distance(a->latitude,a->longitude,b->latitude,b->longitude,'K');

    double dz = fabs(a->altitude-b->altitude);
    double finaldist = sqrt(pow(dist,2)+pow(dz,2));
    double time = finaldist / (plane->speed*1.852);
    double fuelconsump = plane->consumptionRate;
    return time*fuelconsump;
}



double deg2rad(double deg) {
    return (deg * pi / 180);
}


double rad2deg(double rad) {
    return (rad * 180 / pi);
}

double distance(double lat1, double lon1, double lat2, double lon2, char unit) {

    double theta, dist;
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



double distanceinRads(double latitudeA, double longitudeA, double latitudeB, double longitudeB){
    double R = 6371000;
    double d = acos(sin(latitudeA)*sin(latitudeB) + cos(latitudeA)*cos(latitudeB)*cos(longitudeB-longitudeA))*R;
    return d;
}


double bear(double latitudeA, double longitudeA, double latitudeB, double longitudeB){
    double b = atan2(sin(longitudeB-longitudeA)*cos(latitudeB),cos(latitudeA)*sin(latitudeB) - sin(latitudeA)*cos(latitudeB)*cos(longitudeB-longitudeA));
    return b;
}


int inBoundary(NoFlyZone *nf, Waypoint *p){
    if(p == NULL || nf == NULL){
        return 0;
    }

    double x = p->latitude;
    double y = p->longitude;

    if(x>=(nf->xBoundaries[0]) && x<=(nf->xBoundaries[1]) && y >= (nf->yBoundaries[0]) && y <= (nf->yBoundaries[1])){
        return 1;
    }

    return 0 ;
}


//Ponto 1 = A = X[0] Y[0] Z[0]

//Ponto 2 = B = X[1] Y[1] Z[1]

//Ponto 3 = C = circleX circleY


int restrictionSphereCollision(LineSegment *ls, Sphere *sphere){

    double R = 6371;

    double xA = (R+ ls->Z[0] * 0.0003048) * cos(deg2rad(ls->X[0])) * cos(deg2rad(ls->Y[0]));
    double yA = (R+ ls->Z[0] * 0.0003048)  * cos(deg2rad(ls->X[0])) * sin(deg2rad(ls->Y[0]));
    double zA = (R+ ls->Z[0] * 0.0003048) * sin(deg2rad(ls->X[0]));

    double xB = (R + ls->Z[1] * 0.0003048)  * cos(deg2rad(ls->X[1])) * cos(deg2rad(ls->Y[1]));
    double yB = (R + ls->Z[1] * 0.0003048)  * cos(deg2rad(ls->X[1])) * sin(deg2rad(ls->Y[1]));
    double zB = (R + ls->Z[1] * 0.0003048) * sin(deg2rad(ls->X[1]));

    double xC = (R + sphere->zCenter * 0.0003048) * cos(deg2rad(sphere->xCenter)) * cos(deg2rad(sphere->yCenter));
    double yC = (R + sphere->zCenter * 0.0003048) * cos(deg2rad(sphere->xCenter)) * sin(deg2rad(sphere->yCenter));
    double zC = (R + sphere->zCenter * 0.0003048) * sin(deg2rad(sphere->xCenter));


    double NA = sqrt(pow(xA,2) + pow(yA,2) + pow(zA,2));
    double NB = sqrt(pow(xB,2) + pow(yB,2) + pow(zB,2));


    double crossproductX = yA*zB - zA * yB;
    double crossproductY = zA*xB - xA*zB;
    double crossproductZ = xA*yB - yA*xB;


    double normalX = crossproductX / (NA*NB);
    double normalY = crossproductY / (NA*NB);
    double normalZ = crossproductZ / (NA*NB);

    double distance = normalX * xC + normalY * yC + normalZ * zC;

    if(fabs(distance) > sphere->radius){
        return 0;
    }

    return 1;
    return 1;
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


double distancePointToSegment(Waypoint *point, LineSegment *ls){
    double R = 6371;

    double lat1 = deg2rad(ls->X[0]);
    double lat2 = deg2rad(ls->X[1]);
    double lat3 = deg2rad(point->latitude);
    double lon1 = deg2rad(ls->Y[0]);
    double lon2 = deg2rad(ls->Y[1]);
    double lon3 = deg2rad(point->longitude);


    double bear12 = bear(lat1,lon1,lat2,lon2);
    double bear13 = bear(lat1,lon1,lat3,lon3);

    double dis13 = distanceinRads(lat1,lon1,lat3,lon3);
    double diff = fabs(bear13-bear12);

    double result;


    if(diff > M_PI){
        diff = 2*pi - diff;
    }
    if(diff>(M_PI_2)){
        result = dis13;
    }
    else{
        double dxt = asin(sin(dis13/R)*sin(bear13-bear12))*R;
        double dis12 = distanceinRads(lat1,lon1,lat2,lon2);
        double dis14 = acos(cos(dis13/R) / cos(dxt/R)) * R;
        if(dis14/dis12){
            result = distanceinRads(lat2,lon2,lat3,lon3);
        }
        else{
            result = fabs(dxt);
        }
    }

    double dz = fabs(ls->Z[0]-ls->Z[1]);
    double finalresult;

    if(dz < EPS){

        double ddz = fabs(ls->Z[0]-point->altitude);
        finalresult = sqrt(pow(result,2)+pow(ddz*0.0003048,2));

    }
    else{
        double ddz = max(ls->Z[1],ls->Z[0]) + dz;
        finalresult = sqrt(pow(result,2)+pow(ddz*0.0003048,2));

    }
    return finalresult;

}



double turntime(int currentHeading, int futureHeading, double speed, int maxBankAngle){
    double rateofturn = (1.091 * tan(maxBankAngle))/speed;

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