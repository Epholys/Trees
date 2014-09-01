#ifndef GUI_SLIDER_HPP
#define GUI_SLIDER_HPP


#include <string>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "Component.hpp"

namespace GUI
{
	template <typename T>
	class Slider : public Component
	{
	public:
		typedef T Type;
		typedef std::shared_ptr<Slider> SPtr;

	public:
		Slider();
		Slider(T& var,
			   const T& increment,
			   const sf::Font& font,
			   const std::string& name);
		
		virtual bool isSelectable();
		virtual void select();
		virtual void deselect();

		virtual void handleEvent(const sf::Event& event);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setName(const std::string& name);
		void updateText();

	private:
		T& variable_;
		T increment_;
	
		sf::RectangleShape backRectangle_;
		sf::Text varValue_;
		sf::Text varName_;
	};

}

#include "Slider.inl"

#endif // GUI_SLIDER_HPP
