#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 把二元查找树转变成排序的双向链表
 */
struct bstree_node{
    int m_value;
    bstree_node *m_left;
    bstree_node *m_right;
};

void helper(bstree_node *&head, bstree_node *&tail, bstree_node *root){
    bstree_node *lt = NULL;
    bstree_node *rh = NULL;

    if(root == NULL){
        head = NULL, tail = NULL;
        return;
    }

    helper(head, lt, root->m_left);
    helper(rh, tail, root->m_right);

    if(lt != NULL){
        lt->m_right = root;
        root->m_left = lt;
    }else{
        head = root;
    }

    if(rh != NULL){
        root->m_right = rh;
        rh->m_left = root;
    }else{
        tail = root;
    }
}

bstree_node *treeToLinkedList(bstree_node *root){
    bstree_node *head, *tail;
    helper(head, tail, root);

    return head;
}



