#pragma once

#include <Box2D/Box2D.h>
#include <boost/shared_ptr.hpp>

//=====================================================================

class CAbstractPhysics;
typedef boost::shared_ptr<CAbstractPhysics> AbstractPhysics;

//=====================================================================

/*!
 * \brief
 * Abstrakcyjny model fizyczny elementu
 * 
 * Bazowy model fizyczny element�w, okre�la zachowanie elementu w symulacji.
 * Opakowanie biblioteki Box2D
 */
class CAbstractPhysics
{
	friend class CPhysicsWorld;
	friend class CContactListener;

public:
	CAbstractPhysics(void);
	virtual ~CAbstractPhysics(void);

	virtual float positionX() const;
	virtual float positionY() const;
	virtual float rotation() const; 

protected:
	//metody wywo�ywane przez klasy zaprzyja�nione
	//tylko one znaj� prawid�owe argumenty wywo�a�
	virtual void do_addToWorld(b2World *world, const b2Vec2 &pos = b2Vec2(0.0f, 0.0f)) = 0; 
	virtual void do_removeFromWorld(b2World *world) = 0;	

	virtual void do_beginContact(b2Contact* contact) { };
	virtual void do_endContact(b2Contact* contact) { };
	virtual void do_preSolve(b2Contact* contact, const b2Manifold* oldManifold) { }; 
	virtual void do_postSolve(b2Contact* contact, const b2ContactImpulse* impulse) { };
	virtual void do_step() { };

	//cia�o elementu
	b2Body *body_;
};

//=====================================================================

