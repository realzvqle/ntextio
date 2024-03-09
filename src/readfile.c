#include "headers/readfile.h"




char* readFile(HANDLE fileHandle, returnStats* stats){
    IO_STATUS_BLOCK ioStatusBlock;
    char* buffer = (char*)malloc(MAX_PATH);
    if(!buffer){
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
        if(stats == NULL) goto SKIP;
        stats->ioStats = ioStatusBlock;
        stats->status = status;
        stats->didFail = TRUE;
        stats->handle = fileHandle;
SKIP:
        return NULL;
    }
    strcpy(buffer, secondaryBuffer);
    if(stats == NULL) goto SECONDSKIP;
    stats->ioStats = ioStatusBlock;
    stats->status = status;
    stats->didFail = FALSE;
    stats->handle = fileHandle;
SECONDSKIP:
    return buffer;
}