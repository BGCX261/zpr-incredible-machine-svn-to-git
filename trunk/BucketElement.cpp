#include "BucketElement.h"
#include "IMApplication.h"

#include <ClanLib/display.h>

//=====================================================================

CBucketElement::CBucketElement() : CAbstractElement(Bucket), simulation_(false)
{
	collisionBody_ = CL_CollisionOutline("Resources/Image/bucket_outline.png");	
	collisionBody_.set_alignment(origin_center);

	sprite_ = CL_Sprite(IMApplication::getInstance().gameWorld()->gc(), "bucket_sprite", 
		IMApplication::getInstance().resources());

	physics_ = BucketPhysics(new CBucketPhysics(collisionBody_.get_width(), collisionBody_.get_height(), 0.0f));
}

//=====================================================================

CBucketElement::~CBucketElement(void)
{
}

//=====================================================================

void CBucketElement::startSimulation(const PhysicsWorld &world)
{
	physics_->setRotation(angle_.to_degrees());
	world->addElement(physics_, position_.x, position_.y);
	simulation_ = true;
}

//=====================================================================

void CBucketElement::stopSimulation(const PhysicsWorld &world)
{	
	simulation_ = false;
	sprite_.set_angle(angle_);
	collisionBody_.set_angle(angle_);
	world->removeElement(physics_);
}

//=====================================================================

void CBucketElement::draw()
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

void CBucketElement::setRotation(const CL_Angle &angle) 
{
	CAbstractElement::setRotation(angle);
	sprite_.set_angle(angle);
}

//=====================================================================

bool CBucketElement::update()
{
	return physics_->isElementInside();
}

//=====================================================================

