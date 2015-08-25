#include "SpringBoardPhysics.h"

//=====================================================================

CSpringBoardPhysics::CSpringBoardPhysics(int width, int height, float angle)
	: width_(width / 100.0f), height_(height / 100.0f), 
	  angle_(-b2_pi * angle / 180.0f), sensor_(0L), bounce_(false)
{
}

//=====================================================================

CSpringBoardPhysics::~CSpringBoardPhysics(void)
{
}

//=====================================================================

void CSpringBoardPhysics::do_addToWorld(b2World *world, const b2Vec2 &pos)
{	
	b2BodyDef bd;
	bd.position.Set(pos.x, pos.y);
	bd.angle = angle_;					
	body_ = world->CreateBody(&bd);

	b2PolygonShape bshape;
	bshape.SetAsBox(width_ / 2.0f, height_ / 2.0f);
	body_->CreateFixture(&bshape, 0.0f);

	b2PolygonShape sshape;
	sshape.SetAsEdge(b2Vec2(-width_ / 2.0f, height_ / 2.0f), 
						b2Vec2(width_ / 2.0f, height_ / 2.0f));
	sensor_ = body_->CreateFixture(&sshape, 0.0f);
	sensor_->SetUserData((void *)this);
}

//=====================================================================

void CSpringBoardPhysics::do_removeFromWorld(b2World *world)
{
	world->DestroyBody(body_);
	body_ = 0L;
	sensor_ = 0L;
}

//=====================================================================

void CSpringBoardPhysics::do_postSolve(b2Contact* contact, const b2ContactImpulse* impulse) 
{ 
	b2Body *body;

	if(contact->GetFixtureA() == sensor_)
	{
		body = contact->GetFixtureB()->GetBody();
	
	} else
	{		
		body = contact->GetFixtureA()->GetBody();
	}

	float32 imp = impulse->normalImpulses[0] < 0.1f ? 0.1f : impulse->normalImpulses[0];
	imp = imp > 0.25f ? 0.25f : imp;
	
	body->ApplyLinearImpulse(1.01f * imp * b2Vec2(sinf(-angle_), cosf(-angle_)), 
								body->GetPosition());

	bounce_ = true;
}

//=====================================================================

bool CSpringBoardPhysics::bounce() 
{
	bool ret = bounce_;
	bounce_ = false;
	
	return ret;
}