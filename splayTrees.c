#include "splayTrees.h"



void Splay(heap *root, size_t key){

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
            
            //LL Rotation
            if (t->left && key < t->left->key){
                y = t->left;
                t->left = y->right;
                y->right = t;
                t = y;

                if (t->left == NULL)
                    break;
            }

            //Link right

            r->left = t;
            r = t;
            t = t->left;
        }

        else if (key > t->key){
            if (t->right == NULL)
                break;
            
            //RR Rotation
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
void Insert_Node_to_Heap(heap *t, metadata *tobeInserted){
   
    if (!*t){
        *t = tobeInserted;
        return ;
    }
    
    metadata *p = *t;
    metadata *q = NULL;
    while (p){
        
        q = p;
        if (tobeInserted->key < p->key){
            p = p->left;             
        }
        else if (tobeInserted->key > p->key){
            p = p->right;            
        }
        else {            
            while (p->next){
                p = p->next;
            }
            p->next = tobeInserted;
            p->next->prev = p;
            return ;
        }
        
    }
    if (tobeInserted->key < q->key)
        q->left = tobeInserted;
    if (tobeInserted->key > q->key)
        q->right = tobeInserted;

    Splay(t, tobeInserted->key);        

    return ;


}
metadata* Delete_Node_from_Heap(heap *t){
    if (!(t))
        return;
    metadata *root = *t, *q = NULL;    
    // not found
    if (!(root))
        return ;
    //leaf case
    if (!root->left && !root->right){
        *t = NULL;
        if (root->next){
            *t = root->next;
            root->next->prev = NULL;
            root->next->left = root->left;
            root->next->right = root->right;
            root->next = NULL;
        }
        
        return root;
    }
    //one child

    //left child
    if (root->left && !root->right){
        //p is root
        *t = root->left;
        if (root->next){
            *t = root->next;
            root->next->prev = NULL;
            root->next->left = root->left;
            root->next->right = root->right;
        }
        root->left = root->right = NULL;
        root->next = root->prev = NULL;
        return root;        
    }

    //right child
    if (!root->left && root->right){
        //p is root
        *t = root->right;
        if (root->next){
            *t = root->next;
            root->next->prev = NULL;
            root->next->left = root->left;
            root->next->right = root->right;
        }
        root->left = root->right = NULL;
        root->prev = root->next = NULL;
        
        return root;
      
    }
    int temp;
    //both children
    if (root->left && root->right){
        metadata *r = NULL;//r is parent of s
        metadata *s = NULL;
        // go to p->left and then go to the rightmost node of left subtree
        s = root->left;
        while (s->right){
            r = s;
            s = s->right;
        }
        // s is now the right most node and r is parent of it.
        // make r->right = s->left
        //copy value of s into p

        if (!r){
            //s doesnt have right members.
            if (root->next){
                *t = root->next;
                root->next->left = root->left;
                root->next->right = root->right;
                root->next = root->prev = NULL;
                root->left = root->right = NULL;
                return root;
            }

            if (s->next){
                temp = root->key;
                root->key = s->key;
                s->key = temp;

                root->next = s->next;
                s->next->prev = root;

                s->next = s->prev = NULL;

                root->left = s->left;

                s->left = s->right = NULL;

                return s;

            }

            temp = s->key;
            s->key = root->key;
            root->key = temp;

            root->left = s->left;

            s->left = s->right = NULL;
            s->next = s->prev = NULL;

            return s;
        }

        else{
            if (root->next){
                root->next->left = root->left;
                root->next->right = root->right;

                root->next->prev = NULL;
                root->next = NULL;
                root->left = root->right = NULL;

                return root;
            }

            if (s->next){
                
                root->next = s->next;
                root->next->prev = root;

                temp = root->key;
                root->key = s->key;
                s->key = temp;

                s->next = s->prev = NULL;

                r->right = s->left;

                s->left = s->right = NULL;

                return s;
            }

            temp = root->key;
            root->key = s->key;
            s->key = temp;
            r->right = s->left;

            return s;
        }

    }
}

/************TODEBUG************/

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

void inorder(heap t){
    if (t == NULL)
        return ;
    inorder(t->left);
    printf("%d ",t->key);
    inorder(t->right);
    return;
}

void postorder(heap t){
    if (t == NULL)
        return ;
    postorder(t->left);
    
    postorder(t->right);

    printf("%d ",t->key);
    return;
}