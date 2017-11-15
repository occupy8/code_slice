/*
 * 归并排序的非递归实现
 */
void merge(int arr[], int low, int mid, int high)
{
    if(arr == NULL || low >= high)
        return;

    int len = high - low + 1;
    int *ptmp = (int *)malloc(len * sizeof(int));
    if(ptmp == NULL)
       return;
    int i0 = low;
    int i1 = mid;
    
    int j0 = mid+1
    int j1 = high;
    
    int t = 0;
    while(i0 < i1 && j0 < j1){
        while(i0 < i1 && arr[i0] < arr[j0])
           ptmp[t++] = arr[i0++]; 
        while(j0 < j1 && arr[j0] < arr[i0])
            ptmp[t++] = arr[j0--];
    } 

    while(i0 < i1)
        ptmp[t++] = arr[i0++];
    while(j0 < j1)
        ptmp[t++] = arr[j0++];

    t = 0;
    for(i0 = low; i0 <= high; i0++)
        arr[i0] = ptmp[t++];

    free(ptmp);
}

int main(void){
    int arr1[] = {1, 2, 3, 8, 9, 5, 6, 10,11 };
    int len = sizeof(arr1)/sizeof(int);

    merge(arr1, 0, 4, len-1);

    int i;
    for(i = 0; i < len; i++){
        printf("%d ", arr1[i]);
    }
    printf("\n");
}
