/*
 * 归并排序的非递归实现
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void merge(int *arr, int low, int mid, int high)
{
    if(arr == NULL || low >= high)
        return;

    int len = high - low + 1;
    int *ptmp = (int *)malloc(len * sizeof(int));
    if(ptmp == NULL)
       return;

    int i = low;
    int j = mid+1;
    int t = 0;

    while(i <= mid && j <= high){
        if(arr[i] < arr[j])
           ptmp[t++] = arr[i++]; 
        else
           ptmp[t++] = arr[j++];
    } 

    while(i <= mid)
        ptmp[t++] = arr[i++];

    while(j <= high)
        ptmp[t++] = arr[j++];

    for(i = 0; i < t; i++)
        arr[low+i] = ptmp[i];

    free(ptmp);
}

//将a中相邻长度为s的子序列两两合并
void merge_pass(int *arr, int s, int len){
	if(NULL == arr || s >= len)
		return;
	int i = 0;
	int j;

	while(i < len - 2*s +1){
		int mid = i+s-1;
		int high = i+2*s-1;
		merge(arr, i, mid, high);
		i += 2*s;
	}

	if(i < len - s + 1)
		merge(arr, i, i+s-1, len);
}

void merge_sort(int *arr, int len){
	int k = 1;
	while(k <= len){
		merge_pass(arr, k, len);
		k *= 2;
	}
}

int main(void){
    int arr1[10] = {1, 2, 3, 8, 9, 5, 6, 10,11 };
    int len = 9;

    //merge(arr1, 0, 4, len-1);
    merge_sort(arr1, len-1);

    int i;
    for(i = 0; i < len; i++){
        printf("%d ", arr1[i]);
    }
    printf("\n");
}
