#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FileMetadata
{
    char *filename;
    char *path;
    int size;
    __time_t created;
    __time_t modified;
    char *permissions;
} fm;

typedef struct BlockMetadata
{
    char *blockID;
    char **datanode;
    int size;
} bm;

typedef struct DataNodeMetadata
{
    char *ID;
    int port;
    char *hostname;
    int storageAvailable;
} dnm;

