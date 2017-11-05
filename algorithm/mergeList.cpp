
/*
 * merge list 
 * sorted list
 *
 */

node *merge(node *h1, node *h2){
    node *head = NULL;
    if(!h1)return h2;
    if(!h2)return h1;

    node *phead = head;
    node *cur = NULL;//调整的节点
    node *next = NULL;//调整节点的下一个节点
    while(h1 && h2){
        if(h1->data < h2->data)
        {
            if(!phead)
                phead = h1;
            else{
                phead->next = h1;
                phead = phead->next;
            }

            h1 = h1->next;
        }
        else
        {
            if(!phead)
                phead = h2;
            else{
                phead->next = h2;
                phead = phead->next;
            }
            h2 = h2->next;
        }
    }

    if(h1)
        phead->next = h1;
    if(h2)
        phead->next = h2;

    return head;
}
