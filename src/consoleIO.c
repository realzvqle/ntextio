#include "headers/consoleIO.h"
#include <handleapi.h>
#include <winuser.h>


#define BUFFERMAX 4096


void ntPut(PCHAR Format, ...){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    writeFile(hStdout, Format, TRUE);
}

void ntPrint(PCHAR Format, ...){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    char buffer[BUFFERMAX];
    va_list args;
    va_start(args, Format);
    wvsprintfA(buffer, Format, args);
    va_end(args);
    writeFile(hStdout, buffer, TRUE);
}


char* ntGet(char* ask){
    ntPut(ask);
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    char* buffer = readFile(hStdin, NULL);
    return buffer;
}