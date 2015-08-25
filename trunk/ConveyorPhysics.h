#pragma once
#include "AbstractPhysics.h"

//=====================================================================

class CConveyorPhysics;
typedef boost::shared_ptr<CConveyorPhysics> ConveyorPhysics;

//=====================================================================

class CConveyorPhysics : public CAbstractPhysics
{
public:
	CConveyorPhysics(int width, int height, float conveyorSpeed);
	~CConveyorPhysics(void);	

	//element zawsze poziomy - optymalizacja
	virtual float rotation() const { return 0.0f; };

protected:
	virtual void do_addToWorld(b2World *world, const b2Vec2 &pos = b2Vec2(0.0f, 0.0f)); 
	virtual void do_removeFromWorld(b2World *world);

private:
	float32 width_;
	float32 height_;
	float32 conveyorSpeed_;
};
