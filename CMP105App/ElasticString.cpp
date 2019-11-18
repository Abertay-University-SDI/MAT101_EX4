#include "ElasticString.h"
#include "CollisionDetection.h"


 const float ElasticString::GravityConstant = 9.8f;

ElasticString::ElasticString(float nLength, float massKG, float positionOnBar, float kValue) :
	naturalLength(nLength),
	mass(massKG),
	isMassSelected(false)
{

	//k = lamda/l   kValue*l = lamda;
	lamda = kValue * naturalLength;

	setPosition(positionOnBar, 150);
	
	velocity = 0;


	xExtensionEquil = (massKG*GravityConstant*naturalLength) / lamda;
	xExtension = xExtensionEquil;
	UpdateVertPosition(naturalLength + xExtension);
	
}


ElasticString::~ElasticString()
{
}


void ElasticString::UpdateVertPosition(float y)
{
	setSize(sf::Vector2f(10,  y));
	mass.setPosition(getPosition() + sf::Vector2f(getSize().x*0.5f - mass.getRadius()*0.5f, getSize().y));
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
		//CHECK INPUT TO Increase or decrease mass 
	}
	if (isMassSelected)
	{
		return; //don't move with kinematics if currently selected
	}


	//T = mg = kx = lamda*x / l  in equilibrium
	//mgl/lamda = EqualibriumX
	xExtensionEquil = mass.GetAmountKG()*GravityConstant*naturalLength / lamda;


	//set xExtension  based on position of ball -or- end of string and natural length 
	float x = fabs(getSize().y) - naturalLength ;
	xExtension =std::max( x, 0.0f);  //our extension is a positive or we are slack 

	//determine if above or below fixed point, and the xExtention (or 0 if slack)
	isAboveFixedPoint = (getSize().y < 0) ? true : false;
	
	float sign = isAboveFixedPoint ? 1.0f : -1.0f;

	
	//F = ma
	//T-mg = ma while below the Equilibrium  and -T - mg while above fixpoint and equilbrium
	//Here add Dampening based on velocity  D(v)
	//F = T - mg  if F > 0 then -D(v)  if F < 0 then +D(v)  dampening always opposes force of motion
	float Tension = sign * (lamda*xExtension) / (naturalLength);
	float force = Tension + GravityConstant *mass.GetAmountKG();

	float dSign = velocity > 0 ? -1.0f : 1.0f; //always opposes motion 
	force += dSign *abs(Tension)* 0.3;


	float acceleration = force / mass.GetAmountKG();
	//need to keep ratio of pixels to meters 
	//need to check to see if x = 0 (or negative) in which case it is slack and only g is acting on it
	//float acceleration = sign*(lamda*xExtension) / (naturalLength*mass.GetAmountKG()) + GravityConstant;//positive is down

	if (fabs(acceleration) < 0.0001)
	{
		acceleration = 0;
	}

	
	//resistence to motion relative to velocity 
	//t = dt
	//u = last frame v
	//v = u + at
	//s = ut + 1/2at^2;
	float u = velocity;
	velocity = u + acceleration * dt;
	//update position if not being selected (in y)
	float s = u * dt + 0.5*acceleration*dt*dt;
	//update length of string
	float newTotalLength = getSize().y + s;

	
	UpdateVertPosition(newTotalLength);


	
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
