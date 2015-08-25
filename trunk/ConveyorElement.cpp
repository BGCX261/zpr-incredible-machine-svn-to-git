#include "ConveyorElement.h"
#include "IMApplication.h"

#include <ClanLib/display.h>

//=====================================================================

CConveyorElement::CConveyorElement() : CAbstractElement(Conveyor), simulation_(false)
{
	collisionBody_ = CL_CollisionOutline("Resources/Image/conveyor_outline.png");	
	collisionBody_.set_alignment(origin_center);

	sprite_ = CL_Sprite(IMApplication::getInstance().gameWorld()->gc(), "conveyor_sprite", 
		IMApplication::getInstance().resources());
	
	sprite_.finish();

	physics_ = ConveyorPhysics(new CConveyorPhysics(sprite_.get_width(), sprite_.get_height(), 3.0f));
}

//=====================================================================

CConveyorElement::~CConveyorElement(void)
{
}

//=====================================================================

void CConveyorElement::startSimulation(const PhysicsWorld &world)
{
	world->addElement(physics_, position_.x, position_.y);
	simulation_ = true;

	sprite_.restart();
}

//=====================================================================

void CConveyorElement::stopSimulation(const PhysicsWorld &world)
{	
	simulation_ = false;
	sprite_.set_angle(angle_);
	collisionBody_.set_angle(angle_);
	world->removeElement(physics_);

	sprite_.finish();
}

//=====================================================================

void CConveyorElement::draw()
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

bool CConveyorElement::update()
{
	sprite_.update();

	return false;
}

//=====================================================================