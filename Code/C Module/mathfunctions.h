//
// Created by francisco on 28/10/20.
//

#ifndef C_MODULE_MATHFUNCTIONS_H
#define C_MODULE_MATHFUNCTIONS_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "mathfunctions.h"
#include "auxfunc.h"
#include "auxlabel.h"
#include "structs.h"


double fuelconsumption(Waypoint *a, Waypoint *b, Airplane *plane);
double deg2rad(double deg);
double rad2deg(double rad);
double distance(double lat1, double lon1, double lat2, double lon2, char unit);
int inBoundary(NoFlyZone *nf, Waypoint *p);
int restrictionCircleCollision(LineSegment *ls, Circle *circle);
double max(double a, double b);
double min(double a, double b);
double time(double distance, double speed);
double distancePointToSegment(Waypoint *point, LineSegment *ls);
double turntime(int currentHeading, int futureHeading, double speed, int maxBankAngle);


#endif //C_MODULE_MATHFUNCTIONS_H
