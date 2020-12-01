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


float fuelconsumption(Waypoint *a, Waypoint *b, Airplane *plane);
float deg2rad(float deg);
float rad2deg(float rad);
float distance(float lat1, float lon1, float lat2, float lon2, char unit);
int inBoundary(NoFlyZone *nf, Waypoint *p);
int restrictionSphereCollision(LineSegment *ls, Sphere *circle);
float max(float a, float b);
float min(float a, float b);
float time(float distance, float speed);
float distancePointToSegment(Waypoint *point, LineSegment *ls);
float turntime(int currentHeading, int futureHeading, float speed, int maxBankAngle);
int changeAltitudeFeasibility(Waypoint *a, Waypoint *b, float speed, float maximumrate);

#endif //C_MODULE_MATHFUNCTIONS_H
