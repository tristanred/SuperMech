#pragma once

#include <libtech/arraylist.h>

class MechPartBase;
class BattleAbility;

/**
 * MechFrames are the class that holds the information about a mech in the
 * player's team. Mechs of different types have different names and are build
 * differently so they have different constrains. Each mech is a collection
 * of parts and it is the parts that gives the mechs it's stats points. Mechs
 * also have battle abilities that can be chosen during a battle.
 *
 */
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

    ArrayList<BattleAbility*>* MechAbilities;

    MechFrame();
    ~MechFrame();

    void RecalculateStatsTotals();
    void ResetHealth();
};

MechFrame* CreateDummy();
