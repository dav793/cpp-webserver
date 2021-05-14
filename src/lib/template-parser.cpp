#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

#include "lib/template-parser.h"

string parseTemplateLine(string line, map<string, string>& interpolationMap) {
	string parsedLine = line;
	int currentPosition = 0;
	while(currentPosition >= 0 && currentPosition < parsedLine.length()) {

		size_t foundStart = parsedLine.find("{{", currentPosition);
		if (foundStart == string::npos) {
			currentPosition = -1;
			continue;
		}

		size_t foundEnd = parsedLine.find("}}", foundStart);
		if (foundEnd == string::npos)
			throw 42;

		string interpolationName = parsedLine.substr(foundStart+2, foundEnd-foundStart-2);
		parsedLine = parsedLine.replace(foundStart, foundEnd+2-foundStart, interpolationMap[interpolationName]);
		currentPosition = foundStart + interpolationMap[interpolationName].length();

	}

	return parsedLine;
}

void parseTemplate(
	string filepath, 
	map<string, string>& interpolationMap, 
	map< string, vector< map<string, string> > >& interpolationVectorMap, 
	vector<string>& linesOutput
) {
	string line;
	ifstream myfile(filepath);
	
	if (myfile.is_open()) {

		while ( getline(myfile, line) )	{

			size_t loopStartPos = line.find("[[");
			if (loopStartPos == string::npos)
				linesOutput.push_back(parseTemplateLine(line, interpolationMap) + "\n");
			else {
				
				size_t loopNameEndPos = line.find(":", loopStartPos);
				if (loopNameEndPos == string::npos)
					throw 42;

				size_t loopIndexEndPos = line.find(":", loopNameEndPos+1);
				if (loopIndexEndPos == string::npos)
					throw 42;

				string loopName = line.substr(loopStartPos+2, loopNameEndPos-loopStartPos-2);
				string indexName = line.substr(loopNameEndPos+1, loopIndexEndPos-loopNameEndPos-1);

				int loopBegin = myfile.tellg();
				int loopEnd;
				for (int j = 0; j < interpolationVectorMap[loopName].size(); ++j) {
				
					while ( getline(myfile, line) )	{
					
						size_t endOfLoopPos = line.find("]]");
						if (endOfLoopPos != string::npos) {
							getline(myfile, line);
							loopEnd = myfile.tellg();
							myfile.seekg(loopBegin-4);
							break;
						}
						else {
							interpolationVectorMap[loopName][j][indexName] = to_string(j);
							linesOutput.push_back(parseTemplateLine(line, interpolationVectorMap[loopName][j]) + "\n");
							map<string, string>::iterator it = interpolationVectorMap[loopName][j].find(indexName);
							interpolationVectorMap[loopName][j].erase(it);
						}

					}
				
				}

				myfile.seekg(loopEnd);

			}
			
		}

		myfile.close();

	}
	else {
		cout << "Unable to open file"; 
	}
}
