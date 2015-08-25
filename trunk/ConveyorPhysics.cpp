#include "ConveyorPhysics.h"

//=====================================================================

CConveyorPhysics::CConveyorPhysics(int width, int height, float conveyorSpeed) 
	: width_(width / 100.0f), height_(height / 100.0f), 
	  conveyorSpeed_(conveyorSpeed) 
{
}

//=====================================================================

CConveyorPhysics::~CConveyorPhysics(void)
{
}

//=====================================================================

void CConveyorPhysics::do_addToWorld(b2World *world, const b2Vec2 &pos)
{
	b2PolygonShape shape;
	shape.SetAsBox(width_ / 2.0f, height_ / 2.0f);
	shape.conveyorSpeed = conveyorSpeed_;
	
	b2BodyDef bd;
	bd.position.Set(pos.x, pos.y);
					
	body_ = world->CreateBody(&bd);
	body_->CreateFixture(&shape, 0.0f);
}

//=====================================================================

void CConveyorPhysics::do_removeFromWorld(b2World *world)
{
	world->DestroyBody(body_);
	body_ = 0L;
}

//=====================================================================
