#include <iostream>
#include <windows.h>

#include "ConsoleHandler.h"
#include "scenes/Menu.h"

int main()
{
    // Resize console, hide cursor, get title & allow colors
    initConsole("Cluedo - Menu");
    Menu m;
    m.launch();
    return 0;
}
