/**
 * 编程判断两个链表是否相交，假设不带环
 */

struct node {
    int data;
    struct node *next;
};

//if there is no cycle
bool isJoinedSimple(struct node *h1, struct node *h2){
    while(h1->next){
        h1 = h1->next;
    }

    while(h2->next){
        h2 = h2->next;
    }

    return h1 == h2;
}

//if there could exist cycle
node *test_cycle(node *h1){
    node *t1 = NULL;
    node *t2 = NULL;

    t1 = t2 = h1;

    while(t2 != NULL && t2->next != NULL){
        t1 = t1->next;
        t2 = t2->next->next;

        if(t1 == t2)
            return p1;
    }

    return NULL;
}

bool isJoined(node *h1, node *h2){
    //check if exist cycle?
    node *c1 = test_cycle(h1);
    node *c2 = test_cycle(h2);
    
    if(c1 == NULL && c2 == NULL) return isJoinedSimple(h1, h2); 

    if(c1 == NULL && c2 != NULL) return false;
    if(c1 != NULL && c2 == NULL) return false;

    //在环上某一点相交
    node *p = c1;
    while(1){
        if(p == c2 || p->next == c2) return true;
        p = p->next->next;
        c1 = c1->next;

        if(p == c1) return false;
    }
    
    return false;
}
