#include "PipePhysics.h"

//=====================================================================

CPipePhysics::CPipePhysics(int width, int height, float angle) 
	: width_(width / 100.0f), height_(height / 100.0f), 
	  angle_(-b2_pi * angle / 180.0f)
{
}

//=====================================================================

CPipePhysics::~CPipePhysics(void)
{
}

//=====================================================================

void CPipePhysics::do_addToWorld(b2World *world, const b2Vec2 &pos)
{	
	b2BodyDef bd;
	bd.position.Set(pos.x, pos.y);
	bd.angle = angle_;					
	body_ = world->CreateBody(&bd);	

	b2PolygonShape tshape;
	tshape.SetAsEdge(b2Vec2(-width_ / 2.0f, height_ / 2.0f), 
						b2Vec2(width_ / 2.0f, height_ / 2.0f));
	body_->CreateFixture(&tshape, 0.0f);

	b2PolygonShape bshape;
	bshape.SetAsEdge(b2Vec2(-width_ / 2.0f, -height_ / 2.0f), 
						b2Vec2(width_ / 2.0f, -height_ / 2.0f));
	body_->CreateFixture(&bshape, 0.0f);
}

//=====================================================================

void CPipePhysics::do_removeFromWorld(b2World *world)
{
	world->DestroyBody(body_);
	body_ = 0L;
}

//=====================================================================
