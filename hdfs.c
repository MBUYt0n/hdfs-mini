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
    int blocks[MAX_BLOCKS];
} fm;

typedef struct BlockMetadata
{
    char *blockID;
    int data_node_ids[MAX_DATA_NODES];
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

void allocateBlock(NameNode *nn, int file_index)
{
    bm newBlock;
    newBlock.blockID = nn->num_blocks++;

    for (int i = 0; i < 3; ++i)
    {
        newBlock.data_node_ids[i] = i % nn->num_data_nodes;
    }

    nn->blocks[file_index] = newBlock;
    nn->files[file_index].blocks[nn->files[file_index].size++] = newBlock.blockID;
}