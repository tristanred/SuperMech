#pragma once

// Howe much HP is worth 1 stat point. This is so we have greater amounts of HP
#define HP_POINT_MULTIPLIER 5

class MechPartBase
{
public:
    char* Name;
    char* BrandName;
    char* Manifacturer; // TODO : Ref to object
    int Generation;
    
    // Attribute points
    int Health;
    int Attack;
    int Defense;
    int Speed;
    int Special;

    int GetTotalPoints();
    int GetAveragePoints();
};
