//二叉查找树

typedef struct Node
{
    int key;
    Node* left;
    Node* right;
    Node* parent;
} *BSTree;

int bst_Insert(BSTree &T, int k, Node* parent=NULL){
    if(T == NULL){
        T = (BSTree)malloc(sizeof(Node));
        T->key = k;
        T->left = NULL;
        T->right = NULL;
        T->parent = parent;
        return 1;
    }
    else if(k == T->key)
        return 0;
    else if(k < T->key)
        return BST_Insert(T->left, k, T);
    else
        return BST_Insert(T->right, k, T);
}

void Create_BST(BSTree &T, int arr[], int n)
{
    T = NULL;
    for(int i = 0; i < n; i++)
        BST_Insert(T, arr[i]);
}

/**
 * 
 */
int BST_Insert_nonRecur(BSTree &T, int k)
{
    Node *pre = NULL;
    node *t = T;

    //find the position
    while(t != NULL)
    {
        pre = t;
        if(k < t->key)
            t = t->left;
        else if(k > t->key)
            t = t->right;
        else
            return 0;
    }

    //insert 
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = k;
    node->left = NULL;
    node->right = NULL;
    node->parent = pre;

    if(pre == NULL)
        T = node;
    else
    {
        if(k < pre->key)
            pre->left = node;
        else
            pre->right = node;
    }

    return 1;
}

Node *BST_search_NonRecur(BSTree T, int k){
    while(T != NULL && k != T->key){
        if(k < T->key)
            T = T->left;
        else
            T = T->right;
    }

    return T;
}

Node* BST_Minimum(BSTree T){
    while(T->left != NULL)
        T = T->left;

    return T;
}

Node* BST_Maximum(BSTree T){
    while(T->right != NULL)
        T = T->right;

    return T;
}

//中序遍历，后继
Node *BST_Successor(Node *node){
    if(node->right != NULL)
        return BST_Minimum(node->right);
    Node*p = node->parent;
    while(p != NULL && p->right == node)
    {
        node = p;
        p = p->parent;
    }

    return p;

}

Node *BST_Predecessor(Node *node){
    if(node->left != NULL)
        return BST_Maximum(node->left);
    Node*p = node->parent;
    while(p!=NULL && p->left == node){
        node = p;
        p = p->parent;
    }

    return p;
}

void BST_Delete(BSTree &T, Node* z){
    if(z->left == NULL && z->right == NULL){
        if(z->parent != NULL){
            if(z->parent->left == z)
                z->parent->left = NULL;
            else
                z->parent->right = NULL;
        }
        else
            T = NULL;
    }
    else if(z->left != NULL && z->right == NULL){
        z->left->parent = z->parent;

        if(z->parent != NULL){
            if(z->parent->left == z)
                z->parent->left = z->left;
            else
                z->parent->right = z->left;
        }
        else
        {
            T = z->left;
        }

        free(z);
    }
    else if(z->left == NULL && z->right != NULL){

    }
    else{
        Node *s = BST_Successor(z);
        z->key = s->key;     //s的关键字替换z的关键字
        BST_Delete(T, s);    //转换为第一或第二种情况
    }
}
