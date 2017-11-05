/**
 * 求一棵二叉树中相距最远的两个节点之间的距离
 *
 * This is interesting...Also recursively.the longgest distance between two nodes must be either
 * from root to one leaf, or between two leafs.For the former case, it's the tree height.For the
 * latter case, it should be the sum of the heights of left and right subtrees of the two leaves
 * most least ancestor.
 */

int maxDistance(node *root){
    int depth;
    return helper(root, depth);
}

int helper(node *root, int &depth){
    if(root == NULL){
        depth = 0;
        return 0;
    }
    int ld, rd;

    int maxleft = helper(root->left, ld);
    int maxright = helper(root->right, rd);

    depth = max(ld, rd)+1;
    return max(maxleft, max(maxright, ld+rd)); 
}

