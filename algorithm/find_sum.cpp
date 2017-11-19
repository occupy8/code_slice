/*
 * 找到和为某一结果的一对数，数组是已经排好序的，递增顺序
 */

#include <iostream>

using namespace std;

int find_num(int arr[], int len, int *num1, int *num2, int sum){
    if(NULL == arr || len < 2 || num1 == NULL || num2 == NULL)
        return -1;

    int pre = 0;
    int last = len-1;

    while(pre < last){
        if(arr[pre]+arr[last] < sum){
            pre++;
        }else if(arr[pre] + arr[last] > sum){
            last--;
        }else{
            *num1 = arr[pre];
            *num2 = arr[last];
            return 0;
        }
    }

    return -1;
}

int main(void){
    int arr[] = { 1, 2, 3, 8, 10, 12};
    int sum = 10;
    int len = sizeof(arr)/sizeof(int);

    int num1 = 0;
    int num2 = 0;
    find_num(arr, len, &num1, &num2, sum);

    cout<<"num1:"<<num1<<"num2:"<<num2<<endl;

    return 0;
}
