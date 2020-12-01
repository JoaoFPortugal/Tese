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
    float *value;
    struct Label *next;
}Label;

typedef struct PossibleSolution {

    float *v;
    int size;
    int *indexarray;
    struct PossibleSolution *next;

}PossibleSolution;


typedef struct NoFlyZone{
    float xBoundaries[2];
    float yBoundaries[2];
}NoFlyZone;


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


typedef struct Equation{
    int *v;
}Equation;


typedef struct Waypoint{
    float latitude;
    float longitude;
    float altitude;
    float distance_to_startingpoint;

}Waypoint;


typedef struct Restriction{
    int type;
    Equation *equation;
    Sphere *sphere;
    NoFlyZone *noFlyZone;
    float maximumVRate;
    struct Restriction *next;

}Restriction;


typedef struct Airplane{
    float weight;
    int fuelQuantity;
    float consumptionRate;
    int speed;
}Airplane;


typedef struct SecondObjective{
    float *objetivevalue;
    struct SecondObjective *next;

}SecondObjective;




#endif //C_MODULE_STRUCTS_H
