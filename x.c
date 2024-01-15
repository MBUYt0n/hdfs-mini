#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    FILE *fp = fopen("tt.txt", "r");

    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    int file_descriptor = fileno(fp);
    struct stat file_info;

    if (fstat(file_descriptor, &file_info) == -1)
    {
        perror("Error getting file information");
        fclose(fp);
        return 1;
    }

    printf("File size: %ld bytes\n", file_info.st_size);

    fclose(fp);
    return 0;
}
