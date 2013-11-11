#pragma once
#include "Game.h"

class ButtonConstants
{
private:

	ButtonConstants(void)
	{
	}

	virtual ~ButtonConstants(void)
	{
	}

public:
	// The width of an extra-small button.
	static const int XSMALL_WIDTH = 50;

	// The height of an extra-small button.
	static const int XSMALL_HEIGHT = 40;

	// The width of a small button.
	static const int SMALL_WIDTH = 100;

	// The height of a small button.
	static const int SMALL_HEIGHT = 40;

	// The width of a medium button.
	static const int MEDIUM_WIDTH = 200;

	// The height of a medium button.
	static const int MEDIUM_HEIGHT = 40;

	// The vertical spacing between buttons.
	static const int VERTICAL_SPACING = 20;

	static void determineInitialButtonPositions(int *initialX, int *initialY, int buttonWidth, int buttonHeight, int buttonCount, int hDivide, int vDivide) {
		ButtonConstants::determineInitialButtonPositions(initialX, initialY, buttonWidth, buttonHeight, buttonCount, hDivide, vDivide, 1, 1);
	}

	static void determineInitialButtonPositions(int *initialX, int *initialY, int buttonWidth, int buttonHeight, int buttonCount, int hDivide, int vDivide, int hLine, int vLine) {
		int calculatedHorizontal = Game::getInstance()->getWindowWidth() / hDivide;
		int calculatedVertical = Game::getInstance()->getWindowHeight() / vDivide;
		
		*initialX = (calculatedHorizontal * vLine) - (buttonWidth / 2);
		*initialY = 
			(calculatedVertical * hLine) + 
			(vDivide % 2 != 0 ? (calculatedVertical)/2 : 0) - 
			(buttonHeight * buttonCount + ButtonConstants::VERTICAL_SPACING*(buttonCount-1))/2;
	};
};

