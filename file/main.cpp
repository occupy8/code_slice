#include "load_data.h"
#include <map>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	map<string, vector<float> > data_list;

	load_data_from_disk("./data.txt", data_list);	

	map<string, vector<float> >::iterator itor;	

	for (itor = data_list.begin(); itor != data_list.end();) {
		cout<<itor->first<<endl;

		itor++;
	}
	
	return 0;
}
