#include <list>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

struct BinaryTreeNode
{
    char value;
    BinaryTreeNode *left;
    BinaryTreeNode *right;
};

void CreatBinaryTree(BinaryTreeNode **pRoot){
    char data;
    cin>>data;

    if(data != '.'){
        *pRoot = new BinaryTreeNode;
        (*pRoot)->value = data;
        CreatBinaryTree(&((*pRoot)->left));   //创建左子树
        CreatBinaryTree(&((*pRoot)->left));
    }
    else *pRoot = NULL;
}

char GetLastCommonNode(list<BinaryTreeNode*> &path1, list<BinaryTreeNode *> &path2){
    list<BinaryTreeNode *>::iterator ite1 = path1.begin();
    list<BinaryTreeNode *>::iterator ite2 = path2.begin();

    BinaryTreeNode *pLast;
    while(ite1 != path1.end() && ite2 != path2.end()){
        if(*ite1 == *ite2)
            pLast=*ite1;
        ite1++;
        ite2++;
    }

    return pLast->value;
}

bool GetNodePath(BinaryTreeNode *pRoot, char pNode, list<BinaryTreeNode *> &path)
{
    bool found = false;
    path.push_back(pRoot);
    if(pRoot->value == pNode)
        return true;
    if(!found && pRoot->left != NULL){
        found = GetNodePath(pRoot->left, pNode, path);
    }
    if(!found && pRoot->right != NULL)
    {
        found = GetNodePath(pRoot->right, pNode, path);
    }

    if(!found)
        path.pop_back();

    return found;
}

void print(list<BinaryTreeNode* > &path)
{
    list<BinaryTreeNode* >::iterator ite;
    for(ite=path.begin(); ite != path.end(); ++ite)
        cout<<(*ite)->value<<' ';
    cout<<endl;
}

int GetLenBetweenNodes( BTreeNode_t *pRoot, BTreeNode_t *pNode1, BTreeNode_t *pNode2){
	if( pRoot == NULL || pNode1 == NULL || pNode2 == NULL )
		return 0;
	if( pNode1 == pNode2 )
		return 0;

	vector<BTreeNode_t *>  vec1;
	vector<BTreeNode_t *>  vec2;
	stack<BTreeNode_t *>  st;

	bool findNod1 = false;
	bool findNod2 = false;
	int len = 0;

	while( !st.empty() || pRoot != NULL  ){//前序遍历，找到从根节点到给定节点的路径
		while( pRoot != NULL ){
			if( findNod1 == false){
				vec1.push_back( pRoot);
				if( pRoot == pNode1)
					findNod1 = true;
			}
			if( findNod2 == false){//没有找到完整路径，就增加节点
				vec2.push_back( pRoot);
				if( pRoot == pNode2 )
					findNod2 = true;
			}

			if( findNod1 && findNod2 )//都已找到，退出查找
				break;

			st.push(pRoot);
			pRoot = pRoot->m_pLeft;
		}

		if( !st.empty() ){
			pRoot = st.top();
			st.pop();
			pRoot = pRoot->m_pRight;
			if( findNod1 == false)//路径错误，则删除节点
				vec1.pop_back();
			if( findNod2 == false)
				vec2.pop_back();
		}

		if( findNod1 && findNod2 )//都已找到，退出查找
			break;
	}

	if( findNod1 && findNod2){
		vector <BTreeNode_t *> :: iterator  iter1 = vec1.begin();
		vector< BTreeNode_t *> :: iterator iter2 = vec2.begin();
		BTreeNode_t *lastCommonParent = NULL;
		int commonSize = 0;
		while( iter1 != vec1.end() && iter2 != vec2.end() ){//同时从根节点开始，遍历两个路径，找到最低祖先节点，并记录从根节点到最低祖先节点的长度
			if( *iter1 == *iter2 ){
				lastCommonParent = *iter1;
				++commonSize;
			}
			else
				break;
		}

		len = vec1.size() + vec2.size() - 2*commonSIze;//两个路径长度-两个共同长度，就是最终距离
	}

	vec1.clear();
	vec2.clear();
	st.clear();

	return len;
}

int main(void)
{
    BinaryTreeNode* pRoot;
    CreatBinaryTree(&pRoot);
    list<BinaryTreeNode *> path1, path2, path3;
    cout<<"please input node char:"<<endl;
    char s1, s2;
    cin>>s1>>s2;
    GetNodePath(pRoot, s1, path1);
    GetNodePath(pRoot, s2, path2);

    char common = GetLastCommonNode(path1, path2);
    GetNodePath(pRoot, common, path3);
    print(path1);
    print(path2);
    print(path3);
    int distance = path1.size()+path2.size()-2*path3.size();
    cout<<s1<<" with "<<s2<<" distance is:" <<distance<<endl;

    return 0;
}
