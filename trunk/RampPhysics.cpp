#include "RampPhysics.h"

//=====================================================================

CRampPhysics::CRampPhysics(int width, int height, float angle) 
	: width_(width / 100.0f), height_(height / 100.0f), 
	  angle_(-b2_pi * angle / 180.0f)
{
}

//=====================================================================

CRampPhysics::~CRampPhysics(void)
{
}

//=====================================================================

void CRampPhysics::do_addToWorld(b2World *world, const b2Vec2 &pos)
{
	b2PolygonShape shape;
	shape.SetAsBox(width_ / 2.0f, height_ / 2.0f);
	
	b2BodyDef bd;
	bd.position.Set(pos.x, pos.y);
	bd.angle = angle_;
					
	body_ = world->CreateBody(&bd);
	body_->CreateFixture(&shape, 0.0f);
}

//=====================================================================

void CRampPhysics::do_removeFromWorld(b2World *world)
{
	world->DestroyBody(body_);
	body_ = 0L;
}

//=====================================================================
