#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"

GameObject::GameObject(LoaderParameters* parameters)
{
	this->parameters = parameters;
	clicked = false;
}

LoaderParameters* GameObject::getParameters()
{
	return parameters;
}

void GameObject::draw()
{
	TextureManager::getInstance()->draw(parameters, Game::getInstance()->getRenderer());
}

void GameObject::handleEvents()
{
	// Check if this object as been clicked.
	if (InputHandler::getInstance()->getMouseButtonState(LEFT_BUTTON) &&
		(InputHandler::getInstance()->getMouseX() > parameters->getXPos()) &&
		(InputHandler::getInstance()->getMouseX() < (parameters->getXPos() + parameters->getWidth())) &&
		(InputHandler::getInstance()->getMouseY() > parameters->getYPos()) &&
		(InputHandler::getInstance()->getMouseY() < (parameters->getYPos() + parameters->getHeight())))
	{
		clicked = true;
	}
}

bool GameObject::isClicked()
{
	return clicked;
}

void GameObject::resetClicked()
{
	clicked = false;
}

void GameObject::clean()
{

}