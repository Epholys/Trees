#include "Component.hpp"


namespace GUI
{
// *** constructor & destructor: ***

	Component::Component()
		: isSelected_(false)
		, isActivated_(false)
	{
	}

	Component::~Component()
	{
	}


//--------------------------------------------------------------------------
// *** Selection Fonctions: ***

	bool Component::isSelected() const
	{
		return isSelected_;
	}

	void Component::select()
	{
		isSelected_ = true;
	}

	void Component::deselect()
	{
		isSelected_ = false;
	}


//----------------------------------------------------------------------
// *** Activation Fonctions: ***

	bool Component::isActive() const
	{
		return isActivated_;
	}

	void Component::activate()
	{
		isActivated_ = true;
	}

	void Component::deactivate()
	{
		isActivated_ = false;
	}

} // namespace GUI
