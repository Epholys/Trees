#ifndef APPLICATION_HPP
#define APPLICATION_HPP


#include <SFML/Graphics.hpp>

#include "Tree.hpp"

class Application
{
public:
	Application();

	void run();

private:
	void handleInput();
	void render();

private:
	sf::RenderWindow window_;

	Tree::Ptr tree_;
};



#endif
