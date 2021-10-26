#include <iostream>
#include <windows.h>
#include "Utils.h"

int main()
{
    activateVirtualTerminal();
    std::cout << "Hello world!" << std::endl;
    std::cout << color("woww", Color::Bright_Blue) << " c'est super" << color(" c'est rouge", Color::Magenta);

    return 0;
}
