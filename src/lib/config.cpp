#include <fstream>
#include <iostream>
#include <string>
#include <map>
using namespace std;

#include "lib/config.h"

string config_filepath = "../config/config";

void parseConfigFile(map<string, string>& configMap) {

	string line;
	ifstream myfile(config_filepath);

	if (myfile.is_open()) {
		while ( getline(myfile, line) )	{
			parseConfigLine(line, configMap);
		}
		myfile.close();
	}
	else {
		cout << "Unable to open file"; 
	}

}

void parseConfigLine(string line, map<string, string>& configMap) {
	size_t separatorPos = line.find("=");
	if (separatorPos == string::npos) 
		throw 101;

	string variableName = line.substr(0, separatorPos);
	string variableValue = line.substr(separatorPos+1, string::npos);
	configMap[variableName] = variableValue;
}
