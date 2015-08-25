#pragma once

#include <Box2D/Box2D.h>
#include <boost/shared_ptr.hpp>

#include "AbstractPhysics.h"

class CContactListener;

//=====================================================================

class CPhysicsWorld;
typedef boost::shared_ptr<CPhysicsWorld> PhysicsWorld;

//=====================================================================

/** 
 * Klasa swiata symulacji
 * 
 * Dostarcza interfejsu do dodawania i usuwania elementów oraz
 * do przeprowadzania symulacji.
 *
 * Opakowanie biblioteki Box2D
 */
class CPhysicsWorld
{
public:
	CPhysicsWorld(void);
	~CPhysicsWorld(void);

	void addElement(const AbstractPhysics &element, float x, float y);
	void removeElement(const AbstractPhysics &element);

	void step();

private:
	b2World *world_;
	CContactListener *contactListener_;
};

//=====================================================================

