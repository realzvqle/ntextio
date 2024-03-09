#include "headers/ntextio.h"



int main(int argc, char* argv[]) {
    char* file = ntGet("File: ");
    char* content = ntGet("Content: ");
    returnStats status = createFile(file);
    if(status.didFail){
        ntPrint("createFile Failed with NTSTATUS 0x%x", status.status);
        return 1;
    }
    returnStats writeStatus = writeFile(status.handle, content, TRUE);
    if(status.didFail){
        ntPrint("createFile Failed with NTSTATUS 0x%x", status.status);
        return 1;
    }
    ntPut("Wrote File\n");
}

