/*
 * 一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。要求时间复杂度是O（n）,空间复杂度是O（1） 
 */
#include <iostream>

using namespace std;

//check the position of num is 1 ??
bool check_bit(int num, int position){
    if((num >> position) & 0x01){
        return true;
    }

    return false;
}

int whereis_bit(int num){
    int roll = 0;
    while((num & 0x1 == 0)&&( roll <= sizeof(int)*8 ) ){
        num = num >> 1;
        roll++;
    }

    if(roll < sizeof(int)*8){
        return roll;
    }

    return -1;
} 

int find_nums(int arr[], int len, int *num1, int *num2){
    if(NULL == arr || NULL == num1 || NULL == num2){
        return -1;
    }

    int i;
    int checknum = 0;
    for(i = 0; i < len; i++){
        checknum ^= arr[i];
    }

    int where = whereis_bit(checknum);
    if(where == -1){
        return -1;
    }

    *num1 = 0;
    *num2 = 0;

    for(i = 0; i < len; i++){
        if(check_bit(arr[i], where)){
            *num1 ^= arr[i];
        }else{
            *num2 ^= arr[i];
        }
    } 

    return 0;
}

int main(void){
    int arr[] = {2, 3, 5, 2, 3, 6, 7, 7};

    int num1;
    int num2;

    int ret = find_nums(arr, sizeof(arr)/sizeof(int), &num1, &num2);
    if(ret == 0){
        cout<<num1<<" "<<num2<<endl;
    }

    return 0;
}
