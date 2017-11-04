#include <stdio.h>
#include <stdlib.h>

/**
 * 求子数组的最大和,数组里有正数也有负数
 * keep current sum, slide from left to right, when sum < 0, reset sum to 0
 */
int maxSubarray(int a[], int size){
    if(size <= 0)
        return 0;
    int sum = 0;
    int max = -(1 << 31);
    int cur = 0;

    while(cur < size){
        sum += a[cur++];
        
        if(sum > max)
        {
            max = sum;
        }else if(sum < 0){
            sum = 0;
        }
    }

    return max;
}
