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

	SliderMenu::SliderMenu(sf::Font font)
		: mainSlider_()
		, index_(0)
		, hasFirstMenu_(false)
		, menus_()
		, menuNames_()
	{
		mainSlider_.reset(new Slider<int>(index_, 1, font, ""));

		menus_.push_back(std::vector<Component::SPtr>(1, mainSlider_));
		menuNames_[index_] = "";
	}


//------------------------------------------------------------------------------

	void SliderMenu::addMenu(const std::string& name)
	{
		if(!hasFirstMenu_)
		{
			menuNames_[index_] = name;
			hasFirstMenu_ = true;
		}
		else
		{
			menus_.push_back(std::vector<Component::SPtr>(1, mainSlider_));
			menuNames_[menus_.size()-1] = name;
		}
	}

	void SliderMenu::addComponent(Component::SPtr comp, std::size_t index)
	{
		assert(index < menus_.size());
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
			while (it != menus_[index_].end() && !((*it)->isSelectable()))
			{
				++it;
			}
			if (it != menus_[index_].end())
			{
				(*it)->select();
				(*itSave)->deselect();
			}
		}

		void SliderMenu::selectPreviousComponent()
		{
			auto it = findComponentSelected();
			auto itSave = it;

			// The first element is always mainSlider_, which is selectable
			while (!((*it)->isSelectable()))
			{
				--it;
			}
			if (it != menus_[index_].end())
			{
				(*it)->select();
				(*itSave)->deselect();
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
			case sf::Keyboard::Up:
				selectNextComponent();
				break;				

			case sf::Keyboard::Down:
				selectPreviousComponent();
				break;

			default:
				auto it = findComponentSelected();
				(*it)->handleEvent(event);
				break;
			}
		}


		index_ = index_ % menus_.size();
		mainSlider_->setName(menuNames_[index_]);
	}


//------------------------------------------------------------------------------

	void SliderMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		for(const auto component : menus_[index_])
		{
			target.draw(*component, states);
		}
	}

}
