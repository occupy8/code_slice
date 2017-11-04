#include <stdio.h>
#include <stdlib.h>

int Fib(int n)
{
    if(n <= 0)
        return 0;

    if(n == 1)
    {
        return 1;
    }
    else if(n == 2)
    {
        return 2;
    }
    else
    {
        return Fib(n-1) + Fib(n-2);
    }
}

int main(void){
    int num = 3;

    int max = Fib(num);

    printf("num:%d, max:%d\n", num, max);

    return 0;
}
