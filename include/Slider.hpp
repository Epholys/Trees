#ifndef GUI_SLIDER_HPP
#define GUI_SLIDER_HPP


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
		typedef std::shared_ptr<Slider> Ptr;

	public:
		Slider();
		Slider(T& var, const T& increment, const sf::Font& font);
		
		virtual bool isSelectable();

		virtual void handleEvent(const sf::Event& event);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		T& variable_;
		T increment_;

		sf::RectangleShape backRectangle_;
		sf::Text varText_;
	};

}

#include "Slider.inl"

#endif // GUI_SLIDER_HPP
