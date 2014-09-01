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
		, varValue_()
		, varName_()
	{
	}


	template <typename T>
	Slider<T>::Slider(T& var,
					  const T& increment,
					  const sf::Font& font,
					  const std::string& name)
		: variable_(var)
		, increment_(increment)
		, backRectangle_(sf::Vector2f(50.f, 25.f))
		, varValue_(toString(var), font, 20)
		, varName_(name, font, 20)
	{
		backRectangle_.setFillColor(sf::Color(0, 0, 0, 150));
		

		sf::Vector2f rectSize = backRectangle_.getSize();

		centerOrigin(varValue_);
		varValue_.move(rectSize.x / 2.f, 0.f);
	   
		varName_.setColor(sf::Color::Black);
		varName_.move(rectSize.x + 5.f, -5.f);
	}

//------------------------------------------------------------------------------

	template<typename T>
	bool Slider<T>::isSelectable()
	{
		return true;
	}

	template<typename T>
	void Slider<T>::select()
	{
		Component::select();
		backRectangle_.setFillColor(sf::Color(0, 0, 0, 200));
	}

	template<typename T>	   
    void Slider<T>::deselect()
	{
		Component::deselect();
		backRectangle_.setFillColor(sf::Color(0, 0, 0, 150));
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

			varValue_.setString(toString(variable_));
		}
	}


//------------------------------------------------------------------------------

	template<typename T>
	void Slider<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(backRectangle_, states);
		target.draw(varValue_, states);
		target.draw(varName_, states);
	}


//------------------------------------------------------------------------------

	template<typename T>
	void Slider<T>::setName(const std::string& name)
	{
		varName_.setString(name);
	}

	template<typename T>
	void Slider<T>::updateText()
	{
		varValue_.setString(toString(variable_));
	}


} // namespace GUI
