#include <algorithm>

#include "SliderMenu.hpp"


namespace GUI
{
	SliderMenu::SliderMenu()
		: mainSlider_()
		, index_(0)
		, hasFirstMenu_(false)
		, menus_()
		, menuNames_()
	{
	}

	SliderMenu::SliderMenu(const sf::Font& font)
		: mainSlider_()
		, index_(0)
		, hasFirstMenu_(false)
		, menus_()
		, menuNames_()
	{
		mainSlider_.reset(new Slider<int>(index_, 1, font, ""));

		menus_.push_back(std::vector<Component::SPtr>(1, mainSlider_));
		menus_[index_].front()->select();
		menuNames_[index_] = "";
	}


//------------------------------------------------------------------------------

	int SliderMenu::addMenu(const std::string& name)
	{
		if(!hasFirstMenu_)
		{
			menuNames_[index_] = name;
			hasFirstMenu_ = true;
			mainSlider_->setName(menuNames_[index_]);
			return index_;
		}
		else
		{
			menus_.push_back(std::vector<Component::SPtr>(1, mainSlider_));
			menuNames_[menus_.size()-1] = name;
			return menus_.size()-1;
		}
	}

	void SliderMenu::addComponent(Component::SPtr comp, std::size_t index)
	{
		assert(index < menus_.size());

		// Here is the Slider-dependent magic variable
		comp->move(0.f, 25.f * menus_[index].size());

		menus_[index].push_back(comp);
	}

//------------------------------------------------------------------------------


	auto SliderMenu::findComponentSelected()
	{
		auto it = std::find_if(menus_[index_].begin(),
							   menus_[index_].end(),
							   [](Component::SPtr comp)
							   {
								   return comp->isSelected();
							   });
		assert(it != menus_[index_].end());

		return it;
	}

	void SliderMenu::selectNextComponent()
	{
		auto it = findComponentSelected();
		auto itSave = it;
			
		do
		{
			++it;
		}while (it != menus_[index_].end() && !((*it)->isSelectable()));
			
		if (it != menus_[index_].end())
		{
			(*itSave)->deselect();
			(*it)->select();
		}
	}

	void SliderMenu::selectPreviousComponent()
	{
		auto it = findComponentSelected();
		auto itSave = it;

		do
		{
			--it;
		}while (it != menus_[index_].begin()-1 && !((*it)->isSelectable()));
 
		if (it != menus_[index_].begin() -1)
		{
			(*itSave)->deselect();
			(*it)->select();
		}
	}


//------------------------------------------------------------------------------

	bool SliderMenu::isSelectable()
	{
		return false;
	}

	void SliderMenu::handleEvent(const sf::Event& event)
	{
		if(event.type == sf::Event::KeyPressed)
		{
			switch(event.key.code)
			{
			case sf::Keyboard::Down:
				selectNextComponent();
				break;				

			case sf::Keyboard::Up:
				selectPreviousComponent();
				break;

			default:
				auto it = findComponentSelected();
				(*it)->handleEvent(event);
				
				index_ = index_ % menus_.size();
				mainSlider_->updateText();
				
				mainSlider_->setName(menuNames_[index_]);
				break;
			}
		}
	}


//------------------------------------------------------------------------------

	void SliderMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		for(const auto& component : menus_[index_])
		{
			target.draw(*component, states);
		}
	}

}















