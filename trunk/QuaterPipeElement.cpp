#include "QuaterPipeElement.h"
#include "IMApplication.h"

#include <ClanLib/display.h>

//=====================================================================

CQuaterPipeElement::CQuaterPipeElement() : CAbstractElement(QuaterPipe), simulation_(false)
{
	collisionBody_ = CL_CollisionOutline("Resources/Image/qpipe_outline.png");	
	collisionBody_.set_alignment(origin_center);

	sprite_ = CL_Sprite(IMApplication::getInstance().gameWorld()->gc(), "quaterpipe_sprite", 
		IMApplication::getInstance().resources());

	physics_ = QuaterPipePhysics(new CQuaterPipePhysics(collisionBody_.get_height(), 49, 0.0f));
}

//=====================================================================

CQuaterPipeElement::~CQuaterPipeElement(void)
{
}

//=====================================================================

void CQuaterPipeElement::startSimulation(const PhysicsWorld &world)
{
	physics_->setRotation(angle_.to_degrees());
	world->addElement(physics_, position_.x, position_.y);
	simulation_ = true;
}

//=====================================================================

void CQuaterPipeElement::stopSimulation(const PhysicsWorld &world)
{	
	simulation_ = false;
	sprite_.set_angle(angle_);
	collisionBody_.set_angle(angle_);
	world->removeElement(physics_);
}

//=====================================================================

void CQuaterPipeElement::draw()
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

void CQuaterPipeElement::setRotation(const CL_Angle &angle) 
{
	CAbstractElement::setRotation(angle);
	sprite_.set_angle(angle);
}