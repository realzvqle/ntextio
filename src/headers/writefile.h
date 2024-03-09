#pragma once

#include "ntfunc.h"
#include "consoleIO.h"


returnStats writeFile(HANDLE fileHandle, char* content, BOOL isRewrite);
NTSTATUS NtWaitForSingleObject(HANDLE Handle, BOOLEAN Alertable, PLARGE_INTEGER Timeout);