#ifndef APPLICATION_HPP
#define APPLICATION_HPP


#include <SFML/Graphics.hpp>

#include "Tree.hpp"
#include "Slider.hpp"
#include "RandomParameters.hpp"

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

	sf::Font font_;

	Tree::Ptr tree_;
	GUI::Slider<unsigned int>::SPtr slider_;

	std::array<RandomParameters::SPtr, Node::TypeCount> randomParams_;
};



#endif
