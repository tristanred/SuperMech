#include "CSVBlockParser.h"
#include "MechPartExporter.h"
#include <libtech/sysutils.h>
#include <libtech/arraylist.h>
#include <libtech/fsutils.h>
#include <libtech/pathutils.h>
#include <stdio.h>

#define TABLE_FORMAT_EXTENSION ".csv"

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        char* inputSearchDirectory = argv[1];

        ArrayList<char*>* filesResult = new ArrayList<char*>();
        get_directory_files(inputSearchDirectory, false, filesResult);

        for (int i = 0; i < filesResult->Count(); i++)
        {
            char* resultPath = filesResult->Get(i);
            
            char filePath[256];
            sanitize_path_slashes(resultPath, filePath);

            char* fileName = get_file_name(filePath);

            char* ext = get_file_extension(filePath);

            if (strcmp(ext, TABLE_FORMAT_EXTENSION) == 0)
            {
                CSVBlockParser parser(filePath);

                auto csvResults = parser.GetResults();

                if (csvResults != NULL)
                {
                    char* fileNameNoExt = get_file_name_noext(filePath);
                    char outputFileName[256];
                    sprintf(outputFileName, "%s.xml", fileNameNoExt);

                    MechPartExporter exporter;
                    exporter.ExportPartsAsXml(csvResults, outputFileName);

                    //delete(fileNameNoExt); // Heap corruption, whyyyy ?
                }

            }

            delete(fileName);
            delete(ext);
        }

        return 0;
    }

    printf("No directory passed in argument.");

    return 1;

}
