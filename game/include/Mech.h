#pragma once

#include <libtech/arraylist.h>

class MechPartBase;

class MechFrame
{
public:
    char* Name;
    char* Description;

    // Live Stats
    int CurrentHealth;
    int CurrentExperience;

    // Stat Points
    // Calculated from the total of the parts
    int HealthPoints;
    int AttackPoints;
    int DefensePoints;
    int SpeedPoints;
    int SpecialPoints;

    // Dynamic Stats
    // Stuff like Crit%, dodge,

    int ProcessorSlots;
    ArrayList<MechPartBase*>* Processors;

    int MemorySlots;
    ArrayList<MechPartBase*>* MemoryModules;

    int StorageSlots;
    ArrayList<MechPartBase*>* StorageModules;

    int HeatSinkSlots;
    ArrayList<MechPartBase*>* HeatSinks;

    int BusChipSlots;
    ArrayList<MechPartBase*>* BusChips;

    MechFrame();
    ~MechFrame();

    void RecalculateStatsTotals();
    void ResetHealth();
};

MechFrame* CreateDummy();
