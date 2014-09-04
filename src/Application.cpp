#include <stdexcept>

#include "Application.hpp"


//------------------------------------------------------------------------------
// *** constructor('s helper): ***

Application::Application()
	: window_(sf::VideoMode(800, 600), "TREE")
	, view_(sf::FloatRect(0,0, 800, 600))
	, mousePosition_(sf::Mouse::getPosition(window_))
	, isPaused_(false)
	, font_()
	, trunkSize_(sf::Vector2f(20, 200))
	, tree_(new Tree(0, sf::Vector2f(400, 575), trunkSize_))
	, randomParams_()
	, menu_()
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

	menu_.reset(new GUI::SliderMenu(font_));
	initTreeMenu();
	initBranchMenu();
	initLeafMenu();
}

void Application::initTreeMenu()
{
	auto index = menu_->addMenu("Tree Parameters");

	menu_->addComponent(
		std::make_shared<GUI::Slider<float>>(trunkSize_.x, 1, font_, "Tree's width"), index);
	menu_->addComponent(
		std::make_shared<GUI::Slider<float>>(trunkSize_.y, 1, font_, "Tree's height"), index);		
}


void Application::initBranchMenu()
{
	auto index = menu_->addMenu("Branches Parameters");

	RandomBranchParameters::SPtr param
		= std::dynamic_pointer_cast<RandomBranchParameters>(randomParams_[Node::Branch]);

	menu_->addComponent(
		std::make_shared<GUI::Slider<float>>(param->minAngle, 1.f, font_, "Min. Angle"), index);
	menu_->addComponent(
		std::make_shared<GUI::Slider<float>>(param->maxAngle, 1.f, font_, "Max. Angle"), index);
	menu_->addComponent(
		std::make_shared<GUI::Slider<unsigned int>>(param->minNSubBranch, 1, font_, "Min. Subbranches"), index);
	menu_->addComponent(
		std::make_shared<GUI::Slider<unsigned int>>(param->maxNSubBranch, 1, font_, "Max. Subbranches"), index);
	menu_->addComponent(
		std::make_shared<GUI::Slider<float>>(param->minSubBranchScale, 0.05f, font_, "Min. Scale"), index);
	menu_->addComponent(
		std::make_shared<GUI::Slider<float>>(param->maxSubBranchScale, 0.05f, font_, "Max. Scale"), index);
		
}

void Application::initLeafMenu()
{
	auto index = menu_->addMenu("Leaves Parameters");

	RandomLeafParameters::SPtr param
		= std::dynamic_pointer_cast<RandomLeafParameters>(randomParams_[Node::Leaf]);

	menu_->addComponent(
		std::make_shared<GUI::Slider<unsigned int>>(param->minNLeaves, 1, font_, "Min. leaves"), index);
	menu_->addComponent(
		std::make_shared<GUI::Slider<unsigned int>>(param->maxNLeaves, 1, font_, "Max. Leaves"), index);		
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

	/* Everything about revertEvent is a disgusting hack not to worry about
	 * the menu_ messing up with randomParams_'s validity
	 */
	sf::Event revertEvent;

	while(window_.pollEvent(event))
	{
		revertEvent = event;

		if(event.type == sf::Event::Closed)
		{
			window_.close();
		}
		else if(event.type == sf::Event::KeyPressed)
		{
			switch(event.key.code)
			{
			case sf::Keyboard::Space:
				tree_.reset(new Tree(0, sf::Vector2f(400, 575), trunkSize_));
				break;

			case sf::Keyboard::Return:
				tree_->grow(Node::Branch, randomParams_[Node::Branch]);
				break;

			case sf::Keyboard::Left:
				revertEvent.key.code = sf::Keyboard::Right;
				break;

			case sf::Keyboard::Right:
				revertEvent.key.code = sf::Keyboard::Left;
				break;

			case sf::Keyboard::F:
				tree_->grow(Node::Leaf, randomParams_[Node::Leaf]);
				break;

			default:
				break;
			}
		}
		else if(event.type == sf::Event::MouseWheelMoved)
		{
			auto delta = event.mouseWheel.delta;
			if(delta>0)
			{
				view_.zoom(0.9f);
			}
			else if(delta<0)
			{
				view_.zoom(1.1f);
			}
		}
		else if(event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left)
		{
			mousePosition_ = sf::Mouse::getPosition(window_);
		}
		else if(event.type == sf::Event::GainedFocus)
		{
			isPaused_ = false;
		}
		else if(event.type == sf::Event::LostFocus)
		{
			isPaused_ = true;
		}

		menu_->handleEvent(event);
		for(const auto& param : randomParams_)
			if(!param->checkValidity())
				menu_->handleEvent(revertEvent);
	}

	if(!isPaused_ &&
	   sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i newMousePosition = sf::Mouse::getPosition(window_);

		if(newMousePosition.y > 0 &&
		   newMousePosition.y < window_.getSize().y &&
		   newMousePosition.x > 0 &&
		   newMousePosition.x < window_.getSize().x)
		{
			sf::Vector2i mouseDelta = mousePosition_ - newMousePosition;
	
			float zoom = view_.getSize().x / window_.getSize().x;

			view_.move(sf::Vector2f(mouseDelta) * zoom);
			mousePosition_ = newMousePosition;
	   }
	}	
}

void Application::render()
{
	window_.setView(view_);
	window_.draw(*tree_);

	window_.setView(window_.getDefaultView());
	window_.draw(*menu_);

	window_.display();
	window_.clear(sf::Color::White);


}
