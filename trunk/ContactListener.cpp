#include "ContactListener.h"
#include "AbstractPhysics.h"

//=====================================================================

CContactListener::CContactListener(void)
{
}

//=====================================================================

CContactListener::~CContactListener(void)
{
}

//=====================================================================

void CContactListener::BeginContact(b2Contact* contact) 
{
	if(contact->GetFixtureA()->GetUserData() != 0L)
	{
		CAbstractPhysics* elemA = (CAbstractPhysics*)contact->GetFixtureA()->GetUserData();
		elemA->do_beginContact(contact);
	}

	if(contact->GetFixtureB()->GetUserData() != 0L)
	{
		CAbstractPhysics* elemB = (CAbstractPhysics*)contact->GetFixtureB()->GetUserData();
		elemB->do_beginContact(contact);
	}
}

//=====================================================================

void CContactListener::EndContact(b2Contact* contact) 
{
	if(contact->GetFixtureA()->GetUserData() != 0L)
	{
		CAbstractPhysics* elemA = (CAbstractPhysics*)contact->GetFixtureA()->GetUserData();
		elemA->do_endContact(contact);
	}

	if(contact->GetFixtureB()->GetUserData() != 0L)
	{
		CAbstractPhysics* elemB = (CAbstractPhysics*)contact->GetFixtureB()->GetUserData();
		elemB->do_endContact(contact);
	}
} 

//=====================================================================

void CContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) 
{
	if(contact->GetFixtureA()->GetUserData() != 0L)
	{
		CAbstractPhysics* elemA = (CAbstractPhysics*)contact->GetFixtureA()->GetUserData();
		elemA->do_preSolve(contact, oldManifold);
	}

	if(contact->GetFixtureB()->GetUserData() != 0L)
	{
		CAbstractPhysics* elemB = (CAbstractPhysics*)contact->GetFixtureB()->GetUserData();
		elemB->do_preSolve(contact, oldManifold);
	}
}

//=====================================================================

void CContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) 
{
	if(contact->GetFixtureA()->GetUserData() != 0L)
	{
		CAbstractPhysics* elemA = (CAbstractPhysics*)contact->GetFixtureA()->GetUserData();
		elemA->do_postSolve(contact, impulse);
	}

	if(contact->GetFixtureB()->GetUserData() != 0L)
	{
		CAbstractPhysics* elemB = (CAbstractPhysics*)contact->GetFixtureB()->GetUserData();
		elemB->do_postSolve(contact, impulse);
	}
}

//=====================================================================

