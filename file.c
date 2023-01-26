#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int main(void) {
    FILE *file_ptr;
    char filename[] = "/proc/cpuinfo", buffer[100];

    if ((file_ptr = fopen(filename, "r")) == NULL) {
        printf("Error: Cannot open file '%s' for reading\n", 
            filename);
        exit(0);
    }

    while (feof(file_ptr) == FALSE) {
        fgets(buffer, 100u, file_ptr);
        printf("%s", buffer);
    }
    
    printf("\n");
    fclose(file_ptr);
    return 0;
}