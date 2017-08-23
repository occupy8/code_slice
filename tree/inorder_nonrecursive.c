void inorder_recursive(Bitree T){
    if(T){
        inorder_recursive(T->lchild);
        visit(T);
        inorder_recursive(T->rchild);
    }
}

void inorder_nonrecursive(Bitree T){
    initstack(S);     /* 初始化栈*/
    push(S, T);       /* 根指针入栈 */
    while(!stackempty(S)){
        while(gettop(S, p)&& p)  /* 一路向左 */
            push(S, p->lchild);
        pop(S, p); /* 空指针退栈 */
        if(!stackempty(S)){
            pop(S, p);
            visit(p);
            push(S, p->rchild);     /* 向右走一步 */
        }

    }
}
