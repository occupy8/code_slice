/*
 * 中序遍历
 */
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct tree_node{
    int val;
    struct tree_node *left;
    struct tree_node *right;
};


void inorder_recursive(tree_node *root, vector<int> &v){
    if(root){
        inorder_recursive(root->left, v);
        v.push_back(root->val); 
        inorder_recursive(root->right, v);
    }
}

void inorder_nonrecursive(tree_node *root, vector<int> &v){
    stack<tree_node *> s;
    tree_node *p = root;

    while(!s.empty() || p){
	while(p){
		s.push(p);
		p = p->left;
	}

	if(!s.empty()){
		p = s.top();
		s.pop();
		v.push_back(p->val);

		p = p->right;
	}
    }
}

int main(void){
    tree_node *root = new tree_node;
    root->val = 1;
    root->left = new tree_node;
    root->right = new tree_node;

    root->left->val = 2;
    root->right->val = 3;

    root->right->right = new tree_node;
    root->right->right->val = 4;

    vector<int> v;
    inorder_nonrecursive(root, v);

    int i;
    for(i = 0; i < v.size(); i++){
        cout<<v[i]<<" ";
    }

    cout<<endl;
}
