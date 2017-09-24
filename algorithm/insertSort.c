#include <stdio.h>
#include <stdlib.h>

void print(int a[], int n){
    for(int j = 0; j < n; j++){
        printf("%d ", a[j]);
    }

    printf("\n");
}

void InsertSort(int a[], int n)
{
    for(int i = 1; i<n; i++){
        if(a[i] < a[i-1]){
            int j = i-1;
            int x = a[i]; //temp 

            a[i] = a[i-1];

            while(x < a[j]){
                a[j+1] = a[j];
                j--;
            }
            a[j+1] = x;
        }
    }
}

int main(){
    int a[] = {3,1,5,9,0,3};

    InsertSort(a, sizeof(a)/sizeof(int));

    print(a, sizeof(a)/sizeof(int));

    return 0;
}
