//
// Created by francisco on 25/10/20.
//

#ifndef C_MODULE_STRUCTS_H
#define C_MODULE_STRUCTS_H





typedef struct Items{
    int a;
    int j;
    int lastitem;
    struct Label *label;
}Items;


typedef struct Label{
    double *value;
    int *lastitem;
    
    struct Label *next;
}Label;

typedef struct PossibleSolution {

    double *v;
    int size;
    int *indexarray;
    struct PossibleSolution *next;

}PossibleSolution;


typedef struct NoFlyZone{
    double xBoundaries[2];
    double yBoundaries[2];
}NoFlyZone;


typedef struct LineSegment{
    double X[2];
    double Y[2];
    double Z[2];
}LineSegment;

typedef struct Sphere{
    double radius;
    double xCenter;
    double yCenter;
    double zCenter;

}Sphere;


typedef struct Equation{
    int *v;
}Equation;


typedef struct Waypoint{
    double latitude;
    double longitude;
    double altitude;
    double distance_to_startingpoint;

}Waypoint;


typedef struct Restriction{
    int type;
    Equation *equation;
    Sphere *sphere;
    NoFlyZone *noFlyZone;
    struct Restriction *next;

}Restriction;


typedef struct Airplane{
    double weight;
    double fuelQuantity;
    double consumptionRate;
    int speed;
}Airplane;


typedef struct SecondObjective{
    double *objetivevalue;
    struct SecondObjective *next;

}SecondObjective;




#endif //C_MODULE_STRUCTS_H
