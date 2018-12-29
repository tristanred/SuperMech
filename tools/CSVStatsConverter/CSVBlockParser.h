#pragma once

#include <libtech/arraylist.h>

class MechPartBase;

enum ParserState
{
    START,
    FIND_TABLE_START,
    READ_TABLE_HEADER,
    READ_TABLE_ELEMENT,
    END
};

class PartsList
{
public:
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

bool is_newline(const char* contents);