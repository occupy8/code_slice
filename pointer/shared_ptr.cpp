#include <iostream>

using namespace std;

template<class T>
class shared_ptr{
private:
    T *m_ptr;
    unsigned int shared_count;
public:
    shared_ptr(T* p):m_ptr(p),shared_count(1){}
    ~shared_ptr(){ deconstruct(); }
    void deconstruct(){
        if(shared_count == 1){
            delete m_ptr;
            m_ptr = 0;
        }

        shared_count--;
    }

    T& operator*(){ return *m_ptr; }
    T* operator->() { return m_ptr; }

    shared_ptr(shared_ptr &sp):m_ptr(sp.m_ptr), shared_count(sp.shared_count){
        shared_count++;
    }

    shared_ptr& operator=(shared_ptr& sp){
        sp.shared_count++;
        deconstruct();
        m_ptr = sp.m_ptr;
        shared_count = sp.shared_count;

        return *this;
    }

};
