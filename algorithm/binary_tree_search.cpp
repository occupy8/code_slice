/**
 * binary tree, from left to right search node 
 */

struct tree_node_t{
	int value;
	struct tree_node_t *left;
	struct tree_node_t *right;
	tree_node_t(int d):value(d),left(NULL),right(NULL){
	
	}	
};

vector<int> print_from_top(struct tree_node_t *root){
	vector<int> result;
	queue<struct tree_node_t *> node_queue;
	struct tree_node_t *ptmp = NULL;

	if(NULL == root)
		return result;
 
	node_queue.push(root);
	while(!node_queue.empty()){
		ptmp = node_queue.front();
		node_queue.pop();

		if(ptmp)
			result.push_back(ptmp->value);
		if(ptmp->left)
			node_queue.push(ptmp->left);
		if(ptmp->right)
			node_queue.push(ptmp->right);
	}

	return result;
}
