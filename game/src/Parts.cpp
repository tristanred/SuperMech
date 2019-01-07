#include "Parts.h"

#include <stdlib.h>

MechPartBase::MechPartBase()
{
   Name = new char[64];
   BrandName = new char[64];
   Manifacturer = new char[64];
   DescriptionText = new char[256];
   Generation = 0;

   Health = 0;
   Attack = 0;
   Defense = 0;
   Speed = 0;
   Special = 0;
}

MechPartBase::~MechPartBase()
{
   if (Name != NULL)
       delete(Name);

   if (BrandName != NULL)
       delete(BrandName);

   if (Manifacturer != NULL)
       delete(Manifacturer);

    if(DescriptionText != NULL)
        delete(DescriptionText);
}

int MechPartBase::GetTotalPoints()
{
    return (Health + Attack + Defense + Speed + Special);
}

int MechPartBase::GetAveragePoints()
{
    return (this->GetTotalPoints() / 5);
}
