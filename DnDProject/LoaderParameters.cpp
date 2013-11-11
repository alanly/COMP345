#include "LoaderParameters.h"


LoaderParameters::LoaderParameters(int xPos, int yPos, int width, int height, int row, int column, string id)
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->width = width;
	this->height = height;
	this->row = row;
	this->column = column;
	this->id = id;
}

int LoaderParameters::getXPos() const
{
	return xPos;
}

int LoaderParameters::getYPos() const
{
	return yPos;
}

int LoaderParameters::getWidth() const
{
	return width;
}

int LoaderParameters::getHeight() const
{
	return height;
}

int LoaderParameters::getRow() const
{
	return row;
}

int LoaderParameters::getColumn() const
{
	return column;
}

string LoaderParameters::getId() const
{
	return id;
}


void LoaderParameters::setXPos(int xPos)
{
	this->xPos = xPos;
}

void LoaderParameters::setYPos(int yPos)
{
	this->yPos = yPos;
}

void LoaderParameters::setWidth(int width)
{
	this->width = width;
}
void LoaderParameters::setHeight(int height)
{
	this->height = height;
}

void LoaderParameters::setRow(int row)
{
	this->row = row;
}

void LoaderParameters::setColumn(int column)
{
	this->column = column;
}

void LoaderParameters::setId(string id)
{
	this->id = id;
}