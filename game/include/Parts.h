#pragma once

// Howe much HP is worth 1 stat point. This is so we have greater amounts of HP
#define HP_POINT_MULTIPLIER 5

/**
 * A part is what gives a mech its stats.
 */
class MechPartBase
{
public:
    MechPartBase();
    ~MechPartBase();

    char* Name;
    char* BrandName;
    char* Manifacturer; // TODO : Ref to object
    char* DescriptionText;
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
