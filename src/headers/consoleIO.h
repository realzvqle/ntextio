#pragma once


#include "ntfunc.h"
#include "writefile.h"
#include "readfile.h"



void ntPut(PCHAR Format, ...);
void ntPrint(PCHAR Format, ...);
char* ntGet(char* ask);