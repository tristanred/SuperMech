#pragma once

#include <libtech/arraylist.h>

class PartsList;

class MechPartExporter
{
public:
    MechPartExporter();
    ~MechPartExporter();
    
    void ExportPartsAsXml(ArrayList<PartsList*>* list, const char* outputFile);
    
};