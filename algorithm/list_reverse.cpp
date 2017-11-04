#include <stdlib.h>
#include <stdio.h>

struct node{
    int data;
    node *next;
};

node *reverse_list(node *head){
    node *pre, *cur, *pnext;

    pre = NULL;
    cur = head;
    pnext = head->next;

    while(pnext){
        cur->next = pre;
        pre = cur;
        cur = pnext;
        pnext = pnext->next;
    }

    cur->next = pre;

    return cur;
}
