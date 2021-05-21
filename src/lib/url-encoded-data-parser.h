#ifndef _UrlEncodedDataParser_H
#define _UrlEncodedDataParser_H
#include <string>
#include <map>

void parseUrlEncodedData(string rawData, map<string, string>& parsedData);

string parseToUrlEncodedData(map<string, string>& data);

#endif // UrlEncodedDataParser_H