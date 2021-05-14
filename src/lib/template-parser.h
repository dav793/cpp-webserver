#ifndef _TemplateParser_H
#define _TemplateParser_H
#include <string>
#include <map>

void parseTemplate(
	string filepath, 
	map<string, string>& interpolationMap, 
	map< string, vector< map<string, string> > >& interpolationVectorMap, 
	vector<string>& linesOutput
);

string parseTemplateLine(string line, map<string, string>& interpolationMap);

#endif // TemplateParser_H