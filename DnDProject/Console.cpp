#include "Console.h"

Console* Console::instance = nullptr;


string Console::getLine(int line)
{
	if (line > 0 && line <= lines.size())
		return lines.at(lines.size() - line);
	return "";
}

void Console::addLine(string line)
{
	lines.push_back(line);
}

Console* Console::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Console();
	}
	return instance;
}