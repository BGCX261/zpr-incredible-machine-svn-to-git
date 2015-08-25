#include "AntigravityElement.h"
#include "IMApplication.h"

#include <ClanLib/display.h>

//=====================================================================

CAntigravityElement::CAntigravityElement() : CAbstractElement(Antigravity), simulation_(false)
{
	collisionBody_ = CL_CollisionOutline("Resources/Image/antigravity_no.png");	
	collisionBody_.set_alignment(origin_center);

	sprite_ = CL_Sprite(IMApplication::getInstance().gameWorld()->gc(), "antigravity_sprite", 
		IMApplication::getInstance().resources());

	sprite_.finish();

	physics_ = AntigravityPhysics(new CAntigravityPhysics(sprite_.get_width(), sprite_.get_height(), sprite_.get_height() * 10));
}

//=====================================================================

CAntigravityElement::~CAntigravityElement(void)
{
}

//=====================================================================

void CAntigravityElement::startSimulation(const PhysicsWorld &world)
{
	world->addElement(physics_, position_.x, position_.y);
	simulation_ = true;
}

//=====================================================================

void CAntigravityElement::stopSimulation(const PhysicsWorld &world)
{	
	simulation_ = false;
	sprite_.set_angle(angle_);
	collisionBody_.set_angle(angle_);
	world->removeElement(physics_);

	sprite_.finish();
}

//=====================================================================

void CAntigravityElement::draw()
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

bool CAntigravityElement::update()
{
	sprite_.update();

	if(sprite_.is_finished() && physics_->isActive() && simulation_)
	{
		sprite_.restart();
	}

	return false;
}

//=====================================================================
