
typedef struct node_t{
    int data;
    struct node_t *next;
}node, *List;

node *reverse_list(node *head){
    if(NULL == head || head->next == NULL)
        return head;
    
    node *cur = head;
    node *pre = NULL; 
    node *next = NULL;

    node *tail = NULL;
    while(cur != NULL){
        //如果当前结点不是null， 那么初始化next
        next = cur->next;
        if(NULL == next)
            tail = cur;
        //进行链表的反转，当前结点的next指向前一个结点
        cur->next = pre;
        //勿忘断链的情形，需要使用pre指针保存状态，pre等价于是后移一个结点
        pre = cur;
        //pnow 后移一个结点
        cur = next;
    }

    return tail;
}
