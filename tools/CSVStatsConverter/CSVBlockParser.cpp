#include "CSVBlockParser.h"

CSVBlockParser::CSVBlockParser(const char* filePath)
{
    isFinished = false;
    this->csvPath = filePath;
}

CSVBlockParser::~CSVBlockParser()
{

}

ArrayList<PartsList*>* CSVBlockParser::GetResults()
{
    char line[256];
    std::ifstream csv(csvPath);
    
    if(csv.is_open() == false)
    {
        return NULL;
    }
    
    ArrayList<PartsList*>* listOfParts = new ArrayList<PartsList*>();
    PartsList* currentPartList;
    ArrayList<char*>* headerColumn = new ArrayList<char*>();
    while(true)
    {
        switch(currentState)
        {
            case START:
            {
                currentState = FIND_TABLE_START;
                break;
            }
            case FIND_TABLE_START:
            {
                csv.getline(line, 256);
                
                // Skip blank line
                if(strcmp(line, "\r") == 0)
                {
                    break;
                }
                
                // Lines without commas start a CSV table
                if(strchr(line, ',') == NULL)
                {
                    // Create a new instance of a part list and set the name
                    currentPartList = new PartsList();
                    currentPartList->name = new char[256];
                    currentPartList->parts = new ArrayList<MechPartBase*>();
                    strcpy(currentPartList->name, line);
                    listOfParts->Add(currentPartList);
                    
                    currentState = READ_TABLE_HEADER;
                    
                    break;
                }
                else
                {
                    // Bad state
                    std::printf("Malformed block");
                    
                    return NULL;
                }
                
                break;
            }
            case READ_TABLE_HEADER:
            {
                csv.getline(line, 256);
                char* token = strtok(line, ",");
                while(token)
                {
                    char* charCopy = new char[strlen(token)+1];
                    strcpy(charCopy, token);
                    headerColumn->Add(charCopy);
                    
                    token = strtok(NULL, ",");
                }
                
                currentState = READ_TABLE_ELEMENT;
                
                break;
            }
            case READ_TABLE_ELEMENT:
            {
                csv.getline(line, 256);
                
                if(strcmp(line, "\r") == 0)
                {
                    currentState = FIND_TABLE_START;
                    
                    break;
                }
                
                MechPartBase* mechPart = new MechPartBase();
                
                char* token = strtok(line, ",");
                int tokenColumn = 0;
                while(token)
                {
                    char* charCopy = new char[strlen(token)+1];
                    strcpy(charCopy, token);
                    
                    if(strcmp(headerColumn->Get(tokenColumn), "Name") == 0)
                    {
                        mechPart->Name = charCopy;
                    }
                    else if(strcmp(headerColumn->Get(tokenColumn), "Health") == 0)
                    {
                        mechPart->Health = atoi(charCopy);;
                    }
                    else if(strcmp(headerColumn->Get(tokenColumn), "Attack") == 0)
                    {
                        mechPart->Attack = atoi(charCopy);
                    }
                    else if(strcmp(headerColumn->Get(tokenColumn), "Defense") == 0)
                    {
                        mechPart->Defense = atoi(charCopy);
                    }
                    else if(strcmp(headerColumn->Get(tokenColumn), "Special") == 0)
                    {
                        mechPart->Special = atoi(charCopy);
                    }
                    else if(strcmp(headerColumn->Get(tokenColumn), "Generation") == 0)
                    {
                        mechPart->Generation = atoi(charCopy);
                    }
                    
                    tokenColumn++;
                    token = strtok(NULL, ",");
                }
                
                currentPartList->parts->Add(mechPart);
                
                if(csv.eof())
                {
                    currentState = END;
                    break;
                }
                
                break;
            }
            case END:
            {
                return listOfParts;
                break;
            }
        }
    }
    
    return listOfParts;
}
