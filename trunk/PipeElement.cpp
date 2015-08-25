#include "PipeElement.h"
#include "IMApplication.h"

#include <ClanLib/display.h>

//=====================================================================

CPipeElement::CPipeElement() : CAbstractElement(Pipe), simulation_(false)
{
	collisionBody_ = CL_CollisionOutline("Resources/Image/pipe_outline.png");	
	collisionBody_.set_alignment(origin_center);

	sprite_ = CL_Sprite(IMApplication::getInstance().gameWorld()->gc(), "pipe_sprite", 
		IMApplication::getInstance().resources());

	physics_ = PipePhysics(new CPipePhysics(collisionBody_.get_width(), collisionBody_.get_height(), 0.0f));
}

//=====================================================================

CPipeElement::~CPipeElement(void)
{
}

//=====================================================================

void CPipeElement::startSimulation(const PhysicsWorld &world)
{
	physics_->setRotation(angle_.to_degrees());
	world->addElement(physics_, position_.x, position_.y);
	simulation_ = true;
}

//=====================================================================

void CPipeElement::stopSimulation(const PhysicsWorld &world)
{	
	simulation_ = false;
	sprite_.set_angle(angle_);
	collisionBody_.set_angle(angle_);
	world->removeElement(physics_);
}

//=====================================================================

void CPipeElement::draw()
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

void CPipeElement::setRotation(const CL_Angle &angle) 
{
	CAbstractElement::setRotation(angle);
	sprite_.set_angle(angle);
}

