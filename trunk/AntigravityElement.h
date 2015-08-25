#pragma once

#include "AbstractElement.h"
#include "AntigravityPhysics.h"

#include <boost/shared_ptr.hpp>

//=====================================================================

class CAntigravityElement;
typedef boost::shared_ptr<CAntigravityElement> AntigravityElement;

//=====================================================================

/*!
 * \brief
 * Element antygrawitacji
 * 
 * Element ten w swojej strefie wp³ywów zmienia grawitacj¹ na przeciwn¹ (odpycha elementy)
 */
class CAntigravityElement : public CAbstractElement
{
public:
	CAntigravityElement();
	~CAntigravityElement(void);

	virtual void startSimulation(const PhysicsWorld &world);
	virtual void stopSimulation(const PhysicsWorld &world);

	virtual void draw();
	virtual bool update();

	static CAbstractElement* create()
	{
		return new CAntigravityElement;
	};
	
private:
	AntigravityPhysics physics_;
	bool simulation_;

	CL_Sprite sprite_;
};

//===================================================================================================
