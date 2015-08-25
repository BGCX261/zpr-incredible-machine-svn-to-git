#include "AntigravityPhysics.h"

using namespace std;

//=====================================================================

CAntigravityPhysics::CAntigravityPhysics(int width, int height, int influenceHeight) 
	: width_(width / 100.0f), height_(height / 100.0f), 
	  influenceHeight_(influenceHeight / 100.0f), sensor_(0L)  
{
}

//=====================================================================

CAntigravityPhysics::~CAntigravityPhysics(void)
{
}

//=====================================================================

void CAntigravityPhysics::do_addToWorld(b2World *world, const b2Vec2 &pos)
{
	b2PolygonShape shape;
	shape.SetAsBox(width_ / 2.0f, height_ / 2.0f);
	
	b2BodyDef bd;
	bd.position.Set(pos.x, pos.y);
					
	body_ = world->CreateBody(&bd);
	body_->CreateFixture(&shape, 0.0f);
	body_->SetUserData((void *)this);
	
	b2PolygonShape box;
	box.SetAsBox(width_ / 2.0f, height_ / 2.0f);
	body_->CreateFixture(&box, 0.0f);

	b2PolygonShape sensor;
	sensor.SetAsBox(width_ / 2.0f, influenceHeight_ / 2.0f, b2Vec2(0.0f, influenceHeight_ / 2.0f), 0.0f);
	
	b2FixtureDef fd;
	fd.shape = &sensor;
	fd.isSensor = true;
	sensor_ = body_->CreateFixture(&fd);
	sensor_->SetUserData((void *)this);
}

//=====================================================================

void CAntigravityPhysics::do_removeFromWorld(b2World *world)
{
	world->DestroyBody(body_);
	body_ = 0L;
	sensor_ = 0L;
	influencedBodies_.clear();
}

//=====================================================================

void CAntigravityPhysics::do_beginContact(b2Contact* contact)
{
	if(contact->GetFixtureA() == sensor_)
	{
		influencedBodies_.insert(contact->GetFixtureB()->GetBody());
	
	} else
	{		
		influencedBodies_.insert(contact->GetFixtureA()->GetBody());
	}
}

//=====================================================================

void CAntigravityPhysics::do_endContact(b2Contact* contact) 
{
	if(contact->GetFixtureA() == sensor_)
	{
		influencedBodies_.erase(contact->GetFixtureB()->GetBody());
	
	} else
	{		
		influencedBodies_.erase(contact->GetFixtureA()->GetBody());
	}
}

//=====================================================================

void CAntigravityPhysics::do_step()
{
	set<b2Body*>::iterator it = influencedBodies_.begin();

	while(it != influencedBodies_.end())
	{
		(*it)->ApplyForce((*it)->GetMass() * b2Vec2(0.0f, 20.0f), (*it)->GetPosition());
		++it;
	}
}