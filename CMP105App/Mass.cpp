#include "Mass.h"



Mass::Mass(float m)
{

	SetAmountKG(m);
	setOrigin(getRadius() / 2.0f, getRadius() / 2.0f);
	setRotation(0);
	setPosition(300, 300);
	setFillColor(sf::Color::Red);
}


Mass::~Mass()
{
}


void Mass::Draw()
{
	if (window)
	{
		window->draw(*this);
	}
}
