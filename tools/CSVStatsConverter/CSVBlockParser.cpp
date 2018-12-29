#include "CSVBlockParser.h"

#include <iostream>
#include <fstream>
#include <string>
#include <pugixml.hpp>
#include "Parts.h"

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
    /**
     * Parsing sequence for a single file. Everything that the parser needs
     * is declared inside the function. Not managing the memory because 
     * this isn't running for long so who cares (might get to it one day).
     */
    
    char line[256]; // Value for the current line being parsed
    std::ifstream csv(csvPath); // Data stream source
    
    if(csv.is_open() == false)
    {
        return NULL;
    }

	currentState = START;
    
    // This is the result list.
    auto* listOfParts = new ArrayList<PartsList*>();
    
    // Current part list (csv block) being parsed.
    PartsList* currentPartList;
    
    // Table header values, this decides the order of the values and where the 
    // values go in the MechBasePart structure.
    auto* headerColumn = new ArrayList<char*>();
    
    while(true)
    {
        switch(currentState)
        {
            case START:
            {
                // Nothing to do in the START state, just to to next state.
                currentState = FIND_TABLE_START;
                break;
            }
            case FIND_TABLE_START:
            {
                /**
                 * This state scanes line by line to find a table title. In 
                 * this format, a table title is a line of text describing
                 * the parts, ex : "Memory Models (Health Brand)". It is 
                 * detected by a line with no commas.
                 */
                
                csv.getline(line, 256);
                
                // Each time we read a line, we need to check if we read in the 
                // EOF byte. If we did, we hit the end of the file and must not
                // keep reading lines from the stream.
                if(csv.eof())
                {
                    // If we're scanning for a new table and we get an EOF,
                    // there must have been some newlines at the end. 
                    
                    // Check if we have some items in the result list, if we
                    // have elements in the list that means the file must have
                    // been correct, go to end state and return gracefully.
                    // If the list is empty and we hit EOF, file must be bad.
                    // Return NULL to indicate any error and print some 
                    // error message.
                    
                    if(listOfParts->Count() > 0)
                    {
                        currentState = END;
                        
                        break;
                    }
                    else
                    {
                        std::printf("Reached End Of File without any results.");
                        csv.close();
                        return NULL;
                    }
                    
                    break;
                }
                
                // Skip blank lines
                if(is_newline(line))
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
                    // If we find a line with commas before hitting a table 
                    // title, the file is malformed.
                    std::printf("Malformed block");
                    csv.close();
                    return NULL;
                }
                
                break;
            }
            case READ_TABLE_HEADER:
            {
                /**
                 * This state reads the table headers. The values are put in 
                 * the headerColumn list to be used later for associating the
                 * csv values to a structure variable.
                 */
                
                csv.getline(line, 256);
                
                // strtok destructs the 'line' variable so it becomes unusable
                // after we processed it.
                char* token = strtok(line, ",");
                while(token)
                {
                    char* charCopy = new char[strlen(token)+1];
                    strcpy(charCopy, token);
                    headerColumn->Add(charCopy);
                    
                    token = strtok(NULL, ",");
                }
                
                if(csv.eof())
                {
                    // In this state, it is not okay to receive an EOF
                    std::printf("Unexepected end of file.");
                    csv.close();
                    return NULL;
                }
                
                currentState = READ_TABLE_ELEMENT;
                
                break;
            }
            case READ_TABLE_ELEMENT:
            {
                csv.getline(line, 256);
                
                /**
                 * This state reads a line of the table and sets the values read
                 * into a MechPartBase instance.
                 */
                
                // Check if we hit the end of the table
                if(is_newline(line))
                {
                    currentState = FIND_TABLE_START;
                    
                    break;
                }
                
                // Read each comma separated value and check with the Header to
                // see, given the current index, where the values goes in the
                // structure.
                MechPartBase* mechPart = new MechPartBase();
                
                char* token = strtok(line, ",");
                int tokenColumn = 0;
                while(token)
                {
                    char* charCopy = new char[strlen(token)+1];
                    strcpy(charCopy, token);
                    
                    // This is just checking the header at the current element
                    // index to see what the current column is for.
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
                
                // After we read all the part data, add it to the current list
                currentPartList->parts->Add(mechPart);
                
                if(csv.eof())
                {
                    // In this state, it is okay to hit the end of file.
                    currentState = END;
                    
                    break;
                }
                
                break;
            }
            case END:
            {
                csv.close();

                return listOfParts;
                break;
            }
        }
    }
    
    return NULL;
}


bool is_newline(const char* contents)
{
    if (strcmp(contents, "\r") == 0 || strcmp(contents, "") == 0 || strcmp(contents, "\n") == 0)
    {
        return true;
    }

    return false;
}