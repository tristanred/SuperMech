#include "Mech.h"

#include "Parts.h"
#include <libtech/stdutils.h>

MechFrame::MechFrame()
{
    this->Name = new char[64];
    this->Description = new char[256];

    this->Processors = new ArrayList<MechPartBase*>();
    this->MemoryModules = new ArrayList<MechPartBase*>();
    this->StorageModules = new ArrayList<MechPartBase*>();
    this->HeatSinks = new ArrayList<MechPartBase*>();
    this->BusChips = new ArrayList<MechPartBase*>();

    CurrentHealth = 0;
    CurrentExperience = 0;

    HealthPoints = 0;
    AttackPoints = 0;
    DefensePoints = 0;
    SpeedPoints = 0;
    SpecialPoints = 0;
}

MechFrame::~MechFrame()
{
    delete(this->Name);
    delete(this->Description);

    // Assuming a mech instance owns the parts object
    this->Processors->DeleteElements();
    this->MemoryModules->DeleteElements();
    this->StorageModules->DeleteElements();
    this->HeatSinks->DeleteElements();
    this->BusChips->DeleteElements();

    delete(this->Processors);
    delete(this->MemoryModules);
    delete(this->StorageModules);
    delete(this->HeatSinks);
    delete(this->BusChips);
}

void MechFrame::RecalculateStatsTotals()
{
    HealthPoints = 0;
    AttackPoints = 0;
    DefensePoints = 0;
    SpeedPoints = 0;
    SpecialPoints = 0;

    for(int i = 0; i < Processors->Count(); i++)
    {
        MechPartBase* part = Processors->Get(i);

        this->HealthPoints += part->Health;
        this->AttackPoints += part->Attack;
        this->DefensePoints += part->Defense;
        this->SpeedPoints += part->Speed;
        this->SpecialPoints += part->Special;
    }

    for(int i = 0; i < MemoryModules->Count(); i++)
    {
        MechPartBase* part = MemoryModules->Get(i);

        this->HealthPoints += part->Health;
        this->AttackPoints += part->Attack;
        this->DefensePoints += part->Defense;
        this->SpeedPoints += part->Speed;
        this->SpecialPoints += part->Special;
    }

    for(int i = 0; i < StorageModules->Count(); i++)
    {
        MechPartBase* part = StorageModules->Get(i);

        this->HealthPoints += part->Health;
        this->AttackPoints += part->Attack;
        this->DefensePoints += part->Defense;
        this->SpeedPoints += part->Speed;
        this->SpecialPoints += part->Special;
    }

    for(int i = 0; i < HeatSinks->Count(); i++)
    {
        MechPartBase* part = HeatSinks->Get(i);

        this->HealthPoints += part->Health;
        this->AttackPoints += part->Attack;
        this->DefensePoints += part->Defense;
        this->SpeedPoints += part->Speed;
        this->SpecialPoints += part->Special;
    }

    for(int i = 0; i < BusChips->Count(); i++)
    {
        MechPartBase* part = BusChips->Get(i);

        this->HealthPoints += part->Health;
        this->AttackPoints += part->Attack;
        this->DefensePoints += part->Defense;
        this->SpeedPoints += part->Speed;
        this->SpecialPoints += part->Special;
    }
}

void MechFrame::ResetHealth()
{
    this->CurrentHealth = this->HealthPoints * HP_POINT_MULTIPLIER;
}

MechFrame* CreateDummy()
{
    MechFrame* dummy = new MechFrame();

    strcpy(dummy->Name, "TN-01");
    strcpy(dummy->Description, "Dummy Mech");

    dummy->ProcessorSlots = 1;
    MechPartBase* proc = new MechPartBase();
    strcpy(proc->Name, "BASIC 001");
    strcpy(proc->BrandName, "ProMax");
    strcpy(proc->Manifacturer, "UltraTech");
    strcpy(proc->DescriptionText, "");
    proc->Generation = 1;
    proc->Health = 1;
    proc->Attack = 1;
    proc->Defense = 1;
    proc->Speed = 1;
    proc->Special = 1;
    dummy->Processors->Add(proc);

    dummy->RecalculateStatsTotals();

    return dummy;
}
