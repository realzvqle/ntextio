#include "headers/writefile.h"
#include "headers/createFile.h"


returnStats writeFile(HANDLE fileHandle, char* content, BOOL isRewrite){
    returnStats stats;
    char buffer[MAX_PATH];
    IO_STATUS_BLOCK ioStatusBlock;
    LARGE_INTEGER byteOffset = { 0 };
    if (!isRewrite) {
        FILE_STANDARD_INFORMATION fileInfo;
        NTSTATUS queryStatus = NtQueryInformationFile(fileHandle, &ioStatusBlock, &fileInfo, sizeof(fileInfo), FileStandardInformation);

        if (NT_SUCCESS(queryStatus)) {
            byteOffset.QuadPart = fileInfo.EndOfFile.QuadPart;
        } else {
            stats.didFail = TRUE;
            stats.status = queryStatus;
            stats.ioStats = ioStatusBlock;
            return stats;
        }
    } else {
        byteOffset.QuadPart = 0;
    }
    int j = 0;
    for (int i = 0; i < strlen(content); i++, j++) {
        if (content[i] == '\\' && content[i + 1] == 'n') {
            buffer[j] = '\n';
            putwchar(L'\n'); 
            i++;
        } else {
            buffer[j] = content[i];
        }
    }
    buffer[j] = '\0';
    size_t contentLength = strlen(content);

    NTSTATUS status = NtWriteFile(fileHandle, 
                                NULL, 
                                NULL, 
                                NULL, 
                                &ioStatusBlock , 
                                buffer, 
                                contentLength, 
                                &byteOffset, 
                                NULL);
    if(!NT_SUCCESS(status)){
        if(status == 0xC0000034){
            returnStats file = createFile("file.txt");
            if(!file.handle){
                stats.didFail = TRUE;
                stats.ioStats = ioStatusBlock;
                stats.status = status;
                stats.handle = file.handle;
                return stats;
            }
            status = NtWriteFile(file.handle, 
                                NULL, 
                                NULL, 
                                NULL, 
                                &ioStatusBlock , 
                                content, 
                                strlen(content), 
                                &byteOffset, 
                                NULL);
            if(!NT_SUCCESS(status)){
                stats.didFail = TRUE;
                stats.ioStats = ioStatusBlock;
                stats.status = status;
                stats.handle = file.handle;
                return stats;
            }
        }
        stats.didFail = FALSE;

        stats.ioStats = ioStatusBlock;
        stats.status = status;
        return stats;
    }
    stats.didFail = FALSE;
    stats.ioStats = ioStatusBlock;
    stats.status = status;
    return stats;
}