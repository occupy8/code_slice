#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

/*
 *     
 */
int load_data_from_disk(const std::string &file_path, 
		std::map<std::string, std::vector<float> > &data_list);
