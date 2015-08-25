#include "PhysicsWorld.h"
#include "ContactListener.h"

CPhysicsWorld::CPhysicsWorld(void)
{
	contactListener_ = new CContactListener;

	b2Vec2 gravity(0.0f, -10.0f);
	world_ = new b2World(gravity, true);
	world_->SetContactListener(contactListener_);
}

//=====================================================================

CPhysicsWorld::~CPhysicsWorld(void)
{
	delete world_;
	delete contactListener_;
}

//=====================================================================

void CPhysicsWorld::addElement(const AbstractPhysics &element, float x, float y)
{
	element->do_addToWorld(world_, b2Vec2(x / 100.0f, -y / 100.0f));
}

//=====================================================================

void CPhysicsWorld::removeElement(const AbstractPhysics &element)
{
	element->do_removeFromWorld(world_);
}

//=====================================================================

void CPhysicsWorld::step(void)
{
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6; 
	int32 positionIterations = 2;

	world_->Step(timeStep, velocityIterations, positionIterations);
	world_->ClearForces();

	b2Body *body;
	for(body = world_->GetBodyList(); body != 0L; body = body->GetNext())
	{
		if(body->GetUserData() != 0L)
		{
			((CAbstractPhysics*)body->GetUserData())->do_step();
		}
	}

}

//=====================================================================

