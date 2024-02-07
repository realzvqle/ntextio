#include "headers/writefile.h"
#include "headers/createFile.h"


IO_STATUS_BLOCK writeFile(HANDLE fileHandle, char* content, BOOL isRewrite){
    char buffer[MAX_PATH];
    IO_STATUS_BLOCK ioStatusBlock;
    LARGE_INTEGER byteOffset = { 0 };
    if (!isRewrite) {
        FILE_STANDARD_INFORMATION fileInfo;
        NTSTATUS queryStatus = NtQueryInformationFile(fileHandle, &ioStatusBlock, &fileInfo, sizeof(fileInfo), FileStandardInformation);

        if (NT_SUCCESS(queryStatus)) {
            byteOffset.QuadPart = fileInfo.EndOfFile.QuadPart;
        } else {
            wprintf(L"NtQueryInformationFile Failed With NTSTATUS 0x%X\n", queryStatus);
            return ioStatusBlock;
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
            HANDLE file = createFile("file.txt");
            if(!file){
                return ioStatusBlock;
            }
            status = NtWriteFile(file, 
                                NULL, 
                                NULL, 
                                NULL, 
                                &ioStatusBlock , 
                                content, 
                                strlen(content), 
                                &byteOffset, 
                                NULL);
            if(!NT_SUCCESS(status)){
                wprintf(L"NtWriteFile Failed With NTSTATUS 0x%X\n", status);
                return ioStatusBlock;
            }
        }
        wprintf(L"NtWriteFile Failed With NTSTATUS 0x%X\n", status);
        return ioStatusBlock;
    }
    return ioStatusBlock;
}