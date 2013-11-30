#pragma once

#include <vector>
#include <string>

using namespace std;

class Console
{
private:
	Console() {}

	static Console* instance;

	vector<string> lines;

public:
	string getLine(int line);
	void addLine(string line);

	static Console* getInstance();
};

