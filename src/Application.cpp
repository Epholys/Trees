#include "Application.hpp"


//------------------------------------------------------------------------------
// *** constructor: ***

Application::Application()
	: window_(sf::VideoMode(800, 600), "TREE")
	, tree_()
{
	tree_ = Tree(0, sf::Vector2f(400,575));
}


//------------------------------------------------------------------------------
// *** public functions: ***

void Application::run()
{
	while(window_.isOpen())
	{
		sf::Event event;

		while(window_.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window_.close();
			}
			if(event.type == sf::Event::KeyPressed)
			{
				switch(event.key.code)
				{
				case sf::Keyboard::Space:
				{
					tree_ = Tree(0, sf::Vector2f(400, 575));
					break;
				}

				case sf::Keyboard::Return:
					tree_.grow();
					break;

				default:
					break;
				}
			}
		}
		
		render();
	}
}


//------------------------------------------------------------------------------
// *** private function: ***

void Application::render()
{
	window_.clear();
	window_.draw(tree_);
	window_.display();
}
