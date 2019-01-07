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
    
    dummy->Health = 1;
    dummy->Attack = 1;
    dummy->Defense = 1;
    dummy->Speed = 1;
    dummy->Special = 1;
    
    return dummy;
}
