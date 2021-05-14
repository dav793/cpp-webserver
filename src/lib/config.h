#ifndef _Config_H
#define _Config_H
#include <map>

void parseConfigFile(map<string, string>& configMap);

void parseConfigLine(string line, map<string, string>& configMap);

#endif // Config_H