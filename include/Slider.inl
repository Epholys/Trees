#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Slider.hpp"
#include "Utility.hpp"


namespace GUI
{
	template <typename T>
	Slider<T>::Slider()
		: variable_()
		, increment_()
		, backRectangle_()
		, varText_()
	{
	}


	template <typename T>
	Slider<T>::Slider(T& var, const T& increment, const sf::Font& font)
		: variable_(var)
		, increment_(increment)
		, backRectangle_(sf::Vector2f(50.f, 25.f))
		, varText_(toString(var), font, 20)
	{
		backRectangle_.setFillColor(sf::Color(0, 0, 0, 150));
		
		sf::Vector2f position = getPosition();
		varText_.setPosition(position.x / 2.f, position.y / 2.f);
	}

//------------------------------------------------------------------------------

	template<typename T>
	bool Slider<T>::isSelectable()
	{
		return true;
	}

	template<typename T>
	void Slider<T>::handleEvent(const sf::Event& event)
	{
		if(event.type == sf::Event::KeyPressed)
		{
			switch(event.key.code)
			{
			case sf::Keyboard::Right:
				variable_ += increment_;
				break;

			case sf::Keyboard::Left:
				variable_ -= increment_;
				break;

			default:
				break;
			}

			varText_.setString(toString(variable_));
		}
	}


//------------------------------------------------------------------------------

	template<typename T>
	void Slider<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(backRectangle_, states);
		target.draw(varText_, states);
	}
}
