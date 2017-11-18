/*
 * 找到从根节点到二叉树任一节点的路径
 */

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct node{
    int data;
    struct node *left;
    struct node *right;
};

enum Tag{
    goLeft,
    goRight,
    goBack
};

void print_path(const vector<node *> & v){
    int i;
    for(i = 0; i < v.size(); i++){
        cout<<v[i]->data<<" ";
    }

    cout<<endl;
}

void print_one_path(node *root, vector<node *> &vec_node, node *target){
      if(NULL == target || NULL == root)
          return;

      if(root == target){
          vec_node.push_back(root);
          return;
      }

      node *cur_node = NULL;
      Tag *cur_tag = NULL;
      vector<Tag *> vec_tag;

      vec_node.push_back(root);  
      vec_tag.push_back(goLeft);

      while(!v.empty()){
        cur_tag = vec_tag.back();
        cur_node = vec_node.back(); 
        if(cur_node == target)
            return;

        switch(*cur_tag){
            case goLeft:
                vec_tag.pop_back();
                vec_tag.push_back(goRight);

                if(cur_node->left){
                    vec_node.push_back(cur_node->left);
                    vec_tag.push_back(goLeft);
                }

                break;
            case goRight:
                vec_tag.pop_back();
                vec_tag.push_back(goBack);

                if(cur_node->right){
                    vec_node.push_back(cur_node->right);
                    vec_tag.push_back(goLeft);
                }

                break;
            case goBack:
                vec_tag.pop_back();
                vec_node.pop_back(); 
                break;
            default:
                break;
        }

      }
}

int main(void){
    node *root = new node;
    root->data = 1;
    root->left = new node;
    root->right = new node;

    root->left->data = 2;
    root->right->data = 3;
    root->right->right = new node;
    root->right->right->data = 4;

    vector<node *> result;

    print_one_path(root, result, root->right->right); 
    print_path(result); 

    return 0;
}
