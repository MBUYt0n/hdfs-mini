// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>

// int main()
// {
//     FILE *fp = fopen("tt.txt", "r");

//     if (fp == NULL)
//     {
//         perror("Error opening file");
//         return 1;
//     }

//     int file_descriptor = fileno(fp);
//     struct stat file_info;

//     if (fstat(file_descriptor, &file_info) == -1)
//     {
//         perror("Error getting file information");
//         fclose(fp);
//         return 1;
//     }

//     printf("File size: %ld bytes\n", file_info.st_size);

//     fclose(fp);
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    const char *filename = "example.txt";
    struct stat file_info;

    if (lstat(filename, &file_info) == -1)
    {
        perror("Error getting file information");
        return 1;
    }

    printf("File size: %ld bytes\n", file_info.st_size);

    // You can access other file information using the members of struct stat

    return 0;
}
