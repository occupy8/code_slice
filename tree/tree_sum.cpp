/*
 * 输入一棵二叉树和一个整数，打印出二叉树中节点值的和为输入整数的所有路径。从树的跟节点开始往下一直到叶子节点经过的节点形成一条路径
 *
 *
 */

#include <iostream>
#include <stack>

using namespace std;

struct tree_node{
    int val;
    struct tree_node *left;
    struct tree_node *right;
};

void all_path(tree_node *root, vector<int> &v, int &cur_sum, int expect_sum){
    if(root == NULL)
        return;

    v.push_back(root->val);
    cur_sum += root->val;
    //当前路径和大于等于指定值，且不是叶子节点
    if(cur_sum >= expect_sum && (root->left || root->right))
    {
        v.pop_back();
        cur_sum -= root->val;
    }

    //输出条件
    if(cur_sum == expect_sum && root->left == NULL && root->right == NULL){
        for(int i = 0; i < v.size(); i++)
            cout<<v[i]<<" ";
        cout<<endl;
    } 

    //from left
    if(root->left)
       all_path(root->left, v, cur_sum, expect_sum);

    //from right
    if(root->right)
       all_path(root->right, v, cur_sum, expect_sum); 
}

//非递归前序遍历
void pre_order(struct tree_node *root){
    stack<struct tree_node *> s;
    struct tree_node *p = root;

    while(p != NULL || !s.empty()){
        while(p != NULL)
        {
            cout<<p->val<<" ";
            s.push(p);
            p = p->left;
        }        

        if(!s.empty()){
            p = s.top();
            s.pop();
            p = p->right;
        }
    }
}

int main(void){
    struct tree_node *root = calloc(sizeof(struct tree_node), 1);
    root->val = 1;
    struct tree_node *left = calloc(sizeof(struct tree_node), 1);
    left->val = 2;
    struct tree_node *right = calloc(sizeof(struct tree_node), 1);
    right->val = 3;
    struct tree_node *leaf = calloc(sizeof(struct tree_node), 1);
    leaf->val = 4;

    root->left = left;
    root->right = right;
    left->left = leaf;

    pre_order(root);
}
