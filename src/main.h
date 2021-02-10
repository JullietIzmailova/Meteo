#include "config.h"

struct TButton
{
    // Button states
    bool Pressed = false;
    bool LastState = false;
    int StateTicker = 0;

    // Button events
    bool EventShortPress = false;
    bool EventLongPress = false;

    // Pointers to Event handlers of buttons.
    // Handler should be out to a separate unit and named: DoShortPress_<UnitName> , DoLongPress_<UnitName>
    //void* DoShortPress;
    //void* DoLongPress;

    void (*DoShortPress)();
    void (*DoLongPress)();
};

extern TButton btn[3] = {};

extern int btnIndex;
extern int Loop_Count = MAIN_LOOP_COUNT_LIMIT;

extern int Screen_Mode = METEO_MODE;
extern int Save_Menu_Selected_Index = 0;


extern int Menu_Selected_Index = 0;


extern String Menu_Items[MENU_ITEMS_SIZE] = { "Item 1", "Item 2", "Item 3" };

