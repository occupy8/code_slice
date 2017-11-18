/*
 * 0,1,...,n-1这n个数字排成一个圆圈，从数字0开始每次从这个圆圈里删除第m个数字。求出这个圆圈里剩下的最后一个数字
 */

#include <iostream>
#include <list>

using namespace std;

int lastRemaining(int n, int m){
    if(n < 1 || m < 1)
        return -1;

    int i;
    list<int> digit_list;
    for(i = 0; i < n; i++){
        digit_list.push_back(i);
    }

    list<int>::iterator it;
    it = digit_list.begin();
    while(digit_list.size() > 1){
        for(i = 1; i < m; i++){
            it++;

            if(it == digit_list.end()){
                it = digit_list.begin();
            } 
        }

        list<int>::iterator next = ++it;
        if(next == digit_list.end()){
            next = digit_list.begin();
        }

        --it;
        digit_list.erase(it);
        it = next;
    }

    return *it;
}

int main(void){
    int n = 10;
    int m = 7;

    int last = lastRemaining(n, m);
    
    cout<<"last:"<<last<<endl; 
}
