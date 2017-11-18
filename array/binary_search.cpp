/*
 * 在一个排好顺序的数组中，查找一个数字出现的次数
 */

#include <iostream>
#include <string.h>

using namespace std;

int find(int arr[], int l, int r, int t)
{
    if(NULL == arr || l >= r)
        return -1; 

    int i = l;
    int j = r;
    int mid;
    while(i < j){
        mid = (i + j)/2;
        if(arr[mid] == t)
            break;
        else if(arr[mid] < t)
            i = mid+1;
        else 
            j = mid-1;
    }

    if(i < j){   //find it!!!
        int num = 1;
        int k = mid;
        while(k >= 0 && arr[k] == t)
        {
            k--;
            num++;
        }

        while(k <= r && arr[k] == t){
            k++;
            num++;
        }
        return num;
    }

    return -1;
}

int find_firstK(int arr[], int l, int r, int t){
    if(NULL == arr || l >= r)
        return -1;
    int i = l;
    int j = r;
    int mid;

    while(i < j){
        mid = (i+j)/2;
        if(arr[mid] > t)
            j = mid-1;
        else if(arr[mid] < t)
            i = mid+1;
        else{
            if(mid == 0 ){
                return mid;
            }
            if(arr[mid - 1] == t){
                j = mid - 1;
                continue;
            }

            return mid;
        }
    }

    if(i < j){
        return mid;
    }

    return -1;
}

int main(void){
    int arr[] = {2, 4, 3, 3, 3, 8, 9, 0};
    int len = sizeof(arr)/sizeof(int);

    int num = find(arr, 0, len-1, 3); 
    
    cout<<"num:"<<num<<endl;

    int first = find_firstK(arr, 0, len-1, 3);

    cout<<"first:"<<first<<endl;

    return 0;
}
