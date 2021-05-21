#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

#include "lib/url-encoded-data-parser.h"

void parseUrlEncodedData(string rawData, map<string, string>& parsedData) {

	int currentPosition = 0;
	while(currentPosition >= 0 && currentPosition < rawData.length()) {
	
		size_t foundEqual = rawData.find("=", currentPosition);
		if (foundEqual == string::npos) {
			currentPosition = -1;
			continue;
		}
		string varName = rawData.substr(currentPosition, foundEqual-currentPosition);
		string varValue;

		size_t foundAmp = rawData.find("&", foundEqual);
		if (foundAmp == string::npos) {
			currentPosition = -1;
			varValue = rawData.substr(foundEqual+1, string::npos);
		}
		else {
			varValue = rawData.substr(foundEqual+1, foundAmp-foundEqual-1);	
			currentPosition = foundAmp+1;
		}

		// cout << "VAR_NAME = " << varName << "; " << "VAR_VALUE = " << varValue << ";\n";
		parsedData[varName] = varValue;

	}

}

string parseToUrlEncodedData(map<string, string>& data) {

	string encodedData = "";

	for(map<string, string>::iterator i = data.begin(); i != data.end(); ++i) {
		string key = i->first;
		string value = i->second;
		
		if (i != data.begin()) {
			encodedData.append("&");
		}
		encodedData.append(key);
		encodedData.append("=");
		encodedData.append(value);
	}

	// cout << "ENCODED DATA = " << encodedData << ";\n";

	return encodedData;

}
