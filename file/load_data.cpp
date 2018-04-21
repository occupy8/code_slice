#include "load_data.h"
#include <fstream>
#include <map>
#include <vector>
#include <string>

void split_string(const std::string &s, std::vector<std::string> &v, const std::string &c) {
	std::string::size_type pos1;
	std::string::size_type pos2;

	pos2 = s.find(c);
	pos1 = 0;
	while(std::string::npos != pos2) {
		v.push_back(s.substr(pos1, (pos2 - pos1)));
		
		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}	

	if (pos1 != s.length()) {
		v.push_back(s.substr(pos1));
	}
}

int load_data_from_disk(const std::string &file_path, 
		std::map<std::string, std::vector<float> > &data_list) {

	std::ifstream in(file_path.c_str());
	if (!in.is_open()) {
		std::cout<< "open file "<< file_path << "failed !" <<std::endl;
	}

	std::string line;
	while (!in.eof()) {
		getline(in, line);
		std::cout << line << std::endl;

		//featureid'\t'feature
		std::vector<std::string> result;
		split_string(line, result, "\t");
		if (result.size() != 2) {
			continue;
		}

		//decry
		std::vector<float> feature;
		data_list[result[0]] = feature;
	}

	in.close();
	
	return 0;
}
