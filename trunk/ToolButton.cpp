#include "ToolButton.h"
#include "IMApplication.h"

using namespace std;

//=====================================================================
	
CToolButton::CToolButton(const std::string& name) 
	: name_(name), mouseDown_(false), enabled_(true)
{
	outline_ = CL_CollisionOutline("Resources/Image/" + name + ".png");	
	outline_.set_alignment(origin_center);

	normalView_ = new CL_Sprite(IMApplication::getInstance().gameWorld()->gc(), name, 
		IMApplication::getInstance().resources());

	hoverView_ = new CL_Sprite(IMApplication::getInstance().gameWorld()->gc(), name + "_hover", 
		IMApplication::getInstance().resources());

	clickedView_ = new CL_Sprite(IMApplication::getInstance().gameWorld()->gc(), name + "_on", 
		IMApplication::getInstance().resources());

	disabledView_ = new CL_Sprite(IMApplication::getInstance().gameWorld()->gc(), name + "_disable", 
		IMApplication::getInstance().resources());

	currentView_ = normalView_;
}

//=====================================================================
	
CToolButton::~CToolButton(void)
{
	delete normalView_;
	delete hoverView_;
	delete clickedView_;
	delete disabledView_;
}

//=====================================================================
	
bool CToolButton::mouseDown(const CL_Point &pos)
{
	if(!enabled_)
		return false;

	if(!outline_.point_inside(CL_Pointf(float(pos.x), float(pos.y))))
	{
		return false;
	}

	currentView_ = clickedView_;
	mouseDown_ = true;

	return true;
}

//=====================================================================
	
void CToolButton::mouseMove(const CL_Point &pos)
{
	if(!enabled_ || mouseDown_)
		return;

	if(outline_.point_inside(CL_Pointf(float(pos.x), float(pos.y))))
	{
		currentView_ = hoverView_;
	
	} else
	{
		currentView_ = normalView_;
	}
}

//=====================================================================
	
void CToolButton::mouseUp  (const CL_Point &pos)
{
	if(!enabled_)
		return;

	if(outline_.point_inside(CL_Pointf(float(pos.x), float(pos.y))))
	{
		if(mouseDown_)
		{
			mouseDown_ = false;
			currentView_ = hoverView_;
		}

	} else
	{
		if(mouseDown_)
		{
			mouseDown_ = false;
			currentView_ = normalView_;
		}
	}
}

//=====================================================================
	
void CToolButton::setPosition(const CL_Point &pos)
{
	position_ = pos;
	outline_.set_translation(float(pos.x), float(pos.y));
}

//=====================================================================
	
void CToolButton::setEnabled(bool value)
{
	enabled_ = value;

	if(enabled_)
	{
		currentView_ = normalView_;
	
	} else
	{
		currentView_ = disabledView_;
	}
}

//=====================================================================
	
void CToolButton::draw()
{
	currentView_->draw(IMApplication::getInstance().gameWorld()->gc(), position_.x, position_.y);
}