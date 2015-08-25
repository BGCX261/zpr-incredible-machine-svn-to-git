#pragma once
#include "AbstractPhysics.h"

//=====================================================================

class CSpringBoardPhysics;
typedef boost::shared_ptr<CSpringBoardPhysics> SpringBoardPhysics;

//=====================================================================

class CSpringBoardPhysics : public CAbstractPhysics
{
public:
	CSpringBoardPhysics(int width, int height, float angle);
	~CSpringBoardPhysics(void);

	//element nieobracalny - optymalizacja
	virtual float rotation() const { return -180 * angle_ / b2_pi; };

	void setRotation(float angle) { angle_ = -b2_pi * angle / 180.0f; };

	bool bounce();

protected:
	virtual void do_addToWorld(b2World *world, const b2Vec2 &pos = b2Vec2(0.0f, 0.0f)); 
	virtual void do_removeFromWorld(b2World *world);

	virtual void do_postSolve(b2Contact* contact, const b2ContactImpulse* impulse);

private:
	float32 width_;
	float32 height_;
	float32 angle_;

	b2Fixture *sensor_;
	bool bounce_;
};

//=====================================================================
