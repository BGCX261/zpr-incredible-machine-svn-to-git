#pragma once

#include "AbstractPhysics.h"
#include <set>

//=====================================================================

class CAntigravityPhysics;
typedef boost::shared_ptr<CAntigravityPhysics> AntigravityPhysics;

//=====================================================================

class CAntigravityPhysics : public CAbstractPhysics
{
public:
	CAntigravityPhysics(int width, int height, int influenceHeight);
	~CAntigravityPhysics(void);

	//element zawsze poziomy - optymalizacja
	virtual float rotation() const { return 0.0f; };

	bool isActive() const { return !influencedBodies_.empty(); };

protected:
	virtual void do_addToWorld(b2World *world, const b2Vec2 &pos = b2Vec2(0.0f, 0.0f)); 
	virtual void do_removeFromWorld(b2World *world);	

	virtual void do_beginContact(b2Contact* contact);
	virtual void do_endContact(b2Contact* contact);
	virtual void do_step();

private:
	float32 width_;
	float32 height_;
	float32 influenceHeight_;

	b2Fixture *sensor_;
	std::set<b2Body *> influencedBodies_;
};
