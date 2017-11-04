
/*
 * 从树的根结点开始往下访问一直到叶结点所经过的所有结点形成一条路径
 */

struct tree_node{
    int data;
    tree_node *left;
    tree_node *right;
};

//use a stack to help
void helper(tree_node *root, int &sum, int &path[], int &top){
    path[top++] = root.data;
    sum -= root.data;
    if(root->left == NULL && root->right == NULL){
        if(sum == 0) print(path);
    }else{
        if(root->left != NULL) helper(root->left, sum, path, top);
        if(root->right != NULL) helper(root->right, sum, path, top);
    }

    //back to 
    top--;
    sum += root.data;
}

void print_paths(tree_node *root, int sum){
    int path[1024];
    helper(root, num, path, 0);
}
