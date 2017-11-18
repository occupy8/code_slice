/*
 * 一个不能被继承的类
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class no_inherit{
public:
    static no_inherit *getInstance(){
        return new no_inherit();
    }

    static void deleteInstance(no_inherit *tmp){
        delete tmp; 
    }

private:
    no_inherit(){}
    ~no_inherit(){}
}; 
