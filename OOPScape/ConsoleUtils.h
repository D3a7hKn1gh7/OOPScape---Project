#pragma once
#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <iostream>
#include <windows.h>

// Enables ANSI escape code support in the Windows console.
inline void enableAnsiColors()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

// ANSI color codes for console output.
namespace Color
{
    inline const char* Green = "\033[32m";
    inline const char* Cyan = "\033[96m";
    inline const char* Red = "\033[31m";
    inline const char* Yellow = "\033[33m";
    inline const char* Reset = "\033[0m";
}

#endif