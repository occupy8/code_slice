/*
 * 输入一棵二叉树的根节点，求该树的深度。从根结点到也结点一次经过的结点（含根，叶结点）形成树的一条路径，最长路径的长度为树的深度
 */

#include <iostream>
#include <vector>

using namespace std;

struct node{
    int val;
    struct node *left;
    struct node *right;
};

enum Tag{
    goNULL,
    goLeft,
    goRight,
    goBack
};

int deep_tree(node *root){
    if(NULL == root)
        return 0;
    int deep = 0;
    vector<node *> vec_path;
    vector<Tag> vec_tag;
    Tag cur_tag = goNULL;
    node *cur_node = NULL;

    vec_path.push_back(root);
    vec_tag.push_back(goLeft);
    while(!vec_path.empty()){
        cur_node = vec_path.back();
        cur_tag = vec_tag.back();
        switch(cur_tag){
            case goLeft:
                vec_tag.pop_back();
                vec_tag.push_back(goRight);

                if(cur_node->left){
                    vec_path.push_back(cur_node->left);
                    vec_tag.push_back(goLeft);
                }
                break;
            case goRight:
                vec_tag.pop_back();
                vec_tag.push_back(goBack);
                if(cur_node->right){
                    vec_path.push_back(cur_node->right);
                    vec_tag.push_back(goLeft);
                }
                break;
            case goBack:
                //check leaf node?
                if(cur_node->left == NULL && cur_node->right == NULL){
                    deep = deep < vec_path.size()? vec_path.size() : deep;
                }
                vec_tag.pop_back();
                vec_path.pop_back();
                break;
            default:
                break;
        }
    }

    return deep; 
}

int main(void){
    int deep = 0;

    node *root = new node;
    root->val = 1;
    root->left = new node;
    root->left->val = 2;
    root->right = new node;
    root->right->val = 3;

    root->right->right = new node;
    root->right->right->val = 4;

    deep = deep_tree(root);

    cout<<"deep:"<<deep<<endl;

    return 0;
}
