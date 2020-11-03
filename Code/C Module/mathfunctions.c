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
    double time = dist / plane->speed;
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


int restrictionCircleCollision(LineSegment *ls, Circle *circle){
    double cx = circle->xCenter;
    double cy = circle->YCenter;

    double dx = ls->X[1]-ls->X[0];
    double dy = ls->Y[1]-ls->Y[0];

    double A = dx * dx + dy * dy;
    double B = 2 * (dx * (ls->X[0]-cx) + dy * (ls->Y[0]-cy));
    double C = (ls->X[0] - cx) * (ls->X[0] - cx) + (ls->Y[0] - cy) * (ls->Y[0] - cy) - (circle->radius * circle->radius);
    double det = B * B - 4 * A * C;

    if(A<=EPS || det < 0){
        return 0;
    }

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
    double R = 637100;

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

    return result;
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