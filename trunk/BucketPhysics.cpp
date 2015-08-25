#include "BucketPhysics.h"

//=====================================================================

CBucketPhysics::CBucketPhysics(int width, int height, float angle) 
	: width_(width / 100.0f), height_(height / 100.0f), 
	  angle_(-b2_pi * angle / 180.0f), sensor_(0L), elementInside_(false)
{
}

//=====================================================================

CBucketPhysics::~CBucketPhysics(void)
{
}

//=====================================================================

void CBucketPhysics::do_addToWorld(b2World *world, const b2Vec2 &pos)
{	
	elementInside_ = false;

	b2BodyDef bd;
	bd.position.Set(pos.x, pos.y);
	bd.angle = angle_;					
	body_ = world->CreateBody(&bd);	

	b2PolygonShape lshape;
	lshape.SetAsEdge(b2Vec2(-width_ / 2.0f, height_ / 2.0f), 
						b2Vec2(-width_ / 2.0f, -height_ / 2.0f));
	body_->CreateFixture(&lshape, 0.0f);

	b2PolygonShape rshape;
	rshape.SetAsEdge(b2Vec2(width_ / 2.0f, height_ / 2.0f), 
						b2Vec2(width_ / 2.0f, -height_ / 2.0f));
	body_->CreateFixture(&rshape, 0.0f);

	b2PolygonShape bshape;
	bshape.SetAsEdge(b2Vec2(-width_ / 2.0f, -height_ / 2.0f), 
						b2Vec2(width_ / 2.0f, -height_ / 2.0f));
	body_->CreateFixture(&bshape, 0.0f);

	b2PolygonShape sensor;
	sensor.SetAsBox(width_ / 2.0f - 0.02f, height_ / 4.0f, b2Vec2(0.0f, -height_ / 4.0f + 0.02f), 0.0f);
	
	b2FixtureDef fd;
	fd.shape = &sensor;
	fd.isSensor = true;
	sensor_ = body_->CreateFixture(&fd);
	sensor_->SetUserData((void *)this);
}

//=====================================================================

void CBucketPhysics::do_removeFromWorld(b2World *world)
{
	elementInside_ = false;
	world->DestroyBody(body_);
	body_ = 0L;
	sensor_ = 0L;
}

//=====================================================================

void CBucketPhysics::do_beginContact(b2Contact* contact)
{
	elementInside_ = true;
}

//=====================================================================

void CBucketPhysics::do_endContact(b2Contact* contact) 
{
	elementInside_ = false;
}

//=====================================================================
