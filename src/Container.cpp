// #include "Container.hpp"


// namespace GUI
// {
// 	Container::Container()
// 		: Component()
// 		, children_()
// 		, hasSelection_(false)
// 	{
// 	}


// //-------------------------------------------------------------------------------

// 	Container::pack(Component::Ptr comp)
// 	{
// 		children_.push_back(comp);
// 		if(!hasSelection_ && comp->isSelectable())
// 		{
// 			hasSelection_ = true;
// 			comp->select();
// 		}
// 	}


// //-------------------------------------------------------------------------------   

// 	bool Container::isSelectable()
// 	{
// 		return false;
// 	}

	

// //-------------------------------------------------------------------------------

// 	virtual void draw(RenderTarget& target, RenderStates states) const
// 	{
// 		states.transform *= getTransform();
		
// 		for (const auto& child : children_)
// 		{
// 			child->draw(target, states);
// 		}
// 	}
// }
