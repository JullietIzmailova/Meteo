#include "config.h"

int Current_Screen = MODE_METEO;

void Set_Current_Screen(int new_mode)
{
    Current_Screen = new_mode;
}

int Get_Current_Screen()
{
    return Current_Screen;
}