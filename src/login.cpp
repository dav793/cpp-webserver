#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

#include "lib/config.h"
#include "lib/template-parser.h"
#include "lib/url-encoded-data-parser.h"
#include "lib/crypto.h"

map<string, string> configMap;		// aqui se cargan las variables de configuracion extraidas de /config/config

map<string, string> interpolationMap {};

map< string, vector< map<string, string> > > interpolationVectorMap {};

string getErrorDescription(int exception) {
	switch(exception) {
		case 42:
			return "Invalid interpolation pattern (" + to_string(exception) + ")";
		default:
			return "Unrecognized exception (" + to_string(exception) + ")";
	}
}

int main(void) {

	parseConfigFile(configMap);
	vector<string> lines;
	bool redirect = false;
	char* len_ = getenv("CONTENT_LENGTH");
	long len = strtol(len_, NULL, 10);
	// cout << "\n" << "CONTENT LENGTH = " << len << "\n";

	if (len == 0) {
		// no post data found: show login page

		// parse template file
		try {
			parseTemplate(configMap["TEMPLATES_PATH"] + "/login.html", interpolationMap, interpolationVectorMap, lines);
		}
		catch(int e) {
			lines.clear();
			map<string, string> errorMap { 
				{"code", "500"},
				{"message", getErrorDescription(e)}
			};
			parseTemplate(configMap["TEMPLATES_PATH"] + "/error.html", errorMap, interpolationVectorMap, lines);
		}
	}
	else {
		// post data found: try to login and redirect to index or show login failure page

		char* postdata = (char *) malloc(len + 1);
		if (!postdata) {
			exit(1);
		}
		fgets(postdata, len + 1, stdin);

		// cout << "\n" << "POSTDATA = " << postdata << "\n";

		string postdata_str(postdata);
		free(postdata);
		map<string, string> parsedPostdata;
		parseUrlEncodedData(postdata_str, parsedPostdata);

		// try to log in

		redirect = true;

		try {
			parseTemplate(configMap["TEMPLATES_PATH"] + "/login.html", interpolationMap, interpolationVectorMap, lines);
		}
		catch(int e) {
			lines.clear();
			map<string, string> errorMap { 
				{"code", "500"},
				{"message", getErrorDescription(e)}
			};
			parseTemplate(configMap["TEMPLATES_PATH"] + "/error.html", errorMap, interpolationVectorMap, lines);
		}

		//try {
		//	parseTemplate(configMap["TEMPLATES_PATH"] + "/login-fail.html", interpolationMap, interpolationVectorMap, lines);
		//}
		//catch(int e) {
		//	lines.clear();
		//	map<string, string> errorMap { 
		//		{"code", "500"},
		//		{"message", getErrorDescription(e)}
		//	};
		//	parseTemplate(configMap["TEMPLATES_PATH"] + "/error.html", errorMap, interpolationVectorMap, lines);
		//}

	}

	// print request headers
	if (redirect == true) {
		cout << "Status: 303 See Other\n";
		cout << "Location: http://localhost\n";
	}
	cout << "Content-type: text/html\n\n";

	// print request body
	for (int i = 0; i < lines.size(); ++i) {
		cout << lines[i];
	}
		
	return 0;

}