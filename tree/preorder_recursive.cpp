#include <iostream>
#include <vector>
#include <stack>

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

//非递归
void preorder_norecursion_traversal(tree_node *root, vector<int > &v){
	stack<tree_node *> s;
	tree_node *p = root;
	
	while(p != NULL || !s.empty()){
		while(p != NULL){
			s.push(p);
			v.push_back(p->val);
			
			p = p->left;
		}
		//叶子节点？？
		if(!s.empty()){
			p = s.top();
			s.pop();

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

    vector<int> result;
    //preorder_traversal(root, result);
    preorder_norecursion_traversal(root, result);

    for(int i = 0; i < result.size(); i++)
        cout<<result[i]<<" ";

    cout<<endl;
    //delete

    return 0;
}
