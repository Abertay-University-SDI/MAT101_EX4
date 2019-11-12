#include "Level.h"

#include <Windows.h>

Level::Level(sf::RenderWindow* hwnd, Input* in):
	elasticString(200, 2,150, 5)
{
	window = hwnd;
	input = in;

	// initialise game objects
	play = true;

	zigTexture.loadFromFile("gfx/zig.png");
	Bar.setFillColor(sf::Color::Black);
	Bar.setPosition(0, 150);
	Bar.setSize(sf::Vector2f(window->getSize().x, 10.0f));
	elasticString.setTexture(&zigTexture);
	elasticString.setInput(input);
	//elasticString.setSize(sf::Vector2f(100, 100));
	elasticString.setRenderWindow(window);
	if (!font.loadFromFile("font/arial.ttf"))
	{
		// something went wrong
		MessageBox(NULL, L"Font failed to load", L"Error", MB_OK);
	}

	//drag = false;

	// Create a text
	text.setString("Elastics");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	//text.setPosition(10, 10);
	text.setFillColor(sf::Color::Red);


}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	//The class that provides access to the keyboard state is sf::Keyboard.It only contains one function, isKeyPressed, which checks the current state of a key(pressed or released).It is a static function, so you don't need to instanciate sf::Keyboard to use it.
		//This function directly reads the keyboard state, ignoring the focus state of your window.This means that isKeyPressed may return true even if your window is inactive.
	if (input->isKeyJustDown(sf::Keyboard::Escape))
	{
		input->setKeyUp(sf::Keyboard::Escape);
		window->close();
	}
	if (input->isKeyJustDown(sf::Keyboard::Return))
	{
		
		play = !play;
	}
}

// Update game objects
void Level::update(float dt)
{
	if (play)
	{
		


		elasticString.update(dt);
		/*std::string xpos = std::to_string(sf::Mouse::getPosition(*window).x);
		std::string ypos = std::to_string(sf::Mouse::getPosition(*window).y);
		text.setString("Mouse: " + xpos + ", " + ypos);*/
	}
}

// Render level
void Level::render()
{
	beginDraw();
	elasticString.Draw();
	window->draw(Bar);
	window->draw(text);
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}