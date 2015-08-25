#include "BallElement.h"
#include "IMApplication.h"

#include <ClanLib/display.h>

//=====================================================================

CBallElement::CBallElement() : CAbstractElement(Ball), simulation_(false)
{
	collisionBody_ = CL_CollisionOutline("Resources/Image/tennis-ball.png");	
	collisionBody_.set_alignment(origin_center);

	sprite_ = CL_Sprite(IMApplication::getInstance().gameWorld()->gc(), "ball_sprite", 
		IMApplication::getInstance().resources());

	physics_ = BallPhysics(new CBallPhysics(sprite_.get_width() / 2));
}

//=====================================================================

CBallElement::~CBallElement(void)
{
}

//=====================================================================

void CBallElement::startSimulation(const PhysicsWorld &world)
{
	world->addElement(physics_, position_.x, position_.y);
	simulation_ = true;
}

//=====================================================================

void CBallElement::stopSimulation(const PhysicsWorld &world)
{	
	simulation_ = false;
	sprite_.set_angle(angle_);
	collisionBody_.set_angle(angle_);
	world->removeElement(physics_);
}

//=====================================================================

void CBallElement::draw()
{
	if(simulation_)
	{
		sprite_.set_angle(CL_Angle::from_degrees(physics_->rotation()));
		sprite_.draw(IMApplication::getInstance().gameWorld()->gc(), physics_->positionX(), physics_->positionY());
	
	} else
	{		
		sprite_.draw(IMApplication::getInstance().gameWorld()->gc(), position_.x, position_.y);
	}
}

//=====================================================================

