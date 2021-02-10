typedef struct metadata{
    size_t key;
    struct metadata *left, *right;
    struct metadata *prev, *next;
}metadata;

typedef metadata* heap;
