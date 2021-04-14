#define MAX_SIZE 1024*3

typedef struct metadata{
    size_t key;
    struct metadata *left, *right;
    struct metadata *prev, *next;
}metadata;

typedef metadata* heap;
