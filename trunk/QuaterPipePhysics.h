#pragma once
#include "AbstractPhysics.h"

//=====================================================================

class CQuaterPipePhysics;
typedef boost::shared_ptr<CQuaterPipePhysics> QuaterPipePhysics;

//=====================================================================

class CQuaterPipePhysics : public CAbstractPhysics
{
public:
	CQuaterPipePhysics(int size, int pipeWidth, float angle);
	~CQuaterPipePhysics(void);

	//element nieobracalny - optymalizacja
	virtual float rotation() const { return -180 * angle_ / b2_pi; };

	void setRotation(float angle) { angle_ = -b2_pi * angle / 180.0f; };

protected:
	virtual void do_addToWorld(b2World *world, const b2Vec2 &pos = b2Vec2(0.0f, 0.0f)); 
	virtual void do_removeFromWorld(b2World *world);

private:
	float32 size_;
	float32 pipeWidth_;
	float32 angle_;
};

//=====================================================================
