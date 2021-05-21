#ifndef _COOKIE_PARSER_H
#define _COOKIE_PARSER_H

#include <string>
#include <map>
using namespace std;

void getCookie(map<string, string>& cookieMap);

string createCookieHeader(map<string, string>& cookieMap);

bool tokenCookieExists(map<string, string>& cookieMap);

#endif // _COOKIE_PARSER_H