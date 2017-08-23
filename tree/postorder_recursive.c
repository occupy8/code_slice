void postorder_recursive(Bitree T){
    if(T){
        postorder_recursive(T->lchild);
        postorder_recursive(T->rchild);
    }
}

typedef struct{
    BTNode *ptr;
    enum {0,1,2} mark;
}PMType;

void postorder_nonrecursive(BiTree T){
    PMType a;
    initstack(S);  /* S的元素为PMType类型 */
    push(S, {T,0});    /* 根结点入栈 */
    while(!stackempty(S)){
        pop(S, a);
        switch(a.mark)
        {
            case 0:
                push(S, {a.ptr, 1});
                if(a.ptr->lchild)
                    push(S, {a.ptr->lchild, 0});
                break;
            case 1:
                push(S, {a.ptr,2});
                if(a.ptr->rchild)
                    push(S, {a.ptr->rchild, 0});
                break;
            case 2:
                visit(a.ptr);
        }
    }
}
