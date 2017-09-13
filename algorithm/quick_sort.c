#include <stdio.h>
#include <stdlib.h>

void quick_sort(int a[], int l, int r)
{
    int i,j,temp;

    if(l < r){
        i = l;
        j = r;
        temp = a[i];
        while(i < j){
            while(i < j && a[j] > temp)
                j--;
            if(i < j)
                a[i++] = a[j];

            while(i < j && a[i] < temp)
                i++;

            if(i < j)
                a[j--] = a[i];
        }

        a[i] = temp;

        quick_sort(a, l, i-1);
        quick_sort(a, i+1, r);
    }
}

int quick_sort2(int a[], int l, int r){
    int i, j, temp;

    if(l < r){
        i = l;
        j = r;
        temp = a[i];
        while(i < j){
            while(i < j && a[j] >= temp)
                j--;
            if(i < j)
                a[i++] = a[j];
            while(i < j && a[i] <= temp)
                i++;
            if(i < j)
                a[j--] = a[i];
        } 

        a[i] = temp;

        return i;
    }

    return -1;
}

int quick_unrecursion(int a[], int len){
    int stack[128] = {0,};
    int top = -1;
    int mid;
    int i;
    int j;

    stack[++top] = 0;
    stack[++top] = len-1; 

    while(top >= 0){
        j = stack[top--];
        i = stack[top--];

        mid = quick_sort2(a, i, j);

        if(i < mid-1)
        {
            stack[++top] = i;
            stack[++top] = mid-1;
        }
        if(mid+1 < j){
            stack[++top] = mid+1;
            stack[++top] = j;
        }
    }

    return 0; 
}

int main(void)
{
    int arr[] = {4, 2, 5, 1, 9};

    quick_unrecursion(arr, sizeof(arr)/sizeof(int));

    int i;
    for(i = 0; i < sizeof(arr)/sizeof(int); i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
