#ifndef NODE_HPP
#define NODE_HPP


#include <memory>
#include <functional>
#include <vector>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class Node : public sf::Transformable, public sf::Drawable
{
public:
	typedef std::unique_ptr<Node> Ptr;

	enum Type
	{
		None = 0,
		Branch,
		Leaf,
		TypeCount
	};

public:
	Node();

	virtual void createChildren(Type type);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	virtual	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	std::vector<Ptr> children_;
	std::map<Type, std::function<void()>> growthFunctions_;
};


#endif // NODE_HPP
