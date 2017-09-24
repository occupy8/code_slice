#include <stdio.h>
#include <stdlib.h>

/*
 *    -------------------------------
 *    归并排序测试
 *    -------------------------------
 */
//将两个有序数列合并a[first...mid][mid...last]合并
int mergeArray(int a[], int first, int mid, int last, int temp[]){
    int i,j,k;

    j = mid+1;
    i = first;
    k = 0;

    while(i <= mid && j <= last){
        if(a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    
    while(i <= mid){
        temp[k++] = a[i++];
    }

    while(j <= last){
        temp[k++] = a[j++];
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
        mergeSort(a, mid+1, last, temp);     //右边有序
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
