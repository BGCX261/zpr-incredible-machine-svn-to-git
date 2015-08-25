#include "SpringBoardElement.h"
#include "IMApplication.h"

#include <ClanLib/display.h>

//=====================================================================

CSpringBoardElement::CSpringBoardElement() : CAbstractElement(SpringBoard), simulation_(false)
{
	collisionBody_ = CL_CollisionOutline("Resources/Image/spring_outline.png");	
	collisionBody_.set_alignment(origin_center);

	sprite_ = CL_Sprite(IMApplication::getInstance().gameWorld()->gc(), "springboard_sprite", 
		IMApplication::getInstance().resources());

	sprite_.finish();

	physics_ = SpringBoardPhysics(new CSpringBoardPhysics(collisionBody_.get_width(), collisionBody_.get_height(), 0.0f));
}

//=====================================================================

CSpringBoardElement::~CSpringBoardElement(void)
{
}

//=====================================================================

void CSpringBoardElement::startSimulation(const PhysicsWorld &world)
{
	physics_->setRotation(angle_.to_degrees());
	world->addElement(physics_, position_.x, position_.y);
	simulation_ = true;
}

//=====================================================================

void CSpringBoardElement::stopSimulation(const PhysicsWorld &world)
{	
	simulation_ = false;
	sprite_.set_angle(angle_);
	collisionBody_.set_angle(angle_);
	world->removeElement(physics_);

	sprite_.finish();
}

//=====================================================================

void CSpringBoardElement::draw()
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

bool CSpringBoardElement::update()
{
	sprite_.update();

	if(sprite_.is_finished() && physics_->bounce() && simulation_)
	{
		sprite_.restart();
	}

	return false;
}

//=====================================================================

void CSpringBoardElement::setRotation(const CL_Angle &angle) 
{
	CAbstractElement::setRotation(angle);
	sprite_.set_angle(angle);
}