#include "RampElement.h"
#include "IMApplication.h"

#include <ClanLib/display.h>

//=====================================================================

CRampElement::CRampElement() : CAbstractElement(Ramp), simulation_(false)
{
	collisionBody_ = CL_CollisionOutline("Resources/Image/ramp.png");	
	collisionBody_.set_alignment(origin_center);

	sprite_ = CL_Sprite(IMApplication::getInstance().gameWorld()->gc(), "ramp_sprite", 
		IMApplication::getInstance().resources());

	physics_ = RampPhysics(new CRampPhysics(sprite_.get_width(), sprite_.get_height(), 0.0f));
}

//=====================================================================

CRampElement::~CRampElement(void)
{
}

//=====================================================================

void CRampElement::startSimulation(const PhysicsWorld &world)
{
	physics_->setRotation(angle_.to_degrees());
	world->addElement(physics_, position_.x, position_.y);
	simulation_ = true;
}

//=====================================================================

void CRampElement::stopSimulation(const PhysicsWorld &world)
{	
	simulation_ = false;
	sprite_.set_angle(angle_);
	collisionBody_.set_angle(angle_);
	world->removeElement(physics_);
}

//=====================================================================

void CRampElement::draw()
{
	if(simulation_)
	{
		sprite_.draw(IMApplication::getInstance().gameWorld()->gc(), physics_->positionX(), physics_->positionY());
	
	} else
	{		
		sprite_.draw(IMApplication::getInstance().gameWorld()->gc(), position_.x, position_.y);
	}
}

//=====================================================================

void CRampElement::setRotation(const CL_Angle &angle) 
{
	CAbstractElement::setRotation(angle);
	sprite_.set_angle(angle);
}

//=====================================================================