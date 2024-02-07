#include "headers/ntextio.h"




int main(int argc, char* argv[]) {
    char* buffer = ntGet("Whats Your Name: ");
    ntPrint("%s", buffer);
    ntPut(buffer);
    free(buffer);
    return 0;
}
