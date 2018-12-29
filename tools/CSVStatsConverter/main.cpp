#include "CSVBlockParser.h"

int main(int argc, char** argv)
{
    CSVBlockParser parser("/Users/tristan/Desktop/Memory.csv");
    
    auto x = parser.GetResults();

    return 0;
}
