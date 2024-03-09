#pragma once
#define _WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <WinUser.h>
#include <winternl.h>
#include <wchar.h>
#include <stdarg.h>
#include <vadefs.h>
#include <tchar.h>
#include <signal.h>




typedef struct _returnStats{
    BOOL didFail;
    NTSTATUS status;
    HANDLE handle;
    IO_STATUS_BLOCK ioStats;
    char failedInfo[4096];
} returnStats;

