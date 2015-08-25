#include "BallPhysics.h"

//=====================================================================

CBallPhysics::CBallPhysics(int radius) 
	: radius_(radius / 100.0f)
{
}

//=====================================================================

CBallPhysics::~CBallPhysics(void)
{
}

//=====================================================================

void CBallPhysics::do_addToWorld(b2World *world, const b2Vec2 &pos)
{	
	b2CircleShape shape;
	shape.m_radius = radius_;

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(pos.x, pos.y);

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 1.0f;
	fd.restitution = 0.5f;
	fd.friction = 1.0f;

	body_ = world->CreateBody(&bd);
	body_->CreateFixture(&fd);
}

//=====================================================================

void CBallPhysics::do_removeFromWorld(b2World *world)
{
	world->DestroyBody(body_);
	body_ = 0L;
}

//=====================================================================
