void preorder_recursive(Bitree T){
    if(T){
        visit(T);
        preorder_recursive(T->lchild);
        preorder_recursive(T->rchild);
    }
}

void preorder_nonrecursive(Bitree T){
    initstack(S);
    push(S, T);   /* 根指针进栈*/
    while(!stackempty(S)){
        while(gettop(S, p)&&p){  /* 向左走到尽头 */
            visit(p);            /* 每向前走一步都访问当前结点 */
            push(S, p->lchild);
        }
        pop(S, p);
        if(!stackempty(S)){
            pop(S, p);
            push(S, p->rchild);
        }
    }
}
