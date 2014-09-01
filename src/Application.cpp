#include <stdexcept>

#include "Application.hpp"


//------------------------------------------------------------------------------
// *** constructor('s helper): ***

Application::Application()
	: window_(sf::VideoMode(800, 600), "TREE")
	, font_()
	, tree_(new Tree(0, sf::Vector2f(400, 575)))
	, menu_()
	, randomParams_()
{
	if(!font_.loadFromFile("media/font/FORCEDSQUARE.ttf"))
	{
		throw std::runtime_error("Can't open media/font/FORCEDSQUARE.ttf");
	}

	randomParams_[Node::Branch] = 
		std::make_shared<RandomBranchParameters>(initDefaultBranchParams());
	randomParams_[Node::Leaf] = 
		std::make_shared<RandomLeafParameters>(initDefaultLeafParams());

	RandomBranchParameters::SPtr randBranch =
		std::dynamic_pointer_cast<RandomBranchParameters>(randomParams_[Node::Branch]);


	initMenu();
}

void Application::initMenu()
{
	menu_.reset(new GUI::SliderMenu(font_));
}


//------------------------------------------------------------------------------
// *** public functions: ***

void Application::run()
{
	while(window_.isOpen())
	{
		handleInput();
		
		render();
	}
}



//------------------------------------------------------------------------------
// *** private function: ***

void Application::handleInput()
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
				tree_.reset(new Tree(0, sf::Vector2f(400, 575)));
				break;
			}

			case sf::Keyboard::Return:
				tree_->grow(Node::Branch, randomParams_[Node::Branch]);
				break;

			case sf::Keyboard::F:
				tree_->grow(Node::Leaf, randomParams_[Node::Leaf]);
				break;

			default:
				break;
			}
		}

		menu_->handleEvent(event);
	}
}

void Application::render()
{
	window_.clear(sf::Color::White);
	window_.draw(*tree_);
	window_.draw(*menu_);
	window_.display();
}
