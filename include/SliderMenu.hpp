#ifndef GUI_SLIDERMENU_HPP
#define GUI_SLIDERMENU_HPP


#include <vector>
#include <map>
#include <string>

#include "Assertion.hpp"
#include "Slider.hpp"

namespace GUI
{
	class SliderMenu : public Component
	{
	public:
		SliderMenu();
		explicit SliderMenu(sf::Font font);

		virtual bool isSelectable();

		virtual void handleEvent(const sf::Event& event);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void addMenu(const std::string& name);
		void addComponent(Component::SPtr comp, std::size_t index);

	private:
		auto findComponentSelected();

		void selectNextComponent();
		void selectPreviousComponent();

	private:
		Slider<int>::SPtr mainSlider_;
		int index_;
		bool hasFirstMenu_;

		std::vector< std::vector<Component::SPtr> > menus_;
		std::map<std::size_t, std::string> menuNames_;
	};
}


#endif // GUI_SLIDERMENU_HPP
