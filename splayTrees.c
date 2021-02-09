#include "splayTrees.h"

void init(heap *t){
    *t = NULL;
    return ;
}

void insert(heap *t, size_t data){
    metadata *nn = (metadata*)malloc(sizeof(metadata));
    if (!(nn))
        return ;
    nn->key = data;
    nn->left = NULL;
    nn->right = NULL;

    if (*t == NULL){
        *t = nn;
        return ;
    }

    metadata *p = *t;
    metadata *q = NULL;

    while (p){
        q = p;
        if (data < p->key)
            p = p->left;
        else if(data > p->key)
            p = p ->right;
        else{
            free(nn);
            return ;
        }
    }
    if (data < q->key)
        q->left = nn;
    else{
        q->right = nn;
    }
    return ;
}

void preorder(heap t){
    if (t == NULL)
        return ;
    printf("%d ",t->key);
    preorder(t->left);
    preorder(t->right);
    return ;
}

void splay(heap *root, size_t key){

    metadata *t = *root;

    if (!t)
        return NULL;
    
    metadata n = {0};
    metadata *l = &n;
    metadata *r = l;

    metadata *y = NULL;

    while (1){
        if (key < t->key){
            if (t->left == NULL)
                break;
            
            //Rotate Right
            
            if (t->left && key < t->left->key){
                y = t->left;
                t->left = y->right;
                y->right = t;
                t = y;

                if (t->left == NULL)
                    break;
            }

            //LINK right

            r->left = t;
            r = t;
            t = t->left;
            
        }

        else if (key > t->key){
            if (t->right == NULL)
                break;
            
            //Rotate Left

            if (key > t->right->key){
                y = t->right;
                t->right = y->left;
                y->left = t;
                t = y;

                if (t->right == NULL)
                    break;
            }

            //Link Left

            l->right = t;
            l = t;
            t = t->right;

        }

        else{
            break;
        }
    }


    l->right = r->left = NULL;
    l->right = t->left;
    r->left = t->right;
    t->left = n.right;
    t->right = n.left;

    *root = t;  

}
