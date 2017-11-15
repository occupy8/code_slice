#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct tree_node{
    int val;
    struct tree_node *left;
    struct tree_node *right;
};

void postorder_nonrecursive(tree_node *root, vector<int> &v){
    if(!root)
        return;

    stack<struct tree_node *> s;
    //pcur当前访问节点，plast:上次访问节点
    struct tree_node *pcur = root;
    struct tree_node *plast = NULL;

    //先把当前节点移动到左子树最下边
    while(pcur){
        s.push(pcur);
        pcur = pcur->left;
    }

    while(!s.empty()){
        pcur = s.top();
        s.pop();
        //一个根节点被访问的前提是:无右子树或右子树已经被访问过
        if(pcur->right == NULL || pcur->right == plast){
            v.push_back(pcur->val);
            plast = pur;
            /*
             * else if(pcur->left == plast) //若左子树被访问过，则需先进入右子树（根节点需再次入栈）
             */
        }else{
            //根节点再次入栈
            s.push(pcur);
            pcur = pcur->right;
            while(pcur){
                s.push(pcur);
                pcur = pcur->left;
            }
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
    postorder_nonrecursive(root, result);
    

    for(int i = 0; i < result.size(); i++)
        cout<<result[i]<<" ";

    cout<<endl;
    //delete

    return 0;
}
