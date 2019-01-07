#pragma once

#include <libtech/arraylist.h>

class MechPartBase;

class MechFrame
{
public:
    char* Name;
    char* Description;
    
    // Stats
    int Health;
    int Attack;
    int Defense;
    int Speed;
    int Special;

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
};

MechFrame* CreateDummy();
