#ifndef GUI_COMPONENT_HPP
#define GUI_COMPONENT_HPP


#include <memory>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace GUI
{
	class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
	{
	public:
		typedef	std::shared_ptr<Component> SPtr;
		
	public:
		Component();
		virtual ~Component();

		virtual bool isSelectable() =0;
		bool isSelected() const;
		virtual void select();
		virtual void deselect();
	   
		bool isActive() const;
		virtual void activate();
		virtual void deactivate();
		
		virtual void handleEvent(const sf::Event& event) =0;

	private:
		bool isSelected_;
		bool isActivated_;
	};
}


#endif // GUI_COMPONENT_HPP
