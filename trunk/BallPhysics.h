#pragma once

#include "AbstractPhysics.h"

//=====================================================================

class CBallPhysics;
typedef boost::shared_ptr<CBallPhysics> BallPhysics;

//=====================================================================

class CBallPhysics : public CAbstractPhysics
{
public:
	CBallPhysics(int radius);
	virtual ~CBallPhysics(void);

protected:
	virtual void do_addToWorld(b2World *world, const b2Vec2 &pos = b2Vec2(0.0f, 0.0f)); 
	virtual void do_removeFromWorld(b2World *world);

private:
	float32 radius_;
};

//=====================================================================

