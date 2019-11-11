#include "ElasticString.h"
#include "CollisionDetection.h"


ElasticString::ElasticString(float nLength, float massKG, float positionOnBar, float kValue) :
	naturalLength(nLength),
	mass(massKG),
	isMassSelected(false)
{

	//k = lamda/l   kValue*l = lamda;
	lamda = kValue * naturalLength;

	setPosition(positionOnBar, 150);
	setSize(sf::Vector2f(10, naturalLength * 100));
	mass.setPosition(getPosition() + sf::Vector2f(getSize().x*0.5f - mass.getRadius()*0.5f, getSize().y));
	velocity = 0;
}


ElasticString::~ElasticString()
{
}

void ElasticString::update(float dt)
{
	//USER INPUT TO PULL DOWN THE MASS
	if (input != nullptr )
	{
		//Check to see if the mouse is on the mass 
		if (input->isMouseLDown() && Collision::CirclePoint(mass.getRadius()*1.02f, mass.getPosition(), sf::Vector2f(input->getMouseX(), input->getMouseY())))
		{
			isMassSelected = true;
		}
		if (!input->isMouseLDown())
		{
			isMassSelected = false;
		}


		if (isMassSelected)
		{
			mass.setFillColor(sf::Color::Green);
			mass.setPosition(sf::Vector2f(mass.getPosition().x, input->getMouseY()));
			float yLength = mass.getPosition().y - getPosition().y;
			setSize(sf::Vector2f(getSize().x, yLength));
		}
		else
		{
			mass.setFillColor(sf::Color::Red);
		}

		//Increase or decrease mass 
	}



	//figure out energy at a given point
	//ifMassIsSelected then v = 0, otherwise might have a velocity 
	//T = mg = kx = lamda*x / l  in equilibrium
	//mgl/lamda = EqualibriumX
	xExtentionEquil = mass.GetAmountKG()*9.8*naturalLength / lamda;


	//set xExtension  based on position of ball and natural length 
	//determine if above or below fixed point, and the xExtention (or 0 if slack)

	//F = ma
	//T-mg = ma while below the Equilibrium 
	//need to keep ratio of pixels to meters 
	//need to check to see if x = 0 (or negative) in which case it is slack and only g is acting on it
	float acceleration = -(lamda*xExtention) / (naturalLength*mass.GetAmountKG()) + 9.8;//positive is down
	//resistence to motion relative to velocity 
	//t = dt
	//u = last frame v
	//v = u + at
	//s = ut + 1/2at^2;
	//update position if not being selected (in y)
	//update length of string
	




	// SEnergy = 1/2kx^2   

	
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
