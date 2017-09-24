#include <stdio.h>
#include <stdlib.h>

/*
 *    -------------------------------
 *    归并排序测试
 *    -------------------------------
 */
//temp version
int MemeryArray(int a[], int n, int b[], int m, int c[], int k)
{
    if(NULL == a || NULL == b || NULL == c){
        return -1;
    }

    if(n+m > k)
        return -1;

    //接下来哪个小放哪个
    int i, j, o;

    i = j = o = 0;
    while(i < n && j < m){
        if(a[i] < b[j])
            c[o++] = a[i++];
        else
            c[o++] = b[j++];
    } 

    while(i < n){
        c[o++] = a[i++];
    }

    while(j < m){
        c[o++] = b[j++];
    }

    return 0;
}

//将两个有序数列合并a[first...mid][mid...last]合并
int mergeArray(int a[], int first, int mid, int last, int temp[]){
    int i,j,k;

    j = mid+1;
    i = k = 0;

    while(i <= mid && j <= last){
        if(a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    
    while(i <= mid){
        temp[k++] = a[i++];
    }

    while(j <= last){
        temp[k++] = a[i++];
    }

    //back to a[]
    for(i = 0; i < k; i++)
        a[first+i] = temp[i];
    
    return 0;
}

void mergeSort(int a[], int first, int last, int temp[]){
    if(first < last){
        int mid = (first + last)/2;
        mergeSort(a, first, mid, temp);    //左边有序
        mergeSort(a, mid, last, temp);     //右边有序
        mergeArray(a, first, mid, last, temp);    //合并
    }
}

int main(void)
{
    int a[] = {0, 8, 3, 5};
    int temp[6];

    int len = sizeof(a)/sizeof(int);

    mergeSort(a, 0, len-1, temp);

    int i;
    for(i = 0; i < len; i++){
        printf("%d ", a[i]);
    }

    printf("\n");

    return 0;
}
