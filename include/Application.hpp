#ifndef APPLICATION_HPP
#define APPLICATION_HPP


#include <SFML/Graphics.hpp>

#include "Tree.hpp"
#include "SliderMenu.hpp"
#include "RandomParameters.hpp"

class Application
{
public:
	Application();

	void run();

private:
	void initTreeMenu();
	void initBranchMenu();
	void initLeafMenu();

	void handleInput();
	void render();

private:
	sf::RenderWindow window_;
	sf::View view_;

	sf::Font font_;

	sf::Vector2f trunkSize_;
	Tree::Ptr tree_;

	std::array<RandomParameters::SPtr, Node::TypeCount> randomParams_;
	GUI::SliderMenu::SPtr menu_;
};



#endif
