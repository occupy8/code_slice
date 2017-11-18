/*
 * 1+2+...+n
 * 不能用乘除法，和if，else，while
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int add(int n){
    if(n == 0)
        return 0;
    else
        return add(n-1)+n;
}

class Temp{
public:
    Temp() {++N; Sum += N;}

    static void Reset() { N = 0; Sum = 0; }
    static unsigned int GetSum() { return Sum; }
private:
    static unsigned int N;
    static unsigned int Sum;
};

unsigned int Temp::N = 0;
unsigned int Temp::Sum = 0;

unsigned int Sum_Solution1(unsigned int n){
    Temp::Reset();

    Temp *a = new Temp[n];
    delete []a;
    a = NULL;

    return Temp::GetSum();
}

int main(void){
    int n = Sum_Solution1(100);

    cout<<n<<endl;    
}
