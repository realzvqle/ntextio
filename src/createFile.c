#include "headers/createFile.h"
#include <winternl.h>

wchar_t* getDir() {
    TCHAR buffer[MAX_PATH];
    DWORD length = GetCurrentDirectory(MAX_PATH, buffer);

    wchar_t* path = (wchar_t*)malloc((length + 1) * sizeof(wchar_t));  // +1 for null-terminator
    if (!path) {
        return NULL;
    }

    mbstowcs(path, buffer, length);
    path[length] = L'\0';  // Null-terminate the string

    if (path[length - 1] != L'\\') {
        wcscat(path, L"\\");
    }

    return path;
}

// Rest of your code remains unchanged

HANDLE createFile(CHAR* filename) {
    DbgPrint("PCHAR Format, ...");
    WCHAR buffer[MAX_PATH];
    if (filename[1] == ':') {
        swprintf(buffer, sizeof(buffer) / sizeof(buffer[0]), L"\\??\\%hs\0\\", filename);
    }
    else {
        WCHAR* path = getDir(); 
        swprintf(buffer, sizeof(buffer) / sizeof(buffer[0]), L"\\??\\%s%hs\0\\", path, filename);
        free(path);  
    }

    wprintf(L"Path is %ls\n", buffer); 
    UNICODE_STRING objectName;
    RtlInitUnicodeString(&objectName, buffer);
    OBJECT_ATTRIBUTES obj;
    InitializeObjectAttributes(&obj, &objectName, OBJ_CASE_INSENSITIVE, NULL, NULL);

    HANDLE fHandle;
    IO_STATUS_BLOCK ioStatusBlock;

    NTSTATUS createFileStatus = NtCreateFile(
        &fHandle,
        FILE_WRITE_DATA | FILE_READ_DATA | FILE_READ_ATTRIBUTES | FILE_WRITE_ATTRIBUTES,
        &obj,
        &ioStatusBlock,
        NULL,
        FILE_ATTRIBUTE_NORMAL,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        FILE_CREATE,
        FILE_SEQUENTIAL_ONLY,
        NULL,
        0
    );

    if (!NT_SUCCESS(createFileStatus)) {
        wprintf(L"NtCreateFile failed with status 0x%X\n", createFileStatus);
        NtClose(fHandle);
        return NULL;
    }

    return fHandle;
}

HANDLE openFile(CHAR* filename) {
    DbgPrint("PCHAR Format, ...");
    WCHAR buffer[MAX_PATH];
    if (filename[1] == ':') {
        swprintf(buffer, sizeof(buffer) / sizeof(buffer[0]), L"\\??\\%hs\0\\", filename);
    }
    else {
        WCHAR* path = getDir(); 
        swprintf(buffer, sizeof(buffer) / sizeof(buffer[0]), L"\\??\\%s%hs\0\\", path, filename);
        free(path);  
    }

    UNICODE_STRING objectName;
    RtlInitUnicodeString(&objectName, buffer);
    OBJECT_ATTRIBUTES obj;
    InitializeObjectAttributes(&obj, &objectName, OBJ_CASE_INSENSITIVE, NULL, NULL);

    HANDLE fHandle;
    IO_STATUS_BLOCK ioStatusBlock;

    NTSTATUS createFileStatus = NtCreateFile(
        &fHandle,
        FILE_WRITE_DATA | FILE_READ_DATA | FILE_READ_ATTRIBUTES | FILE_WRITE_ATTRIBUTES,
        &obj,
        &ioStatusBlock,
        NULL,
        FILE_ATTRIBUTE_NORMAL,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        FILE_OPEN,
        FILE_SEQUENTIAL_ONLY,
        NULL,
        0
    );

    if (!NT_SUCCESS(createFileStatus)) {
        wprintf(L"NtCreateFile failed with status 0x%X\n", createFileStatus);
        NtClose(fHandle);
        return NULL;
    }

    return fHandle;
}
