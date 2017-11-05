/*
 * 1+2+...+n
 * 不能用乘除法，和if，else，while
 *
 */

int add(int n){
    if(n == 0)
        return 0;
    else
        return add(n-1)+n;
}


