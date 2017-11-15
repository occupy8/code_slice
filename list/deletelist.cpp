/*
 * 在O(1)时间删除链表节点
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct node_t{
    int val;
    struct node *next;
}node, *list;

void delete_node(list &head, node *target){
    if(NULL == head || target == NULL)
        return head;
    node *p = NULL;

    //head ?
    if(head == target){
        head = head->next;
        free(target);

        return ;
    }

    //tail ?
    if(target->next == NULL){
       p = head;
       while(p->next != target)
          p = p->next;

       p->next = NULL;
       free(target); 
    }

    //middle
    node *tmp = target;
    memcpy(target, target->next, sizeof(node));

    free(tmp);

    return head;
}
