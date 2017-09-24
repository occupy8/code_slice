#include <stdio.h>
#include <stdlib.h>

/**
 * 堆排序算法
 */
// new node, father node is (i-1)/2
void MinHeapFixup(int a[], int i){
	int j, temp;
	
	temp = a[i];
	j = (i -1)/2;
	while(j >= 0 && i != 0){
		if(a[j] <= temp)
			break;
		
		a[i] = a[j];
		i = j;
		j = (i - 1)/2;
	}

	a[i] = temp;
}

//insert num
void MinHeapAddNumber(int a[], int n, int nNum){
	a[n] = nNum;
	minHeapFixup(a, n);
}

//from i, n:total of num, from 0 to i
void MinHeapFixdown(int a[], int i, int n){
	int j, temp;
	temp = a[i];
	j = 2*i+1;

	while(j < n){
		if(j+1 < n && a[j+1] < a[j])
			j++;
		if(a[j] >= temp)
			break;
		
		a[i] = a[j];
		i = j;
		j = 2*i+1;
	}

	a[i] = temp;
}

//del num
void MinHeapDeleteNumber(int a[], int n){
	swap(a[0], a[n-1]);
	MinHeapFixdown(a, 0, n-1);
}

//create min heap
void MakeMinHeap(int a[], int n){
	for(int i = n/2-1; i>= 0; i--)
		MinHeapFixdown(a, i, n);
}

void minHeapSort(int a[], int n){
	for(int i = n-1; i >= 1; i--){
		swap(a[i], a[0]);
		MinHeapFixdown(a, 0, i);
	}
}

int main(void){

    int a[] = {1, 9, 4, 2, 10, 5};
    int len = sizeof(a)/sizeof(a[0]);

    minHeapSort(a, len);

    for(int i = 0; i < len; i++){
       printf("%d ", a[i]); 
    }

    printf("\n");

    return 0;
}
