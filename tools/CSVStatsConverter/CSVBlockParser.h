#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <libtech/arraylist.h>
#include <Parts.h>
#include <pugixml.hpp>

enum ParserState
{
    START,
    FIND_TABLE_START,
    READ_TABLE_HEADER,
    READ_TABLE_ELEMENT,
    END
};

struct PartsList
{
    char* name;
    ArrayList<MechPartBase*>* parts;
};

class CSVBlockParser
{
public:
    ArrayList<PartsList*>* results;
    bool isFinished;
    ParserState currentState;
    
    const char* csvPath;

    CSVBlockParser(const char* filePath);
    ~CSVBlockParser();

    ArrayList<PartsList*>* GetResults();
};
