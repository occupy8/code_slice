#include <stdio.h>
#include <stdlib.h>

/*
 *   1, 2,  3,  4    //1.按顺序遍历4个元素（列数），步长为1
 *   5, 6,  7,  8    //2.步长改为4（列数），遍历2个元素（行数-1）
 *   9, 10, 11, 12   //3.步长改为-1，遍历3个元素（列数-1）
 *                   //4.步长改为-4（负的列数），遍历1个元素（行数-1）
 */
void traverse(const int **arr, int row, int col){
    const int *data = (const int *)arr;
    int i = -1;
    int step = 1;
    int k;

    for(k = 0; k < col;k++){
        i += step; 
        printf("%d,", data[i]);
    }
    step = col;
    for(k = 0; k < row-1; k++){
        i += step;
        printf("%d,", data[i]);
    }
    step = -1;
    for(k = 0; k < col-1; k++){
        i += step;
        printf("%d,", data[i]);
    }
    step = -col;
    for(k = 0; k < row-1; k++){
        i += step;
        printf("%d,", data[i]);
    }
}

int main(void){
    int arr[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};

    traverse(arr, 3, 4);

    return 0;
}
