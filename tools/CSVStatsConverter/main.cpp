#include "CSVBlockParser.h"
#include "MechPartExporter.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    CSVBlockParser parser("E:/Prog/SuperMech/doc/Memory.csv");
    
    auto x = parser.GetResults();


    if (x == NULL)
    {
        printf("Error : No valid list returned.");

        return 1;
    }

    MechPartExporter exporter;
    exporter.ExportPartsAsXml(x, "output.xml");

    return 0;
}
