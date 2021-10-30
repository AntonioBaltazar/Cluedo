#ifndef CONSOLEHANDLER_H_INCLUDED
#define CONSOLEHANDLER_H_INCLUDED

void activateVirtualTerminal();
void initConsole(std::string title);
void preventScrollBar();
void resizeConsole(std::string title);
void hideCursor(bool showFlag);

#endif // CONSOLEHANDLER_H_INCLUDED
