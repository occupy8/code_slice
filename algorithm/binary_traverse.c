/*
   binary tree traverse 
   front middle after method
*/

struct node_tree{
	int val;
	struct node_tree *left;
	struct node_tree *right;
};

void preorder(struct node_tree *root, vector<int> &path){
	if(root){
		path.push_back(root->val);
		preorder(root->left, path);
		preorder(root->right, path);
	}
}

void inorder(struct node_tree *root, vector<int> &path){
	if(root){
		inorder(root->left, path);
		path.push_back(root->val);
		inorder(root->right, path);
	}
}

void postorder(struct node_tree *root, vector<int> &path){
	if(root){
		postorder(root->left, path);
		postorder(root->right, path);
		vector.push_back(root->val);
	}
}

//unrecursion

void unrecursion_traveral(struct node_tree *root, vector<int> &path){
	if(NULL == root)
		return ;
	stack<struct node_tree *> s;
        struct node_tree *p = NULL;
	
	s.push(root);
	while(!s.empty()){
		p = s.top();
		s.pop();
		if(p == NULL)
			continue;
		else{
			path.push_back(p->val);
			s.push(p->right);
			s.push(p->left);
		}		
	}

	return ;
}
