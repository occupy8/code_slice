#include <iostream>
#include <string>
#include <vector>

using namespace std;

void split(string str, string separator, vector<string> &result) {
    result.clear();
    string::size_type position = str.find(separator);
    string::size_type lastPosition = 0;
    uint32_t separatorLength = separator.length();

    while (position != str.npos) {
        result.push_back(str.substr(lastPosition, position - lastPosition));
        lastPosition = position + separatorLength;
        position = str.find(separator, lastPosition);
    }
    result.push_back(str.substr(lastPosition, string::npos));
}

int main(void){

    string str("1\n98\noienqwa");
    vector<string> result;

    split(str, "\n", result);

    int i;
    for(i = 0; i < result.size(); i++)
    {
        string tmp = result[i];
        cout<<tmp<<endl;
    }

    cout<<"------------------------------"<<endl;
    
    return 0;
}
