#include <iostream>

/*
 * n1:32767n2:0
 * 构造函数的初始化顺序只和声明顺序有关
 *
 */

using namespace std;

class A{
private:
    int n1;
    int n2;
public:
    A():n2(0),n1(n2+2){

    } 

    void show(){
        cout<<"n1:"<<n1<<"n2:"<<n2<<endl;
    }
};

int main(void){
    A a;
    a.show();
}
