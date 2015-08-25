#pragma once
#include "AbstractPhysics.h"

//=====================================================================

class CRampPhysics;
typedef boost::shared_ptr<CRampPhysics> RampPhysics;

//=====================================================================

class CRampPhysics : public CAbstractPhysics
{
public:
	CRampPhysics(int width, int height, float angle);
	~CRampPhysics(void);

	//element nieobracalny - optymalizacja
	virtual float rotation() const { return -180 * angle_ / b2_pi; };

	void setRotation(float angle) { angle_ = -b2_pi * angle / 180.0f; };

protected:
	virtual void do_addToWorld(b2World *world, const b2Vec2 &pos = b2Vec2(0.0f, 0.0f)); 
	virtual void do_removeFromWorld(b2World *world);

private:
	float32 width_;
	float32 height_;
	float32 angle_;
};

//=====================================================================

