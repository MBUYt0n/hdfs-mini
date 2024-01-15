#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BLOCKS 100
#define MAX_DATA_NODES 10

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

typedef struct NameNode
{
    fm files[MAX_BLOCKS];
    bm blocks[MAX_BLOCKS];
    dnm data_nodes[MAX_DATA_NODES];
    int num_files;
    int num_blocks;
    int num_data_nodes;
} NameNode;

typedef struct DataNode
{
    int node_id;
    char data[1024];
} DataNode;

void initialiseNamenode(NameNode *nn)
{
    nn->num_blocks = 0;
    nn->num_data_nodes = 0;
    nn->num_files = 0;
}

void addFile(NameNode *nn, char *filename, char *path)
{
    fm newFile;
    newFile.created = time(NULL);
    newFile.modified = time(NULL);
    strcpy(newFile.filename, filename);
    strcpy(newFile.path, path);
    struct stat file_info;
    int size = lstat(filename, &file_info);
    newFile.size = size;
    nn->files[nn->num_files++] = newFile;
}