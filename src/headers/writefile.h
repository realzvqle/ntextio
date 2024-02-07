#pragma once

#include "ntfunc.h"
#include "consoleIO.h"


IO_STATUS_BLOCK writeFile(HANDLE fileHandle, char* content, BOOL isRewrite);
NTSTATUS NtWaitForSingleObject(HANDLE Handle, BOOLEAN Alertable, PLARGE_INTEGER Timeout);