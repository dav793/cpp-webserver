#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
using namespace std;

#include "lib/cookie-parser.h"
#include "lib/url-encoded-data-parser.h"
#include "lib/crypto.h"

void getCookie(map<string, string>& cookieMap) {
	string cookieHeaderName = "HTTP_COOKIE";
	char* cookieValue = (char*) getenv(cookieHeaderName.c_str());
	if (cookieValue) {
		// @todo: desencriptar cookie
		string cookieValueStr(cookieValue);
		parseUrlEncodedData(cookieValueStr, cookieMap);
	}
}

string createCookieHeader(map<string, string>& cookieMap) {
	string sessionCookie = parseToUrlEncodedData(cookieMap);
	// @todo: encriptar cookie
	string cookieHeader = "Set-Cookie: token=" + sessionCookie + "; Path=/";
	return cookieHeader;
}

bool tokenCookieExists(map<string, string>& cookieMap) {
	if (!cookieMap.empty()) {
		map<string, string>::iterator it = cookieMap.find("token");
		if (it != cookieMap.end() && it->second.compare("deleted") != 0) {
			return true;
		}
	}
	return false;
}
