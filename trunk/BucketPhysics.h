#pragma once
#include "AbstractPhysics.h"
//=====================================================================

class CBucketPhysics;
typedef boost::shared_ptr<CBucketPhysics> BucketPhysics;

//=====================================================================

class CBucketPhysics : public CAbstractPhysics
{
public:
	CBucketPhysics(int width, int height, float angle);
	~CBucketPhysics(void);

	//element nieobracalny - optymalizacja
	virtual float rotation() const { return -180 * angle_ / b2_pi; };

	void setRotation(float angle) { angle_ = -b2_pi * angle / 180.0f; };

	bool isElementInside() const { return elementInside_; };

protected:
	virtual void do_addToWorld(b2World *world, const b2Vec2 &pos = b2Vec2(0.0f, 0.0f)); 
	virtual void do_removeFromWorld(b2World *world);	

	virtual void do_beginContact(b2Contact* contact);
	virtual void do_endContact(b2Contact* contact);

private:
	float32 width_;
	float32 height_;
	float32 angle_;

	b2Fixture *sensor_;

	bool elementInside_;
};
