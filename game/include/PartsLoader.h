#pragma once

#include <libtech/arraylist.h>
#include "Parts.h"

/**
 * Helper class to load parts from config files.
 */
class PartsLoader
{
    /**
     * Save the component part to XML. If the output file already exists the
     * part will be added to the XML parts list.
     */
    static void SavePartToXML(MechPartBase* part, const char* output);

    /**
     *
     */
    static ArrayList<MechPartBase*>* LoadPartsFromXML(const char* inputPath);
};