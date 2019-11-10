#pragma once
#include "SFML\Graphics.hpp"

class Mass : public sf::CircleShape
{
public:
	Mass(float m = 1);
	~Mass();
	float GetAmountKG() const { return mass; }
	void SetAmountKG(float m) { mass = m; setRadius(5 * mass); }

	void setRenderWindow(sf::RenderWindow* w) {
		window = w;
	}
	void Draw();
protected:
	float mass;
	sf::RenderWindow* window;
};

