#include "headers/readfile.h"




char* readFile(HANDLE fileHandle){
    IO_STATUS_BLOCK ioStatusBlock;
    char* buffer = (char*)malloc(MAX_PATH);
    if(!buffer){
        perror("Failed Memory Allocating The Buffer\n");
        return NULL;
    }
    char secondaryBuffer[MAX_PATH];
    LARGE_INTEGER byteOffset = { 0 };
    NTSTATUS status = NtReadFile(fileHandle, 
                                NULL, 
                                NULL, 
                                NULL, 
                                &ioStatusBlock , 
                                &secondaryBuffer, 
                                MAX_PATH, 
                                &byteOffset, 
                                NULL);
    if(!NT_SUCCESS(status)){
        wprintf(L"NtReadFile Failed With NTSTATUS 0x%X\n", status);
        return NULL;
    }
    strcpy(buffer, secondaryBuffer);
    return buffer;
}