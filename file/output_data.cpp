#include <iostream>
#include <string>
#include <list>
#include <fstream>

#include "output_data.h"

int output_data(const std::string &file_path, 
		const std::string &groupid,
		std::list<std::string> &data_list) {

	std::fstream out;
	out.open(file_path.c_str(), std::ios::out | std::ios::app);
	if (!out.is_open()) {
		std::cout<< "open file "<<file_path << " faild" <<std::endl;

		return -1;
	}

	out<<groupid;
	out<<'\t';

	std::list<std::string>::iterator itor = data_list.begin();
	while (itor != data_list.end()) {
		out<< *itor;
		itor++;
		if (itor != data_list.end()) {
			out<<",";
		}		
	}

	out << std::endl;
	out.close();

	return 0;
}
