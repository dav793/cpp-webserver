#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

#include "lib/config.h"
#include "lib/template-parser.h"
#include "lib/crypto.h"
#include "lib/cookie-parser.h"

map<string, string> configMap;		// aqui se cargan las variables de configuracion extraidas de /config/config

map<string, string> interpolationMap { 
	{"restaurantName", "Bob's burgers"},
	{"mainDish", "Burgers"},
	{"sideDish", "Fries"}
};

map< string, vector< map<string, string> > > interpolationVectorMap {
	{ "shopItems", {
		{ {"name", "Burger"}, {"pricePerUnit", "$4.50"} },
		{ {"name", "Fries"}, {"pricePerUnit", "$1.50"} },
		{ {"name", "Hot dog"}, {"pricePerUnit", "$2.50"} },
		{ {"name", "Coca Cola"}, {"pricePerUnit", "$1.00"} }
	} }
};

string getErrorDescription(int exception) {
	switch(exception) {
		case 42:
			return "Invalid interpolation pattern (" + to_string(exception) + ")";
		default:
			return "Unrecognized exception (" + to_string(exception) + ")";
	}
}

int main(int argc, char* argv[], char* env[]) {

	parseConfigFile(configMap);

	// parse template file
	vector<string> lines;
	try {
		parseTemplate(configMap["TEMPLATES_PATH"] + "/test.html", interpolationMap, interpolationVectorMap, lines);
	}
	catch(int e) {
		lines.clear();
		map<string, string> errorMap { 
			{"code", "500"},
			{"message", getErrorDescription(e)}
		};
		parseTemplate(configMap["TEMPLATES_PATH"] + "/error.html", errorMap, interpolationVectorMap, lines);
	}

	// print request headers
	cout << "Content-type: text/html\n\n";

	// print request body
	for (int i = 0; i < lines.size(); ++i) {
		cout << lines[i];
	}
		
	// read cookie
	map<string, string> cookieMap;
	getCookie(cookieMap);
	if (tokenCookieExists(cookieMap)) {
		cout << "COOKIE TOKEN = " << cookieMap["token"] << "\n";
	}
	else {
		cout << "No valid cookie was found" << "\n";
	}

	return 0;

}