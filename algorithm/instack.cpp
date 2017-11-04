#include <stdio.h>
#include <stdlib.h>

/*
 * 实现stack
 * 能返回stack中最小的数，且复杂度为O(1)
 *
 *
 */

struct min_stack_element{
    int data;
    int min;
};

struct min_stack{
    min_stack_element *data;
    int size;
    int top;
};

min_stack min_stack_init(int max_size){
    struct min_stack stack;

    stack.data = malloc(max_size*sizeof(struct min_stack_element));
    if(stack.data)
        memset(stack.data, 0, max_size*sizeof(struct min_stack_element));
    stack.size = max_size;
    stack.top = 0;

    return stack;
}

void min_stack_push(min_stack &stack, int data){
    if(stack.top >= stack.size)
        return;

    min_stack_element *element = &stack.data[stack.top++];
    element->data = data;
    element->min = stack.top == 1? data : stack.data[stack.top-2].min; 
    if(element->min > data)
        element->min = data;
}

int min_stack_pop(min_stack &stack, int &out){
    if(stack.top == 0)
        return -1;
    out = stack.data[stack.top].data;
    stack.top--; 

    return 0;
}

int min_stack_min(min_stack stack){
    if(stack.top == 0)
        return -1;

    return stack.data[stack.top-1].min;
}
