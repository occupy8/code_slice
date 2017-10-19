#include <iostream>
#include <stack>

using namespace std;

class NewQueue{
private:
	stack<int> st1, st2;
public:
	void enter(int value)
	{
		st1.push(value);
	}

	int out(){
		int val;
		if(st2.empty()){
			while(!st1.empty()){
				int i = st1.top();
				st1.pop();
				st2.push(i);
			}
		}

		val = st2.top();
		st2.pop();

		return val;
	}

	bool qEmpty() const
	{
		return st1.empty() && st2.empty();
	}
};


int main(int argc, const char *argv[]){
	NewQueue q;
	
	int i = 3;
	int j = 5;
	int k = 4;

	q.enter(i);
	q.enter(j);
	q.enter(k);

	while(!q.qEmpty()){
		cout<< q.out() <<endl;
	}
}
