#include "ElasticString.h"



ElasticString::ElasticString(float nLength, float massKG, float kValue):
	naturalLength(nLength),
	mass(massKG)
{

  //k = lamda/l   kValue*l = lamda;
	lamda = kValue * naturalLength;
}


ElasticString::~ElasticString()
{
}

void ElasticString::update(float dt)
{
}


void ElasticString::setRenderWindow(sf::RenderWindow * w)
{
	pWindow = w;
	//for each mass
	mass.setRenderWindow(w);
}


void ElasticString::Draw()
{
	if (pWindow)
	{
		pWindow->draw(*this);
	}
	mass.Draw();
}
