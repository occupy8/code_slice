#include <stdio.h>
#include <stdlib.h>

int binary_search(int attr[], int left, int right, int element){
    int mid;
    while(left <= right){
        mid = (left+right)/2;
        if(attr[mid] > element){ //left
            right = mid-1;
        }else if(attr[mid] < element){    //right
            left = mid+1; 
        }else{
            return mid;
        }
    }

    return -1;
}

int main(void){
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    int left = 0;
    int right = 8;

    int location = binary_search(array, left, right, 1);
    if(location == -1)
        printf("cao, error happened!\n");
    else
        printf("the location position:%d\n", location);

    return 0;
}
