#include <iostream>
#include <windows.h>
#include "Utils.h"

int main()
{
    activateVirtualTerminal();
    std::cout << "Hello world!" << std::endl;
    std::cout << color("woww", Color::GREEN);
    return 0;
}
