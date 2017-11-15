#include <iostream>
#include <vector>

using namespace std;

struct tree_node{
    int val;
    struct tree_node *left;
    struct tree_node *right;
};

void preorder_traversal(tree_node *root, vector<int> &v){
    if(NULL == root)
        return ;

    v.push_back(root->val); 
    preorder_traversal(root->left, v);
    preorder_traversal(root->right, v);
}

int main(void){
    tree_node *root = new tree_node;
    root->val = 3;
    root->left = new tree_node;
    root->right = new tree_node;

    root->left->val = 2;
    root->right->val = 4;

    vector<int > result;
    preorder_traversal(root);

    for(int i = 0; i < result.size(); i++)
        cout<<result[i]<<" ";

    cout<<endl;
    //delete

    return 0;
}
