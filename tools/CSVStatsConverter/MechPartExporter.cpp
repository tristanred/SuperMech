#include "MechPartExporter.h"

#include <libtech/fsutils.h>
#include <libtech/pathutils.h>
#include <stdio.h>
#include <pugixml.hpp>
#include "Parts.h"
#include "CSVBlockParser.h"

MechPartExporter::MechPartExporter()
{
}

MechPartExporter::~MechPartExporter()
{
}

/* Output format example

<components type="Processors">
    <brand name="Quality Processors">
        <component name="Model 1" health="5" attack="1" defense="1" special="1" generation="1" />
        <component name="Model 2" health="10" attack="2" defense="2" special="2" generation="2" />
        <component name="Model 3" health="15" attack="3" defense="3" special="3" generation="3" />
    </brand>
</components>
*/

void MechPartExporter::ExportPartsAsXml(ArrayList<PartsList*>* list, const char* outputFile)
{
    pugi::xml_document doc = pugi::xml_document();

    pugi::xml_node componentsRootNode = doc.append_child("components");
    componentsRootNode.append_attribute("type").set_value("unknown");
    
    for (int i = 0; i < list->Count(); i++)
    {
        PartsList* element = list->Get(i);
        
        if (element->name == NULL || element->parts == NULL)
        {
            printf("Error when reading PartList %i, NULL values.", i);
            
            return;
        }

        pugi::xml_node brandNode = componentsRootNode.append_child("brand");
        brandNode.append_attribute("name").set_value(element->name);

        for (int k = 0; k < element->parts->Count(); k++)
        {
            MechPartBase* part = element->parts->Get(k);

            pugi::xml_node partNode = brandNode.append_child("component");
            partNode.append_attribute("name").set_value(part->Name);
            partNode.append_attribute("health").set_value(part->Health);
            partNode.append_attribute("attack").set_value(part->Attack);
            partNode.append_attribute("defense").set_value(part->Defense);
            partNode.append_attribute("special").set_value(part->Special);
            partNode.append_attribute("generation").set_value(part->Generation);
        }
    }

    doc.save_file(outputFile);
}
