#include <iostream>

using namespace std;

template<class T>

class shared_ptr{
	private:
		T* m_ptr; //被封装的指针
		unsigned int shared_count;   //引用计数,表示有多少个智能指针对象拥有m_ptr指向的内存块

	public:
		shared_ptr(T* p):m_ptr(p),shared_count(1){ }
		~shared_ptr() { deconstruct();}

		void deconstruct(){
			if(shared_count == 1)   //引用计数为1表示只有一个对象使用指针指向的内存块了
			{
				delete m_ptr;
				m_ptr = 0;
			}

			shared_count--;
		}

		T& operator*() { return *m_ptr;}
		T* operator->() { return m_ptr;}

		//复制构造函数
		shared_ptr(shared_ptr& sp):m_ptr(sp.m_ptr),shared_count(sp.shared_count){
			shared_count++;
		}

		//重载运算符=
		shared_ptr& operator = (shared_ptr& sp){
			sp.shared_count++;   
			deconstruct();  //相当于先删掉左值,然后再通过右值赋值.
			m_ptr = sp.m_ptr;
			shared_count = sp.shared_count;

			return *this;
		}　
};

struct Arwen{
	int age;

	Arwen(int gg) :age(gg) { };
};


//下面代码全部运行正确
void main(){
	shared_ptr<Arwen> myPtr( new Arwen(24) );
	int num =myPtr->age;
	shared_ptr<Arwen> ptrOne( myPtr); //复制构造
	num =myPtr->age; //如果是auto_ptr该处会出错.因为把myPtr复制给ptrOne后,它自己本身相当于失效了

	num = ptrOne->age;
	shared_ptr<Arwen> ptrTwo = ptrOne;
	num = ptrOne->age;//如果是auto_ptr该处也会出错,此时ptrOne也失效了
	num = ptrTwo->age;

	return 0;
}
