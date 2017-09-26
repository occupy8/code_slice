#include <iostream>
#include <vector>

using namespace std;

struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;

    TreeNode(){
        left = NULL;
        right = NULL;
    }
};

class Solution{
public:
    vector<int> vec;
    vector<int> preorderTraversal(TreeNode *root){
        if(root == NULL)
            return vec;

        vec.push_back(root->val);

        preorderTraversal(root->left);
        preorderTraversal(root->right);

        return vec;
    }

};


int main(void){
    TreeNode *root = new TreeNode;
    root->val = 3;
    root->left = new TreeNode;
    root->right = new TreeNode;

    root->left->val = 2;
    root->right->val = 4;

    Solution *so = new Solution;
    vector<int > result = so->preorderTraversal(root);

    for(int i = 0; i < result.size(); i++)
        cout<<result[i]<<" ";

    //delete

    return 0;
}
